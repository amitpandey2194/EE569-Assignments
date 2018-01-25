/*
 * TextureClassificationDef.cpp
 *
 *  Created on: Mar 5, 2017
 *      Author: amitp
 */
#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include<string>
#include <fstream>
#include <math.h>
#include "TextureClassificationDec.h"
using namespace std;

TextureClassification::TextureClassification(){
	puts("constructor");
}

TextureClassification::TextureClassification(const TextureClassification & a){
	puts("copy constructor");
	height=a.height;
	width=a.width;
	BytesPerPixel=a.BytesPerPixel;
}
TextureClassification::~TextureClassification() {
	printf("destructor: height:%d,width:%d and BytesPerPixel:%d\n",height,width,BytesPerPixel );
}

TextureClassification & TextureClassification::operator=(const TextureClassification & o) {
	puts("assignment operator");
	if(this != &o) {
		height = o.height;
		width = o.width;
		BytesPerPixel = o.BytesPerPixel;
	}
	return *this;
}

unsigned char * TextureClassification::DynamicMemoryAllocation1d(int height,int width){
	unsigned char * ImagePointer=new unsigned char [height*width];
	for(int i=0;i<height*width;i++){
		ImagePointer[i]=0;
	}
	return ImagePointer;

}
unsigned char ** TextureClassification::DynamicMemoryAllocation2d(int height,int width){
	unsigned char ** ImagePointer=new unsigned char *[height];
	for(int i=0;i<height;i++){
		ImagePointer[i]=new unsigned char[width];
		for(int j=0;j<width;j++){
			ImagePointer[i][j]=0;
		}
	}
	return ImagePointer;

}
double ** TextureClassification::DynamicMemoryAllocation2d_double(int height,int width){
	double ** ImagePointer=new double *[height];
	for(int i=0;i<height;i++){
		ImagePointer[i]=new double[width];
		for(int j=0;j<width;j++){
			ImagePointer[i][j]=0;
		}
	}
	return ImagePointer;

}
int** TextureClassification::DynamicMemoryAllocation2d_int(int height,int width){
	int ** ImagePointer=new int *[height];
	for(int i=0;i<height;i++){
		ImagePointer[i]=new int[width];
		for(int j=0;j<width;j++){
			ImagePointer[i][j]=0;
		}
	}
	return ImagePointer;

}
unsigned char ** TextureClassification:: DynamicMemoryAllocation1d_2_2d(unsigned char * pointer,int height,int width){
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
unsigned char * TextureClassification::DynamicMemoryAllocation2d_2_1d(double ** pointer,int height,int width){
	unsigned char *Image=new unsigned char[height*width];
	int index=0;
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			Image[index]=unsigned char(pointer[i][j]);
			index++;
		}
	}
	return Image;
}
unsigned char ** TextureClassification::FileRead(const char *argv[],int index,int height,int width){
	FILE *file;
	unsigned char*Image=DynamicMemoryAllocation1d(height,width);
	errno_t err;
	if ((err = fopen_s(&file, argv[index], "rb") != 0)) {
		cout << "Cannot open file: " << argv[index] <<endl;
		exit(1);
	}
	fread(Image, sizeof(unsigned char), height*width, file);
	fclose(file);
	unsigned char ** ImagePointer=DynamicMemoryAllocation1d_2_2d(Image,height,width);
	file=nullptr;delete [] Image;
	return ImagePointer;

}
bool TextureClassification::FileWrite(const char *argv[],unsigned char *Image,int index,int height,int width){
	FILE *file; bool status=false;int success;
	errno_t err;
	if ((err = fopen_s(&file, argv[index], "wb") != 0)) {
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
double ** TextureClassification::LawFilterBank(string vector1,string vector2){
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
double ** TextureClassification::ExpansionFunction(double ** inputImage,int height,int width,int expansion){
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
double** TextureClassification::Convolution(double** ExpandedInput,int height,int width,double**filter,int expansion){
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
	}//printf("new image:");
	return OutPutFilteredImage;
}
double ** TextureClassification::AveragedImage(double**inputImage,int height,int width){
	double sum=0;double ** AveragedImage=DynamicMemoryAllocation2d_double(height,width);double globalMean;
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			sum+=inputImage[i][j];
		}
	}
	globalMean=(sum*1.0)/(height*width);
	//cout<<globalMean<<endl;
	//cout<<"new image"<<endl;
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			AveragedImage[i][j]=inputImage[i][j]-globalMean;

		}
	}
	//printf("%f",AveragedImage[0][0]);printf("\n");
	return AveragedImage;
}
double TextureClassification::AverageEnergy(double** inputImage,int height,int width){
	double average=0.0;double sum=0.0;
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			sum+=pow(inputImage[i][j],2);
		}
	}

	average=(sum)/(1.0*height*width);
	//	printf("%f   ",average);
	return average;
}
double ** TextureClassification::FeatureVectorGeneration(double**inputImage,int height,int width,double** filter){

	int windowSize=5;
	int expansion=(windowSize-1)/2;
	double **OutPutFilteredImage=DynamicMemoryAllocation2d_double(height,width);
	OutPutFilteredImage=Convolution(inputImage,height,width,filter,expansion);
	return OutPutFilteredImage;

}
double** TextureClassification::MainLogicFeatureVectorGeneration(const char*argv[],int height,int width,int numImages,int startPoint){
	int windowSize=5;
	int expansion=(windowSize-1)/2;
	double **FeatureVector=DynamicMemoryAllocation2d_double(numImages,25);
	string vector1[5]={"L5","E5","S5","W5","R5"};
	string vector2[5]={"L5","E5","S5","W5","R5"};
	double** averagedInputImage=DynamicMemoryAllocation2d_double(height,width);
	double **ExpandedDoubleImage=DynamicMemoryAllocation2d_double(height+(2*expansion),width+(2*expansion));
	unsigned char**InputImage=DynamicMemoryAllocation2d(height,width);
	double**InputImageDouble =DynamicMemoryAllocation2d_double(height,width);int counter=0;
	double **filter=DynamicMemoryAllocation2d_double(5,5);
	for(int img=startPoint;img<numImages+startPoint;img++){
		InputImage=FileRead(argv,img,height,width);
		for(int i=0;i<height;i++){
			for(int j=0;j<width;j++){
				InputImageDouble[i][j]=double(InputImage[i][j]);

			}
		}

		averagedInputImage=AveragedImage(InputImageDouble,height,width);
		ExpandedDoubleImage=ExpansionFunction(averagedInputImage,height,width,expansion);
		int count=0;
		for(int i=0;i<5;i++){
			for(int j=0;j<5;j++){
				filter=LawFilterBank(vector1[i],vector2[j]);
//				for(int a=0;a<5;a++){
//					for(int b=0;b<5;b++){
//						cout<<filter[a][b]<<" ";
//					}cout<<endl;
//				}
				double **OutPutImage=DynamicMemoryAllocation2d_double(height,width);
				OutPutImage=FeatureVectorGeneration(ExpandedDoubleImage,height,width,filter);
				FeatureVector[counter][count]=AverageEnergy(OutPutImage,height,width);
				count++;
				//				for(int j=0;j<width;j++){
				//					delete [] OutPutImage[j];
				//				}
				////				for(int j=0;j<5;j++){
				////					delete [] filter[j];
				////				}
				//				delete[] OutPutImage;//delete filter;
			}
		}
		//	printf("\n");
		//	printf("new texture\n");


		counter++;
	}
	//	for(int j=0;j<width;j++){
	//		delete [] averagedInputImage[j];
	//		delete [] InputImage[j];
	//		delete [] InputImageDouble[j];
	//	}
	//	delete [] averagedInputImage;delete [] InputImage;delete [] InputImageDouble;
	//	for(int j=0;j<width+(2*expansion);j++){
	//		delete [] ExpandedDoubleImage[j];
	//	}
	//	delete [] ExpandedDoubleImage;


	return FeatureVector;
}
double ** TextureClassification::K_MeansClustering_Training(double **TestingFeatureVector )
{
	double **codeBook=DynamicMemoryAllocation2d_double(4,25);int count=3;
	double **TestingFeatures=DynamicMemoryAllocation2d_double(12,25);
	for(int i=0;i<4;i++){
		for(int j=0;j<25;j++){
			codeBook[i][j]=TestingFeatureVector[count-3][j];
		}
		count+=3;
	}
	for(int i=0;i<12;i++){
		for(int j=0;j<25;j++){
			TestingFeatures[i][j]=TestingFeatureVector[i][j];
		}
	}
	//	////////////////////////////////////////////////////////////////////////////////
	int finalCount=0;double *euclideanD=new double[4];double tempD=0.0;double temp=0;int index=0;
	int *mappedIndex=new int [12]; double**cluster=DynamicMemoryAllocation2d_double(4,25);double**codeBookNew=DynamicMemoryAllocation2d_double(4,25);
	int oldmappedIndex[12]={0,0,0,0,0,0,0,0};
	while(finalCount!=12){
		finalCount=0;
		int clusterCount[4]={0,0,0,0};
		for(int i=0;i<12;i++){
			for(int k=0;k<4;k++){
				for(int j=0;j<25;j++){
					tempD+=pow((TestingFeatures[i][j]-codeBook[k][j]),2);
				}
				euclideanD[k]=(sqrt(tempD));
				//cout<<tempD<<endl;
				tempD=0.0;
				//cout<<euclideanD[k]<<endl;
			}
			//cout<<"testing"<<endl;
			temp=euclideanD[0];index=0;
			//		cout<<"outside:"<<temp<<endl;
			for(int k=1;k<4;k++){
				if(temp>euclideanD[k]){
					temp=euclideanD[k];
					index=k;
					//	cout<<index<<endl;
				}
				else if(temp==euclideanD[k]){
					index=mappedIndex[i];
				}
			}	//cout<<"temp:"<<temp<<endl;
			mappedIndex[i]=index;
			for(int j=0;j<25;j++){
				cluster[index][j]+=TestingFeatures[i][j];
			}
			clusterCount[index]+=1;

			//cout<<"The Texture"<<i<<" :is mapped to following index:"<<mappedIndex[i]<<endl;
		}

		///////////////
		for(int i=0;i<4;i++){
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
		for(int i=0;i<4;i++){
			for(int j=0;j<25;j++){
				codeBook[i][j]=codeBookNew[i][j];
				//cout<<codeBook[i][j]<<"  ";
				cluster[i][j]=0;
			}
			//cout<<endl;
		}
		for(int i=0;i<12;i++){
			if(oldmappedIndex[i]==mappedIndex[i]){
				finalCount+=1;
				//cout<<finalCount<<endl;
			}
		}
		for(int i=0;i<12;i++){
			oldmappedIndex[i]=mappedIndex[i];
		}
		//finalCount+=1;
		//printf("new iteration\n");
	}
	return codeBook;
}
void TextureClassification::K_MeansClustering_Testing(double ** codeBook,double **TestingFeatureVector){
	///code book assignment....
	double *euclideanD=new double[4];double tempD=0.0;double temp=0;int index=0;
	int mappedIndex[6]={0,0,0,0,0,0};int oldmappedIndex[6]={0,0,0,0,0,0};int clusterCount[4]={0,0,0,0};
	//	for(int i=0;i<12;i++){
	//				printf("%d\n",mappedIndexArray[i]);
	//			}
	for(int i=0;i<6;i++){
		for(int k=0;k<4;k++){
			for(int j=0;j<25;j++){
				tempD+=pow((TestingFeatureVector[i][j]-codeBook[k][j]),2);
			}
			euclideanD[k]=(sqrt(tempD));
			//cout<<tempD<<endl;
			tempD=0.0;
			//cout<<euclideanD[k]<<endl;
		}
		temp=euclideanD[0];index=0;

		for(int k=1;k<4;k++){
			if(temp>euclideanD[k]){
				temp=euclideanD[k];
				index=k;
				//	cout<<index<<endl;
			}
		}	//cout<<"temp:"<<temp<<endl;
		mappedIndex[i]=index;
		cout<<"The Texture"<<i<<" :is mapped to following index:"<<mappedIndex[i]<<endl;
	}


}
double ** TextureClassification::FeatureVectorNormalization(double **FeatureVectorTrainingTexture,int numRows)

{
	double** FeatureVectorTrainingNormalized=DynamicMemoryAllocation2d_double(numRows,25);
	double mean=0;double stdDev=0;double temp=0;
	for(int i=0;i<25;i++){
		for(int j=0;j<numRows;j++){
			temp+=FeatureVectorTrainingTexture[j][i];
		}
		mean=temp/numRows*1.0;temp=0.0;
		for(int j=0;j<numRows;j++){
			temp+=pow((FeatureVectorTrainingTexture[j][i]-mean),2);
		}
		stdDev=sqrt(temp/numRows*1.0);
		for(int j=0;j<numRows;j++){
			FeatureVectorTrainingNormalized[j][i]=(FeatureVectorTrainingTexture[j][i]-mean)/(stdDev);
			//cout<<FeatureVectorTrainingNormalized[j][i]<<endl;
		}//cout<<" "<<endl;
		temp=0.0;stdDev=0.0;mean=0.0;
	}
	return FeatureVectorTrainingNormalized;
}
double **TextureClassification::FeatureVectorNormalizationTraining(double **FeatureVectorTraningTexture,int numRows){
double** FeatureVectorTrainingNormalized=DynamicMemoryAllocation2d_double(numRows,25);
double mean=0;double stdDev=0;double temp=0;
	for(int i=0;i<25;i++){
		for(int j=0;j<numRows;j++){
			temp+=FeatureVectorTraningTexture[j][i];
		}
		mean=temp/numRows*1.0;temp=0.0;
		//printf("mean:%f\n",mean);
		for(int j=0;j<numRows;j++){
			temp+=pow((FeatureVectorTraningTexture[j][i]-mean),2);
		}
		stdDev=sqrt(temp/numRows*1.0);
		for(int j=0;j<numRows;j++){
			FeatureVectorTrainingNormalized[j][i]=(FeatureVectorTraningTexture[j][i]-mean)/(stdDev);
				printf("%f\n",FeatureVectorTrainingNormalized[j][i]);
		}
		//printf("stdDev:%f\n",stdDev);
		temp=0.0;stdDev=0.0;mean=0.0;
		printf("new filter\n");
	}
	return FeatureVectorTrainingNormalized;
}
double** TextureClassification::SuperVisedCodeBook(double **NormalizedFeatureVectorArray) {
	double**codeBook = DynamicMemoryAllocation2d_double(4, 25); int counter = 0;
	for (int i = 0; i <12;i+=3) {
		for (int j = 0; j < 25;j++) {
			codeBook[counter][j] += (NormalizedFeatureVectorArray[i][j] + NormalizedFeatureVectorArray[i + 1][j] + NormalizedFeatureVectorArray[i + 2][j])/(3*1.0);
		}		
		counter++;
	}
	return codeBook;
}
void TextureClassification::TextWriter(double**NormalizedFeatureVectorArray,string path,int numRows) {
	ofstream arrayData;
	arrayData.open(path);
	if (arrayData.is_open()) {
		for (int i = 0; i<numRows; i++) {
			for (int j = 0; j < 25;j++) {
				arrayData << NormalizedFeatureVectorArray[i][j];
				arrayData << "\t";
			}
			arrayData << "\n";
		}
		arrayData.close();
	}
	else
	{
		cout << "unable to open file" << endl;
	}//original histogram to text file
}