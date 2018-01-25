/*
 * TextureClassifcationDec.h
 *
 *  Created on: Mar 5, 2017
 *      Author: amitp
 */

#ifndef TEXTURECLASSIFICATIONDEC_H_
#define TEXTURECLASSIFICATIONDEC_H_
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include<string>
#include "stdafx.h"
using namespace std;
class TextureClassification{
	int height=0,width=0,BytesPerPixel=0;
public:
//	double **codeBook=new double *[4];
//	int *mappedArray=new int[12];
	//constructor//
	TextureClassification();
	TextureClassification(const TextureClassification &); // copy constructor
	TextureClassification & operator=(const TextureClassification &); // copy operator
	~TextureClassification();  // destructor

	int getBytesPerPixel() const {
		return BytesPerPixel;
	}

	void setBytesPerPixel(int bytesPerPixel) {
		BytesPerPixel = bytesPerPixel;
	}

	int getHeight() const {
		return height;
	}

	void setHeight(int height) {
		this->height = height;
	}

	int getWidth() const {
		return width;
	}

	void setWidth(int width) {
		this->width = width;
	}
			unsigned char * DynamicMemoryAllocation1d(int,int);
			unsigned char * DynamicMemoryAllocation2d_2_1d(double **,int,int);
			unsigned char ** DynamicMemoryAllocation2d(int,int);
			double ** DynamicMemoryAllocation2d_double(int,int);
			int** DynamicMemoryAllocation2d_int(int,int);
			unsigned char ** DynamicMemoryAllocation1d_2_2d(unsigned char *,int,int);
			unsigned char ** FileRead(const char*[],int,int,int);
			bool FileWrite(const char*[],unsigned char *,int,int,int);
			double ** LawFilterBank(string,string);
			double **ExpansionFunction(double**,int,int,int);
			double ** Convolution(double**,int,int,double**,int);
			double ** AveragedImage(double**,int,int);
			double AverageEnergy(double**,int,int);
			double** FeatureVectorGeneration(double**,int,int,double**);
			double** MainLogicFeatureVectorGeneration(const char*[],int,int,int,int);
			double** FeatureVectorNormalization(double**,int);
			double** FeatureVectorNormalizationTraining( double**,int);
			double **K_MeansClustering_Training(double**);
			void K_MeansClustering_Testing(double**,double**);
			double** SuperVisedCodeBook(double**);
			void TextWriter(double **,string,int);
};






#endif /* TEXTURECLASSIFICATIONDEC_H_ */
