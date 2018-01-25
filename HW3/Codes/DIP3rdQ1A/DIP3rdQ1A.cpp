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
int main (int argc, const char *argv[])
{
	int height,width;
	//Input read for height,width,BytesPerPixel///
	if (argc < 19){
			cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
			cout << "program_name input_image.raw  and rest other 11 textures " << endl;
			return 0;
		}
			// Check if size is specified
			if (argc >= 20){
				height = atoi(argv[19]);
				width = atoi(argv[20]);
				cout<<height<<endl;
				cout<<width<<endl;
		}
TextureClassification obj;
double **FeatureVectorTraningTexture=obj.MainLogicFeatureVectorGeneration(argv,height,width,12,1);
for(int i=0;i<12;i++){
	for(int j=0;j<25;j++){
		cout<<FeatureVectorTraningTexture[i][j]<<" ";
	}cout<<endl;
}
double **FeatureVectorTrainingNormalized=obj.FeatureVectorNormalizationTraining(FeatureVectorTraningTexture,12);
double **FeatureTestingTexture=obj.MainLogicFeatureVectorGeneration(argv,height,width,6,13);
double **codeBook=obj.K_MeansClustering_Training(FeatureVectorTrainingNormalized);
double**FeatureVectorTestingNormalized=obj.FeatureVectorNormalization(FeatureTestingTexture,6);
obj.K_MeansClustering_Testing(codeBook,FeatureVectorTestingNormalized);
double**SupervisedCodeBook = obj.SuperVisedCodeBook(FeatureVectorTrainingNormalized);
obj.K_MeansClustering_Testing(SupervisedCodeBook, FeatureVectorTestingNormalized);
cout << "print" << endl;
for (int i = 0; i < 12;i++) {
	for (int j = 0; j < 25;j++) {
		cout << FeatureVectorTrainingNormalized[i][j] << endl;
	}
	cout << "new texture" << endl;
}
obj.TextWriter(FeatureVectorTrainingNormalized,"C:\\Users\\amitp\\Desktop\\imageprocessing\\homeworks\\homework3_march26\\HW3_images\\P1\\outputdata\\1_a\\featureVectorArray.txt",12);
obj.TextWriter(FeatureVectorTestingNormalized, "C:\\Users\\amitp\\Desktop\\imageprocessing\\homeworks\\homework3_march26\\HW3_images\\P1\\outputdata\\1_a\\featureVectorTestArray.txt",6);
	return 0;
}





