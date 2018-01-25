// DIP_3rd_Surf_OpenCV.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/highgui.hpp"
#include <math.h>
#include <fstream>

using namespace cv;
using namespace cv::xfeatures2d;
using namespace std;

void readme();
int * histogram(Mat,Mat);
void TextWriter(string,int*,int);
double errorFactor(int *,int*);
/** @function main */
int main(int argc, char** argv)
{
	if (argc != 5)
	{
		readme(); return -1;
	}

	Mat img_1 = imread(argv[1], IMREAD_GRAYSCALE);
	Mat img_2 = imread(argv[2], IMREAD_GRAYSCALE);
	Mat img_3 = imread(argv[3], IMREAD_GRAYSCALE);
	Mat img_4 = imread(argv[4], IMREAD_GRAYSCALE);

	if (!img_1.data || !img_2.data||!img_3.data||!img_4.data)
	{
		std::cout << " --(!) Error reading images " << std::endl; return -1;
	}

	//-- Step 1: Detect the keypoints using SURF Detector
	int minHessianSIFT = 150;
	int minHessianSURF = 400;

	Ptr<SIFT> detector = SIFT::create(minHessianSIFT);
	vector<KeyPoint> keypoints_1, keypoints_2;
	detector->detect(img_1, keypoints_1);
	detector->detect(img_2, keypoints_2);
	//-- Draw keypoints
	Mat img_keypoints_1; Mat img_keypoints_2;
	drawKeypoints(img_1, keypoints_1, img_keypoints_1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	drawKeypoints(img_2, keypoints_2, img_keypoints_2, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	//-- Show detected (drawn) keypoints
	imshow("Keypoints 1", img_keypoints_1);
	imshow("Keypoints 2", img_keypoints_2);
	Mat descriptors_1, descriptors_2; 
	detector->compute(img_1, keypoints_1, descriptors_1);
	detector->compute(img_2, keypoints_2, descriptors_2);
	BFMatcher matcher; 
	vector<DMatch> matches; 
	matcher.match(descriptors_1,descriptors_2,matches);
	Mat matchDespcriptor;
	drawMatches(img_1,keypoints_1,img_2,keypoints_2,matches,matchDespcriptor);
	imshow("Descriptor Matching",matchDespcriptor);
	Ptr<SURF> surfDetector = SURF::create(minHessianSURF);
	vector<KeyPoint> surfKeypoints_1, surfKeypoints_2;
	surfDetector->detect(img_1, surfKeypoints_1);
	surfDetector->detect(img_2, surfKeypoints_2);
	/////////////////surf draw keypoints/////////
	Mat surfImg_keypoints_1; Mat surfImg_keypoints_2;
	drawKeypoints(img_1, surfKeypoints_1, surfImg_keypoints_1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	drawKeypoints(img_2, surfKeypoints_2, surfImg_keypoints_2, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	///////////////////////////////////
	imshow("Surf Keypoints 1", surfImg_keypoints_1);
	imshow(" Surf Keypoints 2", surfImg_keypoints_2);
	Mat surfDescriptors_1, surfDescriptors_2;
	surfDetector->compute(img_1, surfKeypoints_1, surfDescriptors_1);
	surfDetector->compute(img_2, surfKeypoints_2, surfDescriptors_2);
	BFMatcher surfMatcher; Mat surfMatchDespcriptor; vector<DMatch> surfMatches;
	surfMatcher.match(surfDescriptors_1, surfDescriptors_2, surfMatches);
	drawMatches(img_1, surfKeypoints_1, img_2, surfKeypoints_2, surfMatches, surfMatchDespcriptor);
	imshow("Surf Descriptor Matching", surfMatchDespcriptor);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	vector<KeyPoint> keypoints_3, keypoints_4;
	detector->detect(img_3, keypoints_3);
	detector->detect(img_4, keypoints_4);
	Mat img_keypoints_3; Mat img_keypoints_4;
	drawKeypoints(img_3, keypoints_3, img_keypoints_3, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	drawKeypoints(img_4, keypoints_4, img_keypoints_4, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	//-- Show detected (drawn) keypoints
	imshow("Keypoints 3", img_keypoints_3);
	imshow("Keypoints 4", img_keypoints_4);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	vector<KeyPoint> surfKeypoints_3, surfKeypoints_4;
	surfDetector->detect(img_3, surfKeypoints_3);
	surfDetector->detect(img_4, surfKeypoints_4);
	/////////////////surf draw keypoints/////////
	Mat surfImg_keypoints_3; Mat surfImg_keypoints_4;
	drawKeypoints(img_3, surfKeypoints_3, surfImg_keypoints_3, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	drawKeypoints(img_4, surfKeypoints_4, surfImg_keypoints_4, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	///////////////////////////////////
	imshow("Surf Keypoints 3", surfImg_keypoints_3);
	imshow(" Surf Keypoints 4", surfImg_keypoints_4);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Mat descriptors_3, descriptors_4;
	detector->compute(img_3, keypoints_3, descriptors_3);
	detector->compute(img_4, keypoints_4, descriptors_4);
	matcher.match(descriptors_1, descriptors_3, matches);
	drawMatches(img_1, keypoints_1, img_3, keypoints_3, matches, matchDespcriptor);
//	imshow("Descriptor Matching Sift Convertible_1 SUV", matchDespcriptor);
	matcher.match(descriptors_2, descriptors_4, matches);
	drawMatches(img_2, keypoints_2, img_4, keypoints_4, matches, matchDespcriptor);
	imshow("Descriptor Matching Sift Convertible_2 Truck", matchDespcriptor);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Mat surfDescriptors_3, surfDescriptors_4;
	surfDetector->compute(img_3, surfKeypoints_3, surfDescriptors_3);
	surfDetector->compute(img_4, surfKeypoints_4, surfDescriptors_4);
	surfMatcher.match(surfDescriptors_1, surfDescriptors_3, surfMatches);
	drawMatches(img_1, surfKeypoints_1, img_3, surfKeypoints_3, surfMatches, surfMatchDespcriptor);
//	imshow("Surf Descriptor Matching Convertible_1 SUV", surfMatchDespcriptor);
	surfMatcher.match(surfDescriptors_2, surfDescriptors_4, surfMatches);
	drawMatches(img_2, surfKeypoints_2, img_4, surfKeypoints_4, surfMatches, surfMatchDespcriptor);
	imshow("Surf Descriptor Matching Convertible_2 Truck", surfMatchDespcriptor);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///BAG of WORDS///////////////
	BOWKMeansTrainer BGOWORDS(8);
	BGOWORDS.add(descriptors_1);
	BGOWORDS.add(descriptors_3);
	BGOWORDS.add(descriptors_4);
	Mat vocabulary = BGOWORDS.cluster();
	//cout << vocabulary << endl;
	//cout << descriptors_1 << endl;
	//cout << descriptors_2.rows << endl;
	//cout << descriptors_3.rows << endl;
	//cout << descriptors_4.rows << endl;
	/////////////////////////////////////
	int *histCount1 = new int[vocabulary.rows];
	int *histCount2 = new int[vocabulary.rows];
	int *histCount3 = new int[vocabulary.rows];
	int *histCount4 = new int[vocabulary.rows];
	histCount1 = histogram(descriptors_1,vocabulary);
	histCount2 = histogram(descriptors_2, vocabulary);
	histCount3 = histogram(descriptors_3, vocabulary);
	histCount4 = histogram(descriptors_4, vocabulary);
	//cout << vocabulary << endl;
	TextWriter("C:\\Users\\amitp\\Desktop\\imageprocessing\\homeworks\\homework3_march26\\HW3_images\\P2\\3BAGWORDS\\histCount1.txt", histCount1, 8);
	TextWriter("C:\\Users\\amitp\\Desktop\\imageprocessing\\homeworks\\homework3_march26\\HW3_images\\P2\\3BAGWORDS\\histCount2.txt", histCount2, 8);
	TextWriter("C:\\Users\\amitp\\Desktop\\imageprocessing\\homeworks\\homework3_march26\\HW3_images\\P2\\3BAGWORDS\\histCount3.txt", histCount3, 8);
	TextWriter("C:\\Users\\amitp\\Desktop\\imageprocessing\\homeworks\\homework3_march26\\HW3_images\\P2\\3BAGWORDS\\histCount4.txt", histCount4, 8);
	double error1 = errorFactor(histCount1,histCount2);
	double error2 = errorFactor(histCount3, histCount2);
	double error3 = errorFactor(histCount4, histCount2);
	cout << error1 << endl;
	cout << error2 << endl;
	cout << error3 << endl;

	/*for (int i = 0; i < 8;i++) {
		cout << histCount1[i] << endl;
	}*/
	waitKey(0);

	return 0;
}

/** @function readme */
void readme()
{
	std::cout << " Usage: ./SURF_detector <img1> <img2>" << std::endl;
}
 int * histogram(Mat descriptor,Mat vocabulary) {
	double *euclideanD = new double[vocabulary.rows]; double tempD = 0.0; double temp = 0; int index = 0;
	int *histCount = new int[vocabulary.rows];
	for (int i = 0; i < vocabulary.rows;i++) {
		histCount[i] = 0;
	}
	for (int i = 0; i < descriptor.rows; i++) {
		for (int k = 0; k < vocabulary.rows;k++) {
			for (int j = 0; j < descriptor.cols; j++) {
				tempD += ((descriptor.at<float>(i,j)-vocabulary.at<float>(k,j))*(descriptor.at<float>(i, j) - vocabulary.at<float>(k, j)));
			}
			euclideanD[k] = (sqrt(tempD));
			tempD = 0.0;
		}
		temp = euclideanD[0]; index = 0;

		for (int k = 1; k<vocabulary.rows; k++) {
			if (temp>euclideanD[k]) {
				temp = euclideanD[k];
				index = k;
				//	cout<<index<<endl;
			}
		}	//cout<<"temp:"<<temp<<endl;
		histCount[index] += 1;
	//	cout << "The Texture" << i << " :is mapped to following index:" << mappedIndex[i] << endl;
		
	}
	return histCount;
}
 void TextWriter(string path,int *hist,int numRows) {
	 ofstream arrayData;
	arrayData.open(path);
	if (arrayData.is_open()) {
		for (int i = 0; i<numRows; i++) {
			arrayData << hist[i];
			arrayData << "\n";
		}
		arrayData.close();
	}
	else
	{
		cout << "unable to open file" << endl;
	}//original histogram to text file
 }
 double errorFactor(int *histImage,int *histConv2) {
	 double error = 0;
		 for (int j = 0; j < 8;j++) {
			 error += abs(histImage[j]-histConv2[j]);
		 }	 
		 error =error/8.0;
		 return error;
 }