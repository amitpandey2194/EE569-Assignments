/*
 * Main.cpp
 *
 *  Created on: Feb 18, 2017
 *      Author: amitp
 */
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "Homography_ImageOverLay_Dec.h"
using namespace std;
int main (int argc, const char *argv[])
{
	int heightSC,widthSC,BytesPerPixel,heightF,widthF;
	//Input read for height,width,BytesPerPixel///
	if (argc < 4){
			cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
			cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] height width" << endl;
			return 0;
		}

		// Check if image is grayscale or color
		if (argc < 5){
			BytesPerPixel = 1; // default is grey image
		}
		else {
			BytesPerPixel = atoi(argv[4]);
			// Check if size is specified
			if (argc >= 6){
				heightSC = atoi(argv[5]);
				widthSC = atoi(argv[6]);
				heightF = atoi(argv[7]);
				widthF = atoi(argv[8]);
			}
		}
		cout<<"bytesPerPixel is:"<<BytesPerPixel<<endl;
			//Input read for height,width,BytesPerPixel///
			Homography obj;
			unsigned char *** Trojan=obj.FileRead(argv,1,heightSC,widthSC,BytesPerPixel);
			unsigned char *** field=obj.FileRead(argv,2,heightF,widthF,BytesPerPixel);
			unsigned char ***OutputImage=obj.HomographyLogic(Trojan,field,heightSC,widthSC,heightF,widthF,BytesPerPixel);
			unsigned char *OutputImage1_d=obj.DynamicMemoryAllocation3d_2_1d(OutputImage,heightF,widthF,BytesPerPixel);
			obj.FileWrite(argv,OutputImage1_d,3,heightF,widthF,BytesPerPixel);
			return 0;
}





