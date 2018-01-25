/*
 * Homography_ImageOverLay_Dec.h
 *
 *  Created on: Feb 18, 2017
 *      Author: amitp
 */

#ifndef SRC_HOMOGRAPHY_IMAGEOVERLAY_DEC_H_
#define SRC_HOMOGRAPHY_IMAGEOVERLAY_DEC_H_
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
class Homography{
	int height=0,width=0,BytesPerPixel=0;
public:
	//constructor//
	Homography();
	Homography(const Homography &); // copy constructor
	Homography & operator=(const Homography &); // copy operator
	~Homography();  // destructor

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
			unsigned char*** HomographyLogic(unsigned char ***,unsigned char***,int,int,int,int,int);


};




#endif /* SRC_HOMOGRAPHY_IMAGEOVERLAY_DEC_H_ */
