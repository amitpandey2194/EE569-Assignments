/*
 * Segmentation.h
 *
 *  Created on: Mar 16, 2017
 *      Author: amitp
 */
#include "stdafx.h"
#ifndef SEGMENTATION_H_
#define SEGMENTATION_H_
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include<string>
using namespace std;
class ImageSegmentation{
public:

	ImageSegmentation();
	~ImageSegmentation();  // destructor

	unsigned char * DynamicMemoryAllocation1d(int,int,int);
	int * DynamicMemoryAllocation1dint(int,int);
//////////////////////////////////////////////////////////////////////
	unsigned char ** DynamicMemoryAllocation2d(int,int);
	double ** DynamicMemoryAllocation2d_double(int,int);
	int** DynamicMemoryAllocation2d_int(int,int);
//////////////////////////////////////////////////////////////////////
	unsigned char * DynamicMemoryAllocation2d_2_1d(double **,int,int);
	double * DynamicMemoryAllocation3d_2_1dDouble(double ***,int,int,int);
	unsigned char * DynamicMemoryAllocation3d_2_1dUC(unsigned char ***,int,int,int);
//////////////////////////////////////////////////////////////////////////////////////
	unsigned char ** DynamicMemoryAllocation1d_2_2d(unsigned char *,int,int);
	double *** DynamicMemoryAllocation1d_2_3dDouble(double *,int,int,int);
	unsigned char *** DynamicMemoryAllocation1d_2_3d(unsigned char *,int,int,int);
///////////////////////////////////////////////////////////////////////////////////////
	double *** DynamicMemoryAllocation3dDouble(int,int,int);
	unsigned char *** DynamicMemoryAllocation3d(int,int,int);
	int***DynamicMemoryAllocation3dint(int,int,int);
/////////////////////////////////////////////////////////////////////////////////////////
	unsigned char *** FileRead(const char*[],int,int,int,int);
	bool FileWrite(const char*[],unsigned char *,int,int,int,int);
	double ** LawFilterBank(string,string);
	double **ExpansionFunction(double**,int,int,int);
	double ** Convolution(double**,int,int,double**,int);
	double ** AveragedImage(double**,int,int);
	double** FeatureVectorGeneration(double**,int,int,double**);
	double*** MainLogicFeatureVectorGeneration(const char*[],int,int,int,int);
	double*** FeatureVectorNormalization(double***,int,int,int);
	int **K_MeansClustering(double***,double**,int,int height,int width);
	double**RGB2GRAY(const char*[],double***,int,int,int);
	double**PixelEnergyArray(double**,int,int,int);
	double**InitialCodeBook(double***,int,int,int,int,int**);
	unsigned char***ColorCoding(const char*[],int**,int,int,int,int);

};




#endif /* SEGMENTATION_H_ */
