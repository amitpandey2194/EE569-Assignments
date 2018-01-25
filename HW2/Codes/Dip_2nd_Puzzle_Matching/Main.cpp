/*
 * Main.cpp
 *
 *  Created on: Feb 15, 2017
 *      Author: amitp
 */
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "PuzzleMatching.h"
using namespace std;
int main (int argc, const char *argv[])
{
	int height,width,BytesPerPixel,heightMain,widthMain;
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
					height = atoi(argv[5]);
					width = atoi(argv[6]);
					heightMain=atoi(argv[7]);
					widthMain=atoi(argv[8]);
				}
			}
			cout<<"bytesPerPixel is:"<<BytesPerPixel<<endl;
			//Input read for height,width,BytesPerPixel///
			PuzzleMatchingDec obj;
			unsigned char *** Image=obj.FileRead(argv,1,height,width,BytesPerPixel);
			unsigned char*** HillaryImage=obj.FileRead(argv,2,heightMain,widthMain,BytesPerPixel);
			unsigned char ***TrumpImage=obj.FileRead(argv,3,heightMain,widthMain,3);
			int * TrumpCoor=obj.CoordinatesMainImage(TrumpImage,heightMain,widthMain,BytesPerPixel);
			int * HillCorArray=obj.CoordinatesMainImage(HillaryImage,heightMain,widthMain,BytesPerPixel);
			obj.TranslationPieces(argv,Image,HillaryImage,HillCorArray,TrumpImage,TrumpCoor,heightMain,widthMain,height,width,BytesPerPixel);


			return 0;
}





