/*
 * Main.cpp
 *
 *  Created on: Feb 17, 2017
 *      Author: amitp
 */
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "LinearWarping.h"
using namespace std;
int main (int argc, const char *argv[])
{
	int height,width,BytesPerPixel;
	//Input read for height,width,BytesPerPixel///
	if (argc < 3){
			cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
			cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] height width" << endl;
			return 0;
		}

		// Check if image is grayscale or color
		if (argc < 4){
			BytesPerPixel = 1; // default is grey image
		}
		else {
			BytesPerPixel = atoi(argv[3]);
			// Check if size is specified
			if (argc >= 5){
				height = atoi(argv[4]);
				width = atoi(argv[5]);
			}
		}
		cout<<"bytesPerPixel is:"<<BytesPerPixel<<endl;
			//Input read for height,width,BytesPerPixel///
			LinearWarping obj;
			unsigned char *** Image=obj.FileRead(argv,1,height,width,BytesPerPixel);
			unsigned char ***OutputImage=obj.LinearWarpingLogic(Image,height,width,BytesPerPixel);
			unsigned char *OutputImage1_d=obj.DynamicMemoryAllocation3d_2_1d(OutputImage,height,width,BytesPerPixel);
			obj.FileWrite(argv,OutputImage1_d,2,height,width,BytesPerPixel);

			return 0;
}


