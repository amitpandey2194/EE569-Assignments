/*
 * ImageSegmentationDef.cpp
 *
 *  Created on: Mar 16, 2017
 *      Author: amitp
 */
#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include<string>
#include <fstream>
#include <math.h>
#include"Segmentation.h"
#include<random>
#include<ctime>
using namespace std;
ImageSegmentation::ImageSegmentation(){
	puts("constructor");
}

ImageSegmentation::~ImageSegmentation() {
	printf("destructor");
}
unsigned char * ImageSegmentation::DynamicMemoryAllocation1d(int height,int width,int BytesPerPixel){
	unsigned char * ImagePointer=new unsigned char [height*width*BytesPerPixel];
	for(int i=0;i<height*width;i++){
		ImagePointer[i]=0;
	}
	return ImagePointer;

}
int * ImageSegmentation::DynamicMemoryAllocation1dint(int height,int width){
	int * ImagePointer=new int [height*width];
	for(int i=0;i<height*width;i++){
		ImagePointer[i]=0;
	}
	return ImagePointer;

}
unsigned char ** ImageSegmentation::DynamicMemoryAllocation2d(int height,int width){
	unsigned char ** ImagePointer=new unsigned char *[height];
	for(int i=0;i<height;i++){
		ImagePointer[i]=new unsigned char[width];
		for(int j=0;j<width;j++){
			ImagePointer[i][j]=0;
		}
	}
	return ImagePointer;

}
double ** ImageSegmentation::DynamicMemoryAllocation2d_double(int height,int width){
	double ** ImagePointer=new double *[height];
	for(int i=0;i<height;i++){
		ImagePointer[i]=new double[width];
		for(int j=0;j<width;j++){
			ImagePointer[i][j]=0;
		}
	}
	return ImagePointer;

}
int** ImageSegmentation::DynamicMemoryAllocation2d_int(int height,int width){
	int ** ImagePointer=new int *[height];
	for(int i=0;i<height;i++){
		ImagePointer[i]=new int[width];
		for(int j=0;j<width;j++){
			ImagePointer[i][j]=0;
		}
	}
	return ImagePointer;

}
unsigned char ** ImageSegmentation:: DynamicMemoryAllocation1d_2_2d(unsigned char * pointer,int height,int width){
	unsigned char **Image=new unsigned char *[height];
	for(int i=0;i<height;i++){
		Image[i]=new unsigned char [width];
		for(int j=0;j<width;j++){
			Image[i][j]=0;
		}
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
unsigned char * ImageSegmentation::DynamicMemoryAllocation2d_2_1d(double ** pointer,int height,int width){
	unsigned char *Image=new unsigned char[height*width];
	int index=0;
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			Image[index]=(unsigned char)pointer[i][j];
			index++;
		}
	}
	return Image;
}
double *** ImageSegmentation::DynamicMemoryAllocation3dDouble(int height,int width,int BytesPerPixel){
	double *** ImagePointer=new double **[height];
	for(int i=0;i<height;i++){
		ImagePointer[i]=new double *[width];
		for(int j=0;j<width;j++){
			ImagePointer[i][j]=new double[BytesPerPixel];
			for(int k=0;k<BytesPerPixel;k++){
				ImagePointer[i][j][k]=0;
			}
		}
	}
	return ImagePointer;

}
int *** ImageSegmentation::DynamicMemoryAllocation3dint(int height,int width,int BytesPerPixel){
	int *** ImagePointer=new int **[height];
	for(int i=0;i<height;i++){
		ImagePointer[i]=new int *[width];
		for(int j=0;j<width;j++){
			ImagePointer[i][j]=new int[BytesPerPixel];
			for(int k=0;k<BytesPerPixel;k++){
				ImagePointer[i][j][k]=0;
			}
		}
	}
	return ImagePointer;

}
double *** ImageSegmentation:: DynamicMemoryAllocation1d_2_3dDouble(double * pointer,int height,int width,int BytesPerPixel){
	double ***Image=new double **[height];
	for(int i=0;i<height;i++){
		Image[i]=new double *[width];
		for(int j=0;j<width;j++){
			Image[i][j]=new double[BytesPerPixel];
			for(int k=0;k<BytesPerPixel;k++){
				Image[i][j][k]=0;
			}
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
double * ImageSegmentation::DynamicMemoryAllocation3d_2_1dDouble(double *** pointer,int height,int width,int BytesPerPixel){
	double *Image=new double[height*width*BytesPerPixel];
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
unsigned char* ImageSegmentation::DynamicMemoryAllocation3d_2_1dUC(unsigned char *** pointer,int height,int width,int BytesPerPixel){
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
unsigned char *** ImageSegmentation:: DynamicMemoryAllocation1d_2_3d(unsigned char * pointer,int height,int width,int BytesPerPixel){
	unsigned char ***Image=new unsigned char **[height];
	for(int i=0;i<height;i++){
		Image[i]=new unsigned char *[width];
		for(int j=0;j<width;j++){
			Image[i][j]=new unsigned char[BytesPerPixel];
			for(int k=0;k<BytesPerPixel;k++){
				Image[i][j][k]=0;
			}
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
unsigned char *** ImageSegmentation::DynamicMemoryAllocation3d(int height,int width,int BytesPerPixel){
	unsigned char *** ImagePointer=new unsigned char **[height];
	for(int i=0;i<height;i++){
		ImagePointer[i]=new unsigned char *[width];
		for(int j=0;j<width;j++){
			ImagePointer[i][j]=new unsigned char[BytesPerPixel];
			for(int k=0;k<BytesPerPixel;k++){
				ImagePointer[i][j][k]=0;
			}
		}
	}
	return ImagePointer;

}
double ** ImageSegmentation::RGB2GRAY(const char*argv[],double*** colorImage,int height,int width,int BytesPerPixel){
	double**GrayScaleImage=DynamicMemoryAllocation2d_double(height,width);
	//unsigned char**GrayImage=DynamicMemoryAllocation2d(height,width);
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			GrayScaleImage[i][j]=0.2989*colorImage[i][j][0]+0.5870*colorImage[i][j][1]+0.1140*colorImage[i][j][2];
			//GrayImage[i][j]=(unsigned char)(GrayScaleImage[i][j]);
		}
	}
	unsigned char*GraySclImage=DynamicMemoryAllocation2d_2_1d(GrayScaleImage,height,width);
	FileWrite(argv,GraySclImage,6,height,width,1);
	return GrayScaleImage;
}
unsigned char *** ImageSegmentation::FileRead(const char *argv[],int index,int height,int width,int BytesPerPixel){
	FILE *file;
	unsigned char*Image=DynamicMemoryAllocation1d(height,width,BytesPerPixel);
	errno_t err;
	if ((err=fopen_s(&file,argv[index],"rb")!=0)) {
		cout << "Cannot open file: " << argv[index] <<endl;
		exit(1);
	}
	fread(Image, sizeof(unsigned char), height*width*BytesPerPixel, file);
	fclose(file);
	unsigned char *** ImagePointer=DynamicMemoryAllocation1d_2_3d(Image,height,width,BytesPerPixel);
	file=nullptr;delete [] Image;
	return ImagePointer;

}
bool ImageSegmentation::FileWrite(const char *argv[],unsigned char *Image,int index,int height,int width,int BytesPerPixel){
	FILE *file; bool status=false;int success;
	errno_t err;
	if ((err = fopen_s(&file, argv[index], "wb") != 0)) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}

	success=fwrite(Image, sizeof(unsigned char), height*width*BytesPerPixel, file);
	fclose(file);
	if(success==height*width){
		status=true;
	}
	return status;

}
double ** ImageSegmentation::LawFilterBank(string vector1,string vector2){
	double L5[5]={1,4,6,4,1};double E5[5]={-1,-2,0,2,1};double S5[5]={-1,0,2,0,-1};double W5[5]={-1,2,0,-2,1};double R5[5]={1,-4,6,-4,1};
	double transpose_Vector[5][1];double rightHand_Vector[5];
	double **filter=DynamicMemoryAllocation2d_double(5,5);
	if(vector1=="L5"){
		for(int i=0;i<5;i++){
			transpose_Vector[i][0]=L5[i];
		}
		//cout<<"L5"<<endl;
	}
	else if(vector1=="E5"){
		for(int i=0;i<5;i++){
			transpose_Vector[i][0]=E5[i];
		}
		//cout<<"E5"<<endl;
	}
	else if(vector1=="S5"){
		for(int i=0;i<5;i++){
			transpose_Vector[i][0]=S5[i];
		}
		//cout<<"S5"<<endl;
	}
	else if(vector1=="W5"){
		for(int i=0;i<5;i++){
			transpose_Vector[i][0]=W5[i];

		}
		//cout<<"W5"<<endl;
	}
	else if(vector1=="R5"){
		for(int i=0;i<5;i++){
			transpose_Vector[i][0]=R5[i];
		}
		//cout<<"R5"<<endl;
	}
	else{
		cout<<"error"<<endl;
	}
	//////////////////////////////////////////////////
	if(vector2=="L5"){
		for(int i=0;i<5;i++){
			rightHand_Vector[i]=L5[i];
		}
		//cout<<"L5"<<endl;
	}
	else if(vector2=="E5"){
		for(int i=0;i<5;i++){
			rightHand_Vector[i]=E5[i];
		}
		//	cout<<"E5"<<endl;
	}
	else if(vector2=="S5"){
		for(int i=0;i<5;i++){
			rightHand_Vector[i]=S5[i];
		}
		//cout<<"S5"<<endl;
	}
	else if(vector2=="W5"){
		for(int i=0;i<5;i++){
			rightHand_Vector[i]=W5[i];
		}
		//cout<<"W5"<<endl;

	}
	else if(vector2=="R5"){
		for(int i=0;i<5;i++){
			rightHand_Vector[i]=R5[i];
		}
		//cout<<"R5"<<endl;
	}
	else{
		cout<<"error"<<endl;
	}
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			filter[i][j]=transpose_Vector[i][0]*rightHand_Vector[j];
		}
	}
	//	for(int i=0;i<5;i++){
	//		for(int j=0;j<5;j++){
	//			printf("%d    ",filter[i][j]);
	//		}
	//		printf("\n");
	//	}
	//	printf("new filter\n");
	return filter;


}
double ** ImageSegmentation::ExpansionFunction(double ** inputImage,int height,int width,int expansion){
	double**ExpandedImage=DynamicMemoryAllocation2d_double(height+(2*expansion),width+(2*expansion));
	//cout<<expansion<<endl;
	///expansion of the image N*N to N+2*N+2/////
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			ExpandedImage[i+expansion][j+expansion]=inputImage[i][j];
			if(i==0){
				for(int k=0;k<expansion;k++){
					ExpandedImage[k][j+expansion]=inputImage[i][j];
				}
			}
			if(i==height-1){
				for(int k=i+expansion+1;k<=i+(2*expansion);k++){
					ExpandedImage[k][j+expansion]=inputImage[i][j];
				}
			}

		}
	}///copy data up and down for expansion////
	///now column expansion/////
	for(int i=expansion-1;i>=0;i--){
		for(int j=0;j<height+(2*expansion);j++){
			ExpandedImage[j][i]=ExpandedImage[j][i+1];
		}
	}
	for(int i=width+expansion;i<width+(expansion*2);i++){
		for(int j=0;j<height+(2*expansion);j++){
			ExpandedImage[j][i]=ExpandedImage[j][width+expansion-1];
		}
	}//corrected expansion logic
	//	for(int i=125;i<height+expansion;i++){
	//			for(int j=125;j<width+expansion;j++){
	//				printf("%f ",ExpandedImage[i][j]);
	//
	//			}printf("\n");
	//	}
	//	//done with expansion///
	return ExpandedImage;
}
double** ImageSegmentation::Convolution(double** ExpandedInput,int height,int width,double**filter,int expansion){
	int windowSize=(expansion*2)+1;
	double** OutPutFilteredImage=DynamicMemoryAllocation2d_double(height,width);
	//		for(int i=0;i<5;i++){
	//									for(int j=0;j<5;j++){
	//										printf("%f    ",filter[i][j]);
	//									}
	//									printf("\n");
	//								}
	//								printf("new filter\n");
	for(int i=expansion;i<height+expansion;i++){
		for(int j=expansion;j<width+expansion;j++){
			for(int maskrow=0;maskrow<windowSize;maskrow++){
				for(int maskcol=0;maskcol<windowSize;maskcol++){
					OutPutFilteredImage[i-expansion][j-expansion]+=(ExpandedInput[i+maskrow-expansion][j+maskcol-expansion]*filter[maskrow][maskcol]);

				}
			}
			//printf("%f\n",OutPutFilteredImage[i-expansion][j-expansion]);

		}
	}
	return OutPutFilteredImage;
}
double ** ImageSegmentation::AveragedImage(double**inputImage,int height,int width){
	double sum=0;double ** AveragedImage=DynamicMemoryAllocation2d_double(height,width);double globalMean;
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			sum+=inputImage[i][j];
		}
	}
	globalMean=(sum*1.0)/(height*width);
	//cout<<globalMean<<endl;
	//cout<<sum<<endl;
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			AveragedImage[i][j]=inputImage[i][j]-globalMean;
			//printf("%f\n",AveragedImage[i][j]);
		}
	}
	return AveragedImage;
}
double ** ImageSegmentation::FeatureVectorGeneration(double**inputImage,int height,int width,double** filter){

	int windowSize=5;
	int expansion=(windowSize-1)/2;
	double **OutPutFilteredImage=DynamicMemoryAllocation2d_double(height,width);
	OutPutFilteredImage=Convolution(inputImage,height,width,filter,expansion);
	return OutPutFilteredImage;

}
double*** ImageSegmentation::MainLogicFeatureVectorGeneration(const char*argv[],int height,int width,int BytesPerPixel,int energyBlockSize){
	int windowSize=5;int expansion=(windowSize-1)/2;
	string vector1[5]={"L5","E5","S5","W5","R5"};
	string vector2[5]={"L5","E5","S5","W5","R5"};
	unsigned char***InputImage=DynamicMemoryAllocation3d(height,width,BytesPerPixel);
	double***InputImageDouble =DynamicMemoryAllocation3dDouble(height,width,BytesPerPixel);
	double **filter=DynamicMemoryAllocation2d_double(5,5);
	InputImage=FileRead(argv,1,height,width,BytesPerPixel);
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			for(int k=0;k<3;k++){
				InputImageDouble[i][j][k]=double(InputImage[i][j][k]);
				//cout<<InputImageDouble[i][j][k]<<" ";
			}//cout<<"|";
		}//cout<<endl;
	}
	double**InputImageGray=DynamicMemoryAllocation2d_double(height,width);

	InputImageGray=RGB2GRAY(argv,InputImageDouble,height,width,BytesPerPixel);//RGB2GRAYFunction Call;
	double**averagedInputImage=DynamicMemoryAllocation2d_double(height,width);
	averagedInputImage=AveragedImage(InputImageGray,height,width);//GlobalMeanSubtraction
	double**ExpandedDoubleImage=DynamicMemoryAllocation2d_double(height,width);
	ExpandedDoubleImage=ExpansionFunction(averagedInputImage,height,width,expansion);//Expansion
	double***FeatureVectorArray=DynamicMemoryAllocation3dDouble(height,width,25);
	double **ExpandedConvolvedImage=DynamicMemoryAllocation2d_double(height,width);
	double**PixelEArray=DynamicMemoryAllocation2d_double(height,width);
	int counter=0;expansion=(energyBlockSize-1)/2;
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			filter=LawFilterBank(vector1[i],vector2[j]);
			double **OutPutImage=DynamicMemoryAllocation2d_double(height,width);
			OutPutImage=FeatureVectorGeneration(ExpandedDoubleImage,height,width,filter);//ImageAfterConvolution
			ExpandedConvolvedImage=ExpansionFunction(OutPutImage,height,width,expansion);//ExpansionFor13*13 or 15*15 filter
			PixelEArray=PixelEnergyArray(ExpandedConvolvedImage,height,width,expansion);///Energy Calculation////
//			for(int k=0;k<height;k++){
//												for(int l=0;l<width;l++){
//													cout<<PixelEArray[k][l]<<" ";
//												}
//												cout<<endl;
//											}
			for(int k=0;k<height;k++){
				for(int l=0;l<width;l++){
					FeatureVectorArray[k][l][counter]=PixelEArray[k][l];///Stacking of the Images///
					//cout<<FeatureVectorArray[k][l][0]<<" ";
				}//cout<<endl;
			}
//
////							for(int j=0;j<width;j++){
////								delete [] OutPutImage[j];
////							}
////			//				for(int j=0;j<5;j++){
////			//					delete [] filter[j];
////			//				}
////							delete[] OutPutImage;//delete filter;
			counter++;
		}
	}
//	/*//	printf("\n");
//	//	printf("new texture\n");
//	//	for(int j=0;j<width;j++){
//	//		delete [] averagedInputImage[j];
//	//		delete [] InputImage[j];
//	//		delete [] InputImageDouble[j];
//	//	}
//	//	delete [] averagedInputImage;delete [] InputImage;delete [] InputImageDouble;
//	//	for(int j=0;j<width+(2*expansion);j++){
//	//		delete [] ExpandedDoubleImage[j];
//	//	}
//	//	delete [] ExpandedDoubleImage;*/


	return FeatureVectorArray;
}
double**ImageSegmentation::PixelEnergyArray(double**ExpandedImage,int height,int width,int expansion){
	int windowSize=(expansion*2)+1;
	//cout<<windowSize<<endl;
	double** OutPutFilteredImage=DynamicMemoryAllocation2d_double(height,width);
	double**OutPutEnergyArray=DynamicMemoryAllocation2d_double(height,width);
	//		for(int i=0;i<5;i++){
	//									for(int j=0;j<5;j++){
	//										printf("%f    ",filter[i][j]);
	//									}
	//									printf("\n");
	//								}
	//								printf("new filter\n");
	for(int i=expansion;i<height+expansion;i++){
		for(int j=expansion;j<width+expansion;j++){
			for(int maskrow=0;maskrow<windowSize;maskrow++){
				for(int maskcol=0;maskcol<windowSize;maskcol++){
					OutPutFilteredImage[i-expansion][j-expansion]+=pow((ExpandedImage[i+maskrow-expansion][j+maskcol-expansion]),2);
				}
			}
			//printf("%f\n",OutPutFilteredImage[i-expansion][j-expansion]);
		}
	}
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			OutPutEnergyArray[i][j]=OutPutFilteredImage[i][j]/(windowSize*windowSize)*1.0;
		}
	}
	/*for (int i = 0; i < 10;i++) {
		for (int j = 0; j < 10;j++) {
			cout << OutPutEnergyArray[i][j] << "\t";
		}cout << endl;
	}*/
	return OutPutFilteredImage;
}
double***ImageSegmentation::FeatureVectorNormalization(double***FeatureArrayVector,int height,int width,int BytesPerPixel){
	double***NormlizedFeatureArrayVector=DynamicMemoryAllocation3dDouble(height,width,BytesPerPixel);
		for(int i=0;i<height;i++){
			for(int j=0;j<width;j++){
				for(int k=0;k<BytesPerPixel;k++){
				NormlizedFeatureArrayVector[i][j][k]=FeatureArrayVector[i][j][k]/(FeatureArrayVector[i][j][0]);
			}
		}
	}
	return NormlizedFeatureArrayVector;
}
double** ImageSegmentation::InitialCodeBook(double ***NormalizedFeatureVectorArray,int numClusters,int height,int width,int BytesPerPixel,int**coordinateArray){
	double** codeBook=DynamicMemoryAllocation2d_double(numClusters,BytesPerPixel);
	for(int i=0;i<numClusters;i++){
		for(int k=0;k<BytesPerPixel;k++){
			codeBook[i][k]=NormalizedFeatureVectorArray[coordinateArray[i][0]][coordinateArray[i][1]][k];
			//<<codeBook[i][k]<<" ";
		}//cout<<endl;
	}
	return codeBook;
}
int **ImageSegmentation::K_MeansClustering(double***NormalizedFeatureVectorArray,double**codeBook,int numClusters,int height,int width){
	int finalCount=0;double *euclideanD=new double[numClusters];double tempD=0.0;double temp=0;int index=0;
	int **mappedIndex=DynamicMemoryAllocation2d_int(height,width); double**cluster=DynamicMemoryAllocation2d_double(numClusters,25);double**codeBookNew=DynamicMemoryAllocation2d_double(numClusters,25);
	int **oldmappedIndex=DynamicMemoryAllocation2d_int(height,width);
	while(finalCount!=height*width){
		finalCount=0;
		int clusterCount[5] = {0,0,0,0,0};
		for(int i=0;i<height;i++){
			for(int j=0;j<width;j++){
				for(int k=0;k<numClusters;k++){
					for(int l=0;l<25;l++){
						tempD+=pow((NormalizedFeatureVectorArray[i][j][l]-codeBook[k][l]),2);
					}
					euclideanD[k]=(sqrt(tempD));
					//cout<<tempD<<endl;
					tempD=0.0;
					//cout<<euclideanD[k]<<endl;
				}
				//cout<<"testing"<<endl;
				temp=euclideanD[0];index=0;
				//		cout<<"outside:"<<temp<<endl;
				for(int k=1;k<numClusters;k++){
					if(temp>euclideanD[k]){
						temp=euclideanD[k];
						index=k;
					//	cout<<index<<endl;
					}
				/*	else if(temp==euclideanD[k]){
						index=mappedIndex[i][j];
					}*/
				}	//cout<<"temp:"<<temp<<endl;
				mappedIndex[i][j]=index;
				for(int m=0;m<25;m++){
					cluster[index][m]+=NormalizedFeatureVectorArray[i][j][m];
				}
				clusterCount[index]+=1;
			}
		}
		for(int i=0;i<numClusters;i++){
			if(clusterCount[i]!=0){
				for(int j=0;j<25;j++){
					codeBookNew[i][j]=(cluster[i][j])/clusterCount[i]*1.0;
					//printf("%f ",codeBookNew[i][j]);
				}
				//printf("cluster index:%d\n",i);

			}//printf("\n");
			else{
				for(int j=0;j<25;j++){
					codeBookNew[i][j]=codeBook[i][j];
				}
			}
			//	cout<<"count of:"<<i<<":"<<clusterCount[i]<<endl;
		}
		for(int i=0;i<numClusters;i++){
			for(int j=0;j<25;j++){
				codeBook[i][j]=codeBookNew[i][j];
				//	cout<<codeBook[i][j]<<"  ";
				cluster[i][j]=0.0;
			}
			//cout<<endl;
		}

		for(int i=0;i<height;i++){
			for(int j=0;j<width;j++){
				if(oldmappedIndex[i][j]==mappedIndex[i][j]){
					finalCount+=1;
					//cout<<finalCount<<endl;
				}
			}
		}

		for(int i=0;i<height;i++){
			for(int j=0;j<width;j++){
				oldmappedIndex[i][j]=mappedIndex[i][j];
			}
		}
		//finalCount+=1;
		printf("new iteration\n");
	}
	for (int i = 0; i < 5;i++) {
		for (int j = 0; j < 25;j++) {
			cout << codeBook[i][j] << "\t";
		}cout << endl;
	}
	return mappedIndex;
}
unsigned char***ImageSegmentation::ColorCoding(const char *argv[],int**mappedIndex,int numClusters,int height,int width,int BytesPerPixel){
	//unsigned char***ImageSegmentation::ColorCoding(int numClusters,int height,int width,int BytesPerPixel){
	unsigned char***FinalImage=DynamicMemoryAllocation3d(height,width,BytesPerPixel);
	//random_device rd;
	//mt19937 gen(rd());
	//uniform_int_distribution<> dis(0, 255);
	int **colors=DynamicMemoryAllocation2d_int(numClusters,BytesPerPixel);
	srand(time(0));
	for(int i=0;i<numClusters;i++){
		for(int j=0;j<BytesPerPixel;j++){
			colors[i][j]=rand()%256;
			 cout << colors[i][j]<<" ";
		}
		cout<<endl;
	}
	double** binaryImage = DynamicMemoryAllocation2d_double(height,width);
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			if (mappedIndex[i][j]>0) {
				binaryImage[i][j] = 255;
			}
			for(int k=0;k<BytesPerPixel;k++){
				FinalImage[i][j][k]=colors[mappedIndex[i][j]][k];
			}
		}
	}
	unsigned char *BinaryImage = DynamicMemoryAllocation2d_2_1d(binaryImage,height,width);
	FileWrite(argv,BinaryImage,7,height,width,1);
	return FinalImage;
}
