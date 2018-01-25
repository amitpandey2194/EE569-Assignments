/*
 * skeletonizing.h
 *
 *  Created on: Feb 23, 2017
 *      Author: amitp
 */

#ifndef SKELETONIZING_H_
#define SKELETONIZING_H_
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include<string>
using namespace std;
class Skeletonizing{
	int height=0,width=0,BytesPerPixel=0;
public:
	//constructor//
	Skeletonizing();
	Skeletonizing(const Skeletonizing &); // copy constructor
	Skeletonizing & operator=(const Skeletonizing &); // copy operator
	~Skeletonizing();  // destructor

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
			unsigned char * DynamicMemoryAllocation2d_2_1d(unsigned char **,int,int);
			unsigned char ** DynamicMemoryAllocation2d(int,int);
			unsigned char ** DynamicMemoryAllocation1d_2_2d(unsigned char *,int,int);
			unsigned char ** FileRead(const char*[],int,int,int);
			bool FileWrite(const char*[],unsigned char *,int,int,int);
			unsigned char** SkeletonizingLogic_FirstStage(unsigned char **,int,int);
			int compareString(string *,string,int);
			unsigned char ** SkeletonizingLogic_SecondStage(unsigned char**,unsigned char**,int,int,string*);


};






#endif /* SKELETONIZING_H_ */
