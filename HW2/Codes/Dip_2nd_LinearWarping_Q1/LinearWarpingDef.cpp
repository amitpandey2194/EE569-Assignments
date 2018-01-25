/*
 * LinearWarpingDef.cpp
 *
 *  Created on: Feb 17, 2017
 *      Author: amitp
 */
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "LinearWarping.h"
#include<string>
using namespace std;
LinearWarping::LinearWarping(){
	puts("constructor");
}

LinearWarping::LinearWarping(const LinearWarping & a){
	puts("copy constructor");
	height=a.height;
	width=a.width;
	BytesPerPixel=a.BytesPerPixel;
}
LinearWarping::~LinearWarping() {
	printf("destructor: height:%d,width:%d and BytesPerPixel:%d\n",height,width,BytesPerPixel );
}

LinearWarping & LinearWarping::operator=(const LinearWarping & o) {
	puts("assignment operator");
	if(this != &o) {
		height = o.height;
		width = o.width;
		BytesPerPixel = o.BytesPerPixel;
	}
	return *this;
}

unsigned char * LinearWarping::DynamicMemoryAllocation1d(int height,int width,int BytesPerPixel){
	unsigned char * ImagePointer=new unsigned char [height*width*BytesPerPixel];
	return ImagePointer;

}
unsigned char *** LinearWarping::DynamicMemoryAllocation3d(int height,int width,int BytesPerPixel){
	unsigned char *** ImagePointer=new unsigned char **[height];
	for(int i=0;i<height;i++){
		ImagePointer[i]=new unsigned char *[width];
		for(int j=0;j<width;j++){
			ImagePointer[i][j]=new unsigned char[BytesPerPixel];
		}
	}
	return ImagePointer;

}
unsigned char *** LinearWarping:: DynamicMemoryAllocation1d_2_3d(unsigned char * pointer,int height,int width,int BytesPerPixel){
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
unsigned char * LinearWarping::DynamicMemoryAllocation3d_2_1d(unsigned char *** pointer,int height,int width,int BytesPerPixel){
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
unsigned char *** LinearWarping::FileRead(const char *argv[],int index,int height,int width,int BytesPerPixel){
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
bool LinearWarping::FileWrite(const char *argv[],unsigned char *Image,int index,int height,int width,int BytesPerPixel){
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
unsigned char*** LinearWarping::LinearWarpingLogic(unsigned char *** MainImage,int height,int width,int BytesPerPixel){
unsigned char ***LinearWarpedImage=DynamicMemoryAllocation3d(height,width,BytesPerPixel);
int midPoint=((width/2)-1);int columnStart,columnEnd;int countOP;int countIP=width;double x_inv;double factor;int q;int counter=0;int temp;

for(int i=0;i<height/2;i++){
	columnStart=midPoint-i;
	columnEnd=midPoint+i;
	countOP=columnEnd-columnStart+1;
	factor=(countOP*1.0)/(countIP);
//	cout<<columnStart<<endl;
//	cout<<columnEnd<<endl;
//	cout<<countOP<<endl;
//	cout<<countIP<<endl;;
//	cout<<factor<<endl;
	for(int j=columnStart;j<=columnEnd;j++){
			x_inv=counter/factor;
			//cout<<x_inv<<endl;
			q=floor(x_inv);
			for(int k=0;k<3;k++){
				LinearWarpedImage[i][j][k]=MainImage[i][q][k];
			}
			counter++;
		}
	counter=0;
}

for(int i=height/2;i<height;i++){
	columnStart=i-midPoint;
	temp=columnStart*2;
	temp=midPoint-temp;
	columnEnd=i+temp;
	countOP=columnEnd-columnStart+1;
	factor=(countOP*1.0)/countIP;
	for(int j=columnStart;j<=columnEnd;j++){
		x_inv=counter/factor;
		q=floor(x_inv);
		for(int k=0;k<3;k++){
			LinearWarpedImage[i][j][k]=MainImage[i][q][k];
		}
		counter++;
	}
	counter=0;
}










return LinearWarpedImage;
}


