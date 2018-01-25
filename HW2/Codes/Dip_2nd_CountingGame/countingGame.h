/*
 * countingGame.h
 *
 *  Created on: Feb 22, 2017
 *      Author: amitp
 */

#ifndef COUNTINGGAME_H_
#define COUNTINGGAME_H_
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include<string>
using namespace std;
class CountingGame{
	int height=0,width=0,BytesPerPixel=0;
public:
	//constructor//
	CountingGame();
	CountingGame(const CountingGame &); // copy constructor
	CountingGame & operator=(const CountingGame &); // copy operator
	~CountingGame();  // destructor

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
			unsigned char** CountingGameLogic_FirstStage(unsigned char **,int,int);
			int compareString(string *,string,int);
			unsigned char ** CountingGameLogic_SecondStage(unsigned char**,unsigned char**,int,int,string*);
			int * count_Holes(unsigned char**,int,int);
			unsigned char ** FloodFillCaller(unsigned char**,int,int,int,int,int,int);
			int CountOfSquares_Circles(unsigned char**,int,int,int*);

};






#endif /* COUNTINGGAME_H_ */
