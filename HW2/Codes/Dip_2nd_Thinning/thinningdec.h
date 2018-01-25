/*
 * thinning.h
 *
 *  Created on: Feb 22, 2017
 *      Author: amitp
 */

#ifndef THINNINGDEC_H_
#define THINNINGDEC_H_
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include<string>
using namespace std;
class Thinning{
	int height=0,width=0,BytesPerPixel=0;
public:
	//constructor//
	Thinning();
	Thinning(const Thinning &); // copy constructor
	Thinning & operator=(const Thinning &); // copy operator
	~Thinning();  // destructor

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
			unsigned char** ThinningLogic_FirstStage(unsigned char **,int,int);
			int compareString(string *,string,int);
			unsigned char ** ThinningLogic_SecondStage(unsigned char**,unsigned char**,int,int,string*);


};










#endif /* THINNINGDEC_H_ */
