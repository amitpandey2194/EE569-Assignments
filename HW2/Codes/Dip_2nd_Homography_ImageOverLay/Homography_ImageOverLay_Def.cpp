/*
 * Homography_ImageOverLay_Def.cpp
 *
 *  Created on: Feb 18, 2017
 *      Author: amitp
 */
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "Homography_ImageOverLay_Dec.h"
#include<string>
using namespace std;
Homography::Homography(){
	puts("constructor");
}

Homography::Homography(const Homography & a){
	puts("copy constructor");
	height=a.height;
	width=a.width;
	BytesPerPixel=a.BytesPerPixel;
}
Homography::~Homography() {
	printf("destructor: height:%d,width:%d and BytesPerPixel:%d\n",height,width,BytesPerPixel );
}

Homography & Homography::operator=(const Homography & o) {
	puts("assignment operator");
	if(this != &o) {
		height = o.height;
		width = o.width;
		BytesPerPixel = o.BytesPerPixel;
	}
	return *this;
}

unsigned char * Homography::DynamicMemoryAllocation1d(int height,int width,int BytesPerPixel){
	unsigned char * ImagePointer=new unsigned char [height*width*BytesPerPixel];
	return ImagePointer;

}
unsigned char *** Homography::DynamicMemoryAllocation3d(int height,int width,int BytesPerPixel){
	unsigned char *** ImagePointer=new unsigned char **[height];
	for(int i=0;i<height;i++){
		ImagePointer[i]=new unsigned char *[width];
		for(int j=0;j<width;j++){
			ImagePointer[i][j]=new unsigned char[BytesPerPixel];
		}
	}
	return ImagePointer;

}
unsigned char *** Homography:: DynamicMemoryAllocation1d_2_3d(unsigned char * pointer,int height,int width,int BytesPerPixel){
	unsigned char ***Image=new unsigned char **[height];
	for(int i=0;i<height;i++){
		Image[i]=new unsigned char *[width];
		for(int j=0;j<width;j++){
			Image[i][j]=new unsigned char[BytesPerPixel];
		}
	}
	int index=0;
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			for(int k=0;k<3;k++){
				Image[i][j][k]=pointer[index];
				index++;
			}
		}
	}

	return Image;
}
unsigned char * Homography::DynamicMemoryAllocation3d_2_1d(unsigned char *** pointer,int height,int width,int BytesPerPixel){
	unsigned char *Image=new unsigned char[height*width*BytesPerPixel];
	int index=0;
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			for(int k=0;k<3;k++){
				Image[index]=pointer[i][j][k];
				index++;
			}
		}
	}
	return Image;
}
unsigned char *** Homography::FileRead(const char *argv[],int index,int height,int width,int BytesPerPixel){
	FILE *file;
	unsigned char*Image=DynamicMemoryAllocation1d(height,width,BytesPerPixel);
	if (!(file=fopen(argv[index],"rb"))) {
		cout << "Cannot open file: " << argv[index] <<endl;
		exit(1);
	}
	fread(Image, sizeof(unsigned char), height*width*BytesPerPixel, file);
	fclose(file);
	unsigned char *** ImagePointer=DynamicMemoryAllocation1d_2_3d(Image,height,width,BytesPerPixel);
	file=nullptr;delete [] Image;
	return ImagePointer;

}
bool Homography::FileWrite(const char *argv[],unsigned char *Image,int index,int height,int width,int BytesPerPixel){
	FILE *file; bool status=false;int success;
	if (!(file=fopen(argv[index],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}

	success=fwrite(Image, sizeof(unsigned char), height*width*BytesPerPixel, file);
	fclose(file);
	if(success==height*width*BytesPerPixel){
		status=true;
	}
	return status;

}
unsigned char*** Homography::HomographyLogic(unsigned char ***TrojanSC,unsigned char***Field,int heightSC,int widthSC,int heightF,int widthF,int BytePerPixel){
	unsigned char *** FieldFinal=Field;
	double fieldH_Cart,fieldW_Cart,TrojanCartH,TrojanCartW;double trojan_Ind_Cart[3];double field_Cart_Vector[3];double temp=0;
	double h[3][3]={{0.1949,2.6271,-409.7144},{-1.2736,1.1873,523.8087},{0.0003,-0.0030,1.0}};
	double L,L1,L2,L3,L4;int p,q;
	field_Cart_Vector[2]=1.0;//homogeneous coordinates
	double TrojanImageX,TrojanImageY;


	for(int i=0;i<heightF;i++){
		fieldH_Cart=heightF-i-0.5;
		for(int j=0;j<widthF;j++){
			fieldW_Cart=j+0.5;
			field_Cart_Vector[0]=fieldW_Cart;field_Cart_Vector[1]=fieldH_Cart;
			L=fieldH_Cart;
			L1=((-(1.0/43)*fieldW_Cart)+206.2325);
			L2=(((0.75)*fieldW_Cart)-183.875);
			L3=(((15.0/14)*fieldW_Cart)-440.1785);
			L4=((-(2.0/27)*fieldW_Cart)+156.055);
//			cout<<"L is:"<<L<<"for i:"<<i<<endl;
//			cout<<"L1 is:"<<L1<<"for j:"<<j<<endl;
//			cout<<"L2 is:"<<L2<<"for j:"<<j<<endl;
//			cout<<"L3 is:"<<L3<<"for j:"<<j<<endl;
//			cout<<"L4 is:"<<L4<<"for j:"<<j<<endl;
			if((L<=L1) && (L<=L2) && (L>=L3) &&(L>=L4)){
				for(int k=0;k<3;k++){
					for(int l=0;l<3;l++){
						temp+=h[k][l]*field_Cart_Vector[l];
					}
					trojan_Ind_Cart[k]=temp;
					temp=0;
				}
				TrojanCartW=(trojan_Ind_Cart[0]*1.0/trojan_Ind_Cart[2]);TrojanCartH=(trojan_Ind_Cart[1]*1.0/trojan_Ind_Cart[2]);
				TrojanImageX=TrojanCartW-0.5;TrojanImageY=heightSC-TrojanCartH-0.5;
				q=floor(TrojanImageX);p=floor(TrojanImageY);

				if((q>=0 && q<widthSC) && (p>=0 && p<heightSC)){
					if(!((TrojanSC[p][q][0]<=255 && TrojanSC[p][q][0]>=240) && (TrojanSC[p][q][1]<=255 && TrojanSC[p][q][1]>=240) && (TrojanSC[p][q][2]<=255 && TrojanSC[p][q][2]>=240))){
						for(int m=0;m<3;m++){
							FieldFinal[i][j][m]=TrojanSC[p][q][m];
						}
					}
				}


			}


		}
	}



	return FieldFinal;
}


