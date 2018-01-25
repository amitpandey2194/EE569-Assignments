/*
 * Ditheringdef.cpp
 *
 *  Created on: Feb 24, 2017
 *      Author: amitp
 */
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "Ditheringdec.h"
#include<string>
#include <fstream>
using namespace std;

Dithering::Dithering(){
	puts("constructor");
}

Dithering::Dithering(const Dithering & a){
	puts("copy constructor");
	height=a.height;
	width=a.width;
	BytesPerPixel=a.BytesPerPixel;
}
Dithering::~Dithering() {
	printf("destructor: height:%d,width:%d and BytesPerPixel:%d\n",height,width,BytesPerPixel );
}

Dithering & Dithering::operator=(const Dithering & o) {
	puts("assignment operator");
	if(this != &o) {
		height = o.height;
		width = o.width;
		BytesPerPixel = o.BytesPerPixel;
	}
	return *this;
}

unsigned char * Dithering::DynamicMemoryAllocation1d(int height,int width){
	unsigned char * ImagePointer=new unsigned char [height*width];
	return ImagePointer;

}
unsigned char ** Dithering::DynamicMemoryAllocation2d(int height,int width){
	unsigned char ** ImagePointer=new unsigned char *[height];
	for(int i=0;i<height;i++){
		ImagePointer[i]=new unsigned char[width];
	}
	return ImagePointer;

}
unsigned char ** Dithering:: DynamicMemoryAllocation1d_2_2d(unsigned char * pointer,int height,int width){
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
unsigned char * Dithering::DynamicMemoryAllocation2d_2_1d(unsigned char ** pointer,int height,int width){
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
unsigned char ** Dithering::FileRead(const char *argv[],int index,int height,int width){
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
bool Dithering::FileWrite(const char *argv[],unsigned char *Image,int index,int height,int width){
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


unsigned char ** Dithering::DitheringLogic(unsigned char ** InputImage,int height,int width){
	int I_2[2][2]={{0,2},{3,1}};
	int I_4[4][4]={{0,8,2,10},{12,1,14,3},{3,11,1,9},{15,4,13,2}};
	for(int i=0;i<4;i++){
			for(int j=0;j<4;j++){
				printf("%d ",I_4[i][j]);
			}
			printf("\n");
		}
	int A_4[4][4]={{14,10 ,11, 15},{9 ,3 ,0 ,4},{8 ,2 ,1 ,5},{13, 7 ,6, 12}};
	int I_8[8][8]={{0,32,8,40,2,34,10,42},{48,4,56,12,50,6,58,14},{12,44,4,36,14,46,6,38},{60,16,52,8,62,18,54,10},
			{3,35,11,43,1,33,9,41},{51,7,59,15,49,5,57,13},{15,47,7,39,13,45,5,37},{63,19,55,11,61,17,53,9}};
	int sizeofMat=sizeof(I_8)/sizeof(I_8[0]);
	unsigned char **T=DynamicMemoryAllocation2d(sizeofMat,sizeofMat);
	for(int i=0;i<sizeofMat;i++){
		for(int j=0;j<sizeofMat;j++){
			T[i][j]=((I_8[i][j]+0.5)*255)/(pow(sizeofMat,2));
		}
	}
	unsigned char ** OutPutImage=DynamicMemoryAllocation2d(height,width);
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			if(InputImage[i][j]>T[int(fmod(i,sizeofMat))][int(fmod(j,sizeofMat))]){
				OutPutImage[i][j]=255;
			}
			else{
				OutPutImage[i][j]=0;
			}

		}
	}



	return OutPutImage;

}
unsigned char** Dithering::FourLevelGrayScale(unsigned char** InputImage,int height,int width){
	int Threshold0_85=(85-1)/2;
	int Threshold85_170=(170+85-1)/2;
	int Threshold170_255=(170+255-1)/2;
	unsigned char ** OutputImage=DynamicMemoryAllocation2d(height,width);
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			if(InputImage[i][j]>Threshold0_85 && InputImage[i][j]<85 ){
				OutputImage[i][j]=85;
			}
			else if(InputImage[i][j]<Threshold0_85 && InputImage[i][j]>=0){
				OutputImage[i][j]=0;
			}
			else if(InputImage[i][j]>Threshold85_170 && InputImage[i][j]<170){
				OutputImage[i][j]=170;
			}
			else if(InputImage[i][j]<Threshold85_170 && InputImage[i][j]>=85){
				OutputImage[i][j]=85;
			}
			else if(InputImage[i][j]>Threshold170_255 && InputImage[i][j]<255){
				OutputImage[i][j]=255;
			}
			else if(InputImage[i][j]<Threshold170_255 && InputImage[i][j]>=170){
				OutputImage[i][j]=170;
			}
			else{
				printf("error");
			}
		}
	}
	return OutputImage;
}
unsigned char ** Dithering::ErrorDiffusionFloyd(unsigned char ** InputImageMain,int height,int width){
	int oldPixel,newPixel;int error;
	unsigned char**OutPutImage=DynamicMemoryAllocation2d(height,width);
	unsigned char**InputImage=DynamicMemoryAllocation2d(height,width);
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			InputImage[i][j]=InputImageMain[i][j];
		}

	}
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			oldPixel=InputImage[i][j];
			if(oldPixel>127){
				newPixel=255;
			}
			else{
				newPixel=0;
			}
			OutPutImage[i][j]=newPixel;
			InputImage[i][j]=newPixel;
			error=oldPixel-newPixel;
			if(j+1<width){
				InputImage[i][j+1]+=(error*(7/16.0));
			}
			if(j-1>=0 && i+1<height){
				InputImage[i+1][j-1]+=(error*(3/16.0));
			}
			if(i+1<height){
				InputImage[i+1][j]+=(error*(5/16.0));
			}
			if(j+1<width && i+1<height){
				InputImage[i+1][j+1]+=(error*(1/16.0));
			}
		}
	}	return OutPutImage;
}
unsigned char ** Dithering::ErrorDiffusionJJN(unsigned char **InputImageMain,int height,int width){
	int oldPixel,newPixel;int error;
	unsigned char**OutPutImage=DynamicMemoryAllocation2d(height,width);
	unsigned char**InputImage=DynamicMemoryAllocation2d(height,width);
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			InputImage[i][j]=InputImageMain[i][j];
		}
	}
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			oldPixel=InputImage[i][j];
			if(oldPixel>127){
				newPixel=255;
			}
			else{
				newPixel=0;
			}
			OutPutImage[i][j]=newPixel;
			InputImage[i][j]=newPixel;
			error=oldPixel-newPixel;
			if(j+1<width){
				InputImage[i][j+1]+=(error*(7/48.0));
			}
			if(j+2<width){
				InputImage[i][j+2]+=(error*(5/48.0));
			}
			if(j-2>=0 && i+1<height){
				InputImage[i+1][j-2]+=(error*(3/48.0));
			}
			if(j-1>=0 && i+1<height){
				InputImage[i+1][j-1]+=(error*(5/48.0));
			}
			if(i+1<height){
				InputImage[i+1][j]+=(error*(7/48.0));
			}
			if(j+1<width && i+1<height){
				InputImage[i+1][j+1]+=(error*(5/48.0));
			}

			if(j+2<width && i+1<height){
				InputImage[i+1][j+2]+=(error*(3/48.0));
			}

			if(j-2>=0 && i+2<height){
				InputImage[i+2][j-2]+=(error*(1/48.0));
			}
			if(j-1>=0 && i+2<height){
				InputImage[i+2][j-1]+=(error*(3/48.0));
			}
			if(i+2<height){
				InputImage[i+2][j]+=(error*(5/48.0));
			}
			if(j+1<width && i+2<height){
				InputImage[i+2][j+1]+=(error*(3/48.0));
			}
			if(j+2<width && i+2<height){
				InputImage[i+2][j+2]+=(error*(1/48.0));
			}
		}
	}
	return OutPutImage;
}
unsigned char** Dithering::ErrorDiffusionStucki(unsigned char** InputImageMain,int height,int width){
	int oldPixel,newPixel;int error;
		unsigned char**OutPutImage=DynamicMemoryAllocation2d(height,width);
		unsigned char**InputImage=DynamicMemoryAllocation2d(height,width);
		for(int i=0;i<height;i++){
			for(int j=0;j<width;j++){
				InputImage[i][j]=InputImageMain[i][j];
			}
		}
		for(int i=0;i<height;i++){
			for(int j=0;j<width;j++){
				oldPixel=InputImage[i][j];
				if(oldPixel>127){
					newPixel=255;
				}
				else{
					newPixel=0;
				}
				OutPutImage[i][j]=newPixel;
				InputImage[i][j]=newPixel;
				error=oldPixel-newPixel;
				if(j+1<width){
					InputImage[i][j+1]+=(error*(8/42.0));
				}
				if(j+2<width){
					InputImage[i][j+2]+=(error*(4/42.0));
				}
				if(j-2>=0 && i+1<height){
					InputImage[i+1][j-2]+=(error*(2/42.0));
				}
				if(j-1>=0 && i+1<height){
					InputImage[i+1][j-1]+=(error*(4/42.0));
				}
				if(i+1<height){
					InputImage[i+1][j]+=(error*(8/42.0));
				}
				if(j+1<width && i+1<height){
					InputImage[i+1][j+1]+=(error*(4/42.0));
				}

				if(j+2<width && i+1<height){
					InputImage[i+1][j+2]+=(error*(2/42.0));
				}

				if(j-2>=0 && i+2<height){
					InputImage[i+2][j-2]+=(error*(1/42.0));
				}
				if(j-1>=0 && i+2<height){
					InputImage[i+2][j-1]+=(error*(2/42.0));
				}
				if(i+2<height){
					InputImage[i+2][j]+=(error*(4/42.0));
				}
				if(j+1<width && i+2<height){
					InputImage[i+2][j+1]+=(error*(2/42.0));
				}
				if(j+2<width && i+2<height){
					InputImage[i+2][j+2]+=(error*(1/48.0));
				}
			}
		}
		return OutPutImage;
}


