// DIP3rdQ1A.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
/*
* Main.cpp
*
*  Created on: Mar 5, 2017
*      Author: amitp
*/
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "TextureClassificationdec.h"
#include <fstream>
#include <math.h>
using namespace std;
int main(int argc, const char *argv[])
{
	int height, width;
	//Input read for height,width,BytesPerPixel///
	// Check if size is specified
	if (argc >= 2) {
		height = atoi(argv[1]);
		width = atoi(argv[2]);
		cout << height << endl;
		cout << width << endl;
	}
	TextureClassification obj;
	double **FeatureVectorTrainingNormalized = obj.TextReader("C:\\Users\\amitp\\Desktop\\imageprocessing\\homeworks\\homework3_march26\\HW3_images\\P1\\outputdata\\1_a\\PCA.txt",12);
	double **FeatureVectorTestingNormalized = obj.TextReader("C:\\Users\\amitp\\Desktop\\imageprocessing\\homeworks\\homework3_march26\\HW3_images\\P1\\outputdata\\1_a\\PCATEST.txt",6);
	double **codeBook = obj.K_MeansClustering_Training(FeatureVectorTrainingNormalized);
	obj.K_MeansClustering_Testing(codeBook, FeatureVectorTestingNormalized);
	double**SupervisedCodeBook = obj.SuperVisedCodeBook(FeatureVectorTrainingNormalized);
	obj.K_MeansClustering_Testing(SupervisedCodeBook, FeatureVectorTestingNormalized);
	obj.TextWriter(FeatureVectorTrainingNormalized);
	return 0;
}





