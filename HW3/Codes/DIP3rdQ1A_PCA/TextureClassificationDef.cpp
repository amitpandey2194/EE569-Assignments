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
double ** TextureClassification::K_MeansClustering_Training(double **TestingFeatureVector )
{
	double **codeBook=DynamicMemoryAllocation2d_double(4,3);int count=3;
	double **TestingFeatures=DynamicMemoryAllocation2d_double(12,3);
	//		for(int i=0;i<12;i++){
	//			for(int j=0;j<3;j++){
	//				printf("%f ",TestingFeatureVector[i][j]);
	//			}
	//			printf("\n");
	//		}
	//printf("initial codes\n");
	for(int i=0;i<4;i++){
		for(int j=0;j<3;j++){
			codeBook[i][j]=TestingFeatureVector[count-3][j];
			//printf("%f ",codeBook[i][j]);
		}
		//printf("\n");
		count+=3;
	}
	//printf("testing features\n");
	//count=0;
	for(int i=0;i<12;i++){
		//	if(i%3!=0){
		for(int j=0;j<3;j++){
			TestingFeatures[i][j]=TestingFeatureVector[i][j];
			//printf("%f ",TestingFeatures[i][j]);
		}
		//printf("\n");
		//count++;
		//}
	}
	//	////////////////////////////////////////////////////////////////////////////////
	int finalCount=0;double *euclideanD=new double[4];double tempD=0.0;double temp=0;int index=0;
	int *mappedIndex=new int [12]; double**cluster=DynamicMemoryAllocation2d_double(4,3);double**codeBookNew=DynamicMemoryAllocation2d_double(4,3);
	int oldmappedIndex[12]={0,0,0,0,0,0,0,0,0,0,0,0 };
	while(finalCount!=12){
		finalCount=0;
		int clusterCount[4]={0,0,0,0};
		for(int i=0;i<12;i++){
			for(int k=0;k<4;k++){
				for(int j=0;j<3;j++){
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
			for(int j=0;j<3;j++){
				cluster[index][j]+=TestingFeatures[i][j];
			}
			clusterCount[index]+=1;

			cout<<"The Texture"<<i<<" :is mapped to following index:"<<mappedIndex[i]<<endl;
		}

		///////////////
		for(int i=0;i<4;i++){
			if(clusterCount[i]!=0){
				for(int j=0;j<3;j++){
					codeBookNew[i][j]=(cluster[i][j])/clusterCount[i]*1.0;
					//printf("%f ",codeBookNew[i][j]);
				}
				//printf("cluster index:%d\n",i);

			}//printf("\n");
			else{
				for(int j=0;j<3;j++){
					codeBookNew[i][j]=codeBook[i][j];
				}
			}
			//	cout<<"count of:"<<i<<":"<<clusterCount[i]<<endl;
		}

		//	for(int i=0;i<4;i++){
		//		for(int j=0;j<3;j++){
		//			if(codeBookNew[i][j]==codeBook[i][j]){
		//
		//				printf("Final Count:%d  ",finalCount);
		//			}
		//		}
		//		printf("\n");
		//	}
		for(int i=0;i<4;i++){
			for(int j=0;j<3;j++){
				codeBook[i][j]=codeBookNew[i][j];
				//cout<<codeBook[i][j]<<"  ";
				cluster[i][j]=0;
			}
			//cout<<endl;
		}
		for(int i=0;i<12;i++){
			//printf(" old map values: %d,map indexes: %d\n",oldmappedIndex[i],mappedIndex[i]);

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
			for(int j=0;j<3;j++){
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
double** TextureClassification::SuperVisedCodeBook(double **NormalizedFeatureVectorArray) {
	double**codeBook = DynamicMemoryAllocation2d_double(4, 3); int counter = 0;
	for (int i = 0; i <12;i+=3) {
		for (int j = 0; j < 3;j++) {
			codeBook[counter][j] += (NormalizedFeatureVectorArray[i][j] + NormalizedFeatureVectorArray[i + 1][j] + NormalizedFeatureVectorArray[i + 2][j])/(3*1.0);
		}		
		counter++;
	}
	return codeBook;
}
void TextureClassification::TextWriter(double**NormalizedFeatureVectorArray) {
	ofstream arrayData;
	arrayData.open("C:\\Users\\amitp\\Desktop\\imageprocessing\\homeworks\\homework3_march26\\HW3_images\\P1\\outputdata\\1_a\\featureVectorArray.txt");


	if (arrayData.is_open()) {
		for (int i = 0; i<12; i++) {
			for (int j = 0; j < 3;j++) {
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
double** TextureClassification::TextReader(string path, int numRows) {
	ifstream array(path);
	double** PCAFeatureVectorArray = DynamicMemoryAllocation2d_double(numRows, 3);
	for (int i = 0; i < numRows;i++) {
		for (int j = 0; j < 3;j++) {
			array >> PCAFeatureVectorArray[i][j];
		}
	}
	return PCAFeatureVectorArray;
}