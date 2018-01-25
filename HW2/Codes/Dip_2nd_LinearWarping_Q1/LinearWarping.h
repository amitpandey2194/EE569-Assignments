/*
 * LinearWarping.h
 *
 *  Created on: Feb 17, 2017
 *      Author: amitp
 */

#ifndef LINEARWARPING_H_
#define LINEARWARPING_H_
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
class LinearWarping{
	int height=0,width=0,BytesPerPixel=0;
public:
	//constructor//
	LinearWarping();
	LinearWarping(const LinearWarping &); // copy constructor
	LinearWarping & operator=(const LinearWarping &); // copy operator
	~LinearWarping();  // destructor

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
			unsigned char * DynamicMemoryAllocation1d(int,int,int);
			unsigned char * DynamicMemoryAllocation3d_2_1d(unsigned char ***,int,int,int);
			unsigned char *** DynamicMemoryAllocation3d(int,int,int);
			unsigned char *** DynamicMemoryAllocation1d_2_3d(unsigned char *,int,int,int);
			unsigned char *** FileRead(const char*[],int,int,int,int);
			bool FileWrite(const char*[],unsigned char *,int,int,int,int);
			unsigned char*** LinearWarpingLogic(unsigned char ***,int,int,int);


};





#endif /* LINEARWARPING_H_ */
