/*
 * shrinking_def.cpp
 *
 *  Created on: Feb 21, 2017
 *      Author: amitp
 */
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "shrinking_dec.h"
#include<string>
#include <fstream>
using namespace std;

Shrinking::Shrinking(){
	puts("constructor");
}

Shrinking::Shrinking(const Shrinking & a){
	puts("copy constructor");
	height=a.height;
	width=a.width;
	BytesPerPixel=a.BytesPerPixel;
}
Shrinking::~Shrinking() {
	printf("destructor: height:%d,width:%d and BytesPerPixel:%d\n",height,width,BytesPerPixel );
}

Shrinking & Shrinking::operator=(const Shrinking & o) {
	puts("assignment operator");
	if(this != &o) {
		height = o.height;
		width = o.width;
		BytesPerPixel = o.BytesPerPixel;
	}
	return *this;
}

unsigned char * Shrinking::DynamicMemoryAllocation1d(int height,int width){
	unsigned char * ImagePointer=new unsigned char [height*width];
	return ImagePointer;

}
unsigned char ** Shrinking::DynamicMemoryAllocation2d(int height,int width){
	unsigned char ** ImagePointer=new unsigned char *[height];
	for(int i=0;i<height;i++){
		ImagePointer[i]=new unsigned char[width];
	}
	return ImagePointer;

}
unsigned char ** Shrinking:: DynamicMemoryAllocation1d_2_2d(unsigned char * pointer,int height,int width){
	unsigned char **Image=new unsigned char *[height];
	for(int i=0;i<height;i++){
		Image[i]=new unsigned char [width];
	}
	int index=0;
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			Image[i][j]=pointer[index];
			index++;
		}
	}

	return Image;
}
unsigned char * Shrinking::DynamicMemoryAllocation2d_2_1d(unsigned char ** pointer,int height,int width){
	unsigned char *Image=new unsigned char[height*width];
	int index=0;
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			Image[index]=pointer[i][j];
			index++;
		}
	}
	return Image;
}
unsigned char ** Shrinking::FileRead(const char *argv[],int index,int height,int width){
	FILE *file;
	unsigned char*Image=DynamicMemoryAllocation1d(height,width);
	if (!(file=fopen(argv[index],"rb"))) {
		cout << "Cannot open file: " << argv[index] <<endl;
		exit(1);
	}
	fread(Image, sizeof(unsigned char), height*width, file);
	fclose(file);
	unsigned char ** ImagePointer=DynamicMemoryAllocation1d_2_2d(Image,height,width);
	file=nullptr;delete [] Image;
	return ImagePointer;

}
bool Shrinking::FileWrite(const char *argv[],unsigned char *Image,int index,int height,int width){
	FILE *file; bool status=false;int success;
	if (!(file=fopen(argv[index],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}

	success=fwrite(Image, sizeof(unsigned char), height*width, file);
	fclose(file);
	if(success==height*width){
		status=true;
	}
	return status;

}
int Shrinking::compareString(string *BondArray,string imageArray,int sizeOfBondArray){
	int counter=0;

	for(int i=0;i<sizeOfBondArray;i++){

		if(BondArray[i]==imageArray){
			//cout<<BondArray[i]<<endl;
			counter++;
			i=sizeOfBondArray;
		}
	}

	return counter;

}
unsigned char ** Shrinking::ShrinkingLogic_FirstStage(unsigned char ** InputImage,int height,int width){
	string Bond_1[4]={"001010000","100010000","000010100","000010001"};
	string Bond_2[4]={"000011000","010010000","000110000","000010010"};
	string Bond_3[8]={"001011000","011010000","110010000","100110000","000110100","000010110","000010011","000011001"};
	string Bond_4[4]={"001011001","111010000","100110100","000010111"};
	string Bond_5[8]={"110011000","010011001","011110000","001011010","011011000","110110000","000110110","000011011"};
	string Bond_6[10]={"110011001","011110100","111011000","011011001","111110000","110110100","100110110","000110111","000011111","001011011"};
	string Bond_7[4]={"111011001","111110100","100110111","001011111"};
	string Bond_8[4]={"011011011","111111000","110110110","000111111"};
	string Bond_9[8]={"111011011","011011111","111111100","111111001","111110110","110110111","100111111","001111111"};
	string Bond_10[4]={"111011111","111111101","111110111","101111111"};
	unsigned char **NormInputImage=DynamicMemoryAllocation2d(height,width);
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			NormInputImage[i][j]=InputImage[i][j];
		}
	}

	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			NormInputImage[i][j]=((NormInputImage[i][j]*1.0)/255.0);
		}
	}//Normalizing the Input to 0 & 1;

	int Bond=0;unsigned char **MArray=DynamicMemoryAllocation2d(height,width);int counter=0;

	for(int i=1;i<height-1;i++){
		for(int j=1;j<width-1;j++){
			string s;
		if(NormInputImage[i][j]==1){
			for(int k=0;k<3;k++){
				for(int l=0;l<3;l++){

					if(NormInputImage[i+k-1][j+l-1]==1){
						if(k%2==0 && l%2==0){
							Bond+=1;

						}
						else if((k%2==0 && l%2!=0) || (k%2!=0 && l%2==0)){
							Bond+=2;
						}

					}
					s+=to_string(NormInputImage[i+k-1][j+l-1]);

				}
			}

			if(Bond>0 && Bond <12){

				switch(Bond){
				case 1:
					counter=compareString(Bond_1,s,4);

					break;
				case 2:
					counter=compareString(Bond_2,s,4);
					break;
				case 3:
					counter=compareString(Bond_3,s,8);
					break;
				case 4:
					counter=compareString(Bond_4,s,4);
					break;
				case 5:
					counter=compareString(Bond_5,s,8);
					break;
				case 6:
					counter=compareString(Bond_6,s,10);
					break;
				case 7:
					counter=compareString(Bond_7,s,4);
					break;
				case 8:
					counter=compareString(Bond_8,s,4);
					break;
				case 9:
					counter=compareString(Bond_9,s,8);
					break;
				case 10:
					counter=compareString(Bond_10,s,4);
					break;
				default:
					cout<<"default"<<endl;
					break;

				}
			}
			if(counter==1){
				MArray[i][j]=1;
			}
			else if (counter==0){
				MArray[i][j]=0;

			}
			counter=0;
			Bond=0;
			//printf("%d",NormInputImage[i][j]);


		}

		else if(NormInputImage[i][j]==0){
				MArray[i][j]=0;

		}
	}
}


	return MArray;

}
unsigned char** Shrinking::ShrinkingLogic_SecondStage(unsigned char **MArray,unsigned char ** InputImage,int height,int width,string *uncond){
	unsigned char **OutPutImage=DynamicMemoryAllocation2d(height,width);
	int counter=0;
	for(int i=1;i<height-1;i++){
		for(int j=1;j<width-1;j++){
			if(MArray[i][j]==1){

				string s;
				for(int k=0;k<3;k++){
					for(int l=0;l<3;l++){
						s+=to_string(MArray[i+k-1][j+l-1]);
					}
				}

				counter=compareString(uncond,s,364);


				if(counter==1){

					OutPutImage[i][j]=InputImage[i][j];

				}
				else if(counter==0){
					OutPutImage[i][j]=0;

				}
				counter=0;

			}
			else if (MArray[i][j]==0) {
				OutPutImage[i][j]=InputImage[i][j];
			}
		}
	}
return OutPutImage;

}
void Shrinking::Histogram(unsigned char **InputImage, int height,int width){
	// Histogram of Squares
		int k = 0;int count = 0;int HistogramArray[24];
		int int1, int2, int3, int4, int5, int6, int7, int8;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				count = 0;
			if(i-1>=0 && i+1<height && j-1>=0 && j+1<width){
				int1 = InputImage[i - 1][j];
				int2 = InputImage[i + 1][j];
				int3 = InputImage[i][j - 1];
				int4 = InputImage[i][j + 1];
				int5 = InputImage[i - 1][j - 1];
				int6 = InputImage[i + 1][j + 1];
				int7 = InputImage[i + 1][j - 1];
				int8 = InputImage[i - 1][j + 1];
			}
				if (InputImage[i][j] == 255 && int1 == 0 && int2 == 255 && int3 == 0 && int4 == 255 && int5 == 0 && int6 == 255 && int7 == 0 && int8 == 0) {


					while (InputImage[i][j] != 0) {
						j++;
						count++;
					}

					HistogramArray[k] = count;
					k++;
				}
				else if (InputImage[i][j] == 255 && int1 == 0 && int2 == 0 && int3 == 0 && int4 == 0 && int5 == 0 && int6 == 0 && int7 == 0 && int8 == 0)
				{


					while (InputImage[i][j] != 0) {
						j++;
						count++;
					}

					HistogramArray[k] = count;
					k++;
				}
			}
		}
		cout << "Sizes of different Squares" << endl;
		for (int k = 0; k < 24; k++) {
			printf("%d ",HistogramArray[k]);
		}

}

