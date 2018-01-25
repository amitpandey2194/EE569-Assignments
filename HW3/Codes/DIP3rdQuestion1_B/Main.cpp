// DIP3rd2Question.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

/*
* Main.cpp
*
*  Created on: Mar 16, 2017
*      Author: amitp
*/
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "Segmentation.h"
#include <fstream>
#include <math.h>
using namespace std;
int main(int argc, const char *argv[])
{
	int height, width, BytesPerPixel;
	//Input read for height,width,BytesPerPixel///
	if (argc < 3) {
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw  and rest other 11 textures " << endl;
		return 0;
	}
	// Check if size is specified
	if (argc >= 4) {
		BytesPerPixel = atoi(argv[3]);
		height = atoi(argv[4]);
		width = atoi(argv[5]);
		cout << height << endl;
		cout << width << endl;
	}
	ImageSegmentation obj;
	double***FeatureVectorArray = obj.MainLogicFeatureVectorGeneration(argv, height, width, BytesPerPixel, 13);
	//	for(int i=0;i<height;i++){
	//		for(int j=0;j<width;j++){
	//			cout<<FeatureVectorArray[i][j][0]<<" ";
	//		}
	//		cout<<endl;
	//	}
	double***NormalizedFeatureArrayVector = obj.FeatureVectorNormalization(FeatureVectorArray, height, width, 25);
	int numClusters = 5;
	int**coordinateArray = obj.DynamicMemoryAllocation2d_int(numClusters, 2);
	coordinateArray[0][0] = 64; coordinateArray[0][1] = 31;
	coordinateArray[1][0] = 87; coordinateArray[1][1] = 282;
	coordinateArray[2][0] = 100; coordinateArray[2][1] = 395;
	coordinateArray[3][0] = 152; coordinateArray[3][1] = 228;
	coordinateArray[4][0] = 265; coordinateArray[4][1] = 383;
	for (int i = 0; i < 10;i++) {
		for (int j = 0; j < 10;j++) {
			cout << NormalizedFeatureArrayVector[i][j][1] << "  ";
		}
		cout << endl;
	}
	double **codeBook = obj.InitialCodeBook(NormalizedFeatureArrayVector, numClusters, height, width, 25, coordinateArray);
	int **mappedarray = obj.K_MeansClustering(NormalizedFeatureArrayVector, codeBook, numClusters, height, width);
	unsigned char***finalimage = obj.ColorCoding(argv,mappedarray, numClusters, height, width, BytesPerPixel);
	unsigned char*finalimagewrite = obj.DynamicMemoryAllocation3d_2_1dUC(finalimage, height, width, BytesPerPixel);
	obj.FileWrite(argv, finalimagewrite, 2, height, width, BytesPerPixel);





	return 0;
}





