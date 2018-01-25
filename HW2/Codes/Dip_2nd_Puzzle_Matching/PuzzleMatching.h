/*
 * PuzzleMatching.h
 *
 *  Created on: Feb 15, 2017
 *      Author: amitp
 */

#ifndef PUZZLEMATCHING_H_
#define PUZZLEMATCHING_H_
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
class PuzzleMatchingDec{
	int height=0,width=0,BytesPerPixel=0;
public:
	//constructor//
	PuzzleMatchingDec();
	PuzzleMatchingDec(const PuzzleMatchingDec &); // copy constructor
	PuzzleMatchingDec & operator=(const PuzzleMatchingDec &); // copy operator
	~PuzzleMatchingDec();  // destructor

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
			int * CoordinatesMainImage(unsigned char ***,int,int,int);
			int * CoordinatesStraightImage(unsigned char***,int,int,int);
			void TranslationPieces(const char *[],unsigned char***,unsigned char***,int *,unsigned char***,int *,int,int,int,int,int);

};





#endif /* PUZZLEMATCHING_H_ */
