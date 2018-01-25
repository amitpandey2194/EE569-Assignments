/*
 * Main.cpp
 *
 *  Created on: Feb 24, 2017
 *      Author: amitp
 */
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "Ditheringdec.h"
#include <fstream>
using namespace std;

int main (int argc, const char *argv[])
{
	int height,width;

	//Input read for height,width,BytesPerPixel///
	if (argc < 3){
			cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
			cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] height width" << endl;
			return 0;
		}

		// Check if image is grayscale or color

			// Check if size is specified
			if (argc >= 4){
				height = atoi(argv[3]);
				width = atoi(argv[4]);
		}

			Dithering obj;
		unsigned char ** InputImage=obj.FileRead(argv,1,height,width);
		unsigned char ** OutPutImage=obj.DitheringLogic(InputImage,height,width);
		unsigned char *OutputImage1D=obj.DynamicMemoryAllocation2d_2_1d(OutPutImage,height,width);
		obj.FileWrite(argv,OutputImage1D,2,height,width);



			return 0;
}



