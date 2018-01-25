/*
 * Main.cpp
 *
 *  Created on: Feb 22, 2017
 *      Author: amitp
 */
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "countingGame.h"
#include <fstream>
using namespace std;
int main (int argc, const char *argv[])
{
	int height,width;
	string *uncond=new string[364];
	ifstream file("C:\\Users\\amitp\\Desktop\\imageprocessing\\homeworks\\homework2_feb26\\LookUP_Table_2.txt");
	if(file.is_open())
	{


		for(int i = 0; i < 364; ++i)
		{
			file >> uncond[i];
		}
	}//reading the pattern table;
	file.close();
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

	CountingGame obj;

	unsigned char ** InputImage=obj.FileRead(argv,1,height,width);
	unsigned char **NormInputImage=obj.DynamicMemoryAllocation2d(height,width);
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			NormInputImage[i][j]=InputImage[i][j];
		}
	}

	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			NormInputImage[i][j]=((NormInputImage[i][j]*1.0)/255.0);
			if(NormInputImage[i][j]==1){
				NormInputImage[i][j]=0;
			}
			else if(NormInputImage[i][j]==0){
				NormInputImage[i][j]=1;
			}
		}
	}//Normalizing the Input to 0 & 1;
	unsigned char ** MArray=obj.CountingGameLogic_FirstStage(NormInputImage,height,width);
	unsigned char** OutPutImage=obj.CountingGameLogic_SecondStage(MArray,NormInputImage,height,width,uncond);

			int countnew=0;int countOld=0;
				for(int i=0;i<height;i++){
					for(int j=0;j<width;j++){
						if(InputImage[i][j]>0){
							countOld++;
						}
						if(OutPutImage[i][j]>0){
							countnew++;
						}
					}
				}

				countOld=0;countnew=0;
	unsigned char **TempInput=obj.DynamicMemoryAllocation2d(height,width);int count=1;bool status=false;
	while(count<15){
		for(int i=0;i<height;i++){
			for(int j=0;j<width;j++){
				TempInput[i][j]=((OutPutImage[i][j]*1.0)/255.0);
			}
		}
		MArray=obj.CountingGameLogic_FirstStage(TempInput,height,width);
		OutPutImage=obj.CountingGameLogic_SecondStage(MArray,TempInput,height,width,uncond);
		count++;
	}
	//printf("number of Iterations:%d\n",count);
	int *array=new int[18];
	array=obj.count_Holes(OutPutImage,height,width);
	int targetColor=0;int replacementColor=255;int Ycoor,Xcoor;int counter=array[18];unsigned char** OutPutImageFloodFill=obj.DynamicMemoryAllocation2d(height,width);
	for(int i=0;i<(2*counter);i+=2){
		Ycoor=array[i]; Xcoor=array[i+1];
		OutPutImageFloodFill=obj.FloodFillCaller(InputImage,Ycoor,Xcoor,targetColor,replacementColor,height,width);
		InputImage=OutPutImageFloodFill;

	}

	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			NormInputImage[i][j]=InputImage[i][j];
		}
	}

	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			NormInputImage[i][j]=((NormInputImage[i][j]*1.0)/255.0);
		}
	}//Normalizing the Input to 0 & 1;
	MArray=obj.CountingGameLogic_FirstStage(NormInputImage,height,width);
	OutPutImage=obj.CountingGameLogic_SecondStage(MArray,NormInputImage,height,width,uncond);
			 countnew=0; countOld=0;
				for(int i=0;i<height;i++){
					for(int j=0;j<width;j++){
						if(InputImage[i][j]>0){
							countOld++;
						}
						if(OutPutImage[i][j]>0){
							countnew++;
						}
					}
				}

				countOld=0;countnew=0;
	count=1;status=false;
	int sizeOfArray=0;
	while(!(status)){
		for(int i=0;i<height;i++){
			for(int j=0;j<width;j++){
				TempInput[i][j]=((OutPutImage[i][j]*1.0)/255.0);
			}
		}
		MArray=obj.CountingGameLogic_FirstStage(TempInput,height,width);
		OutPutImage=obj.CountingGameLogic_SecondStage(MArray,TempInput,height,width,uncond);
					for(int i=0;i<height;i++){
						for(int j=0;j<width;j++){
							if(TempInput[i][j]>0){
								countOld++;
							}
							if(OutPutImage[i][j]>0){
								countnew++;
							}
						}
					}
	//				printf("number of white pixels in old:%d\n",countOld);
	//				printf("number of white pixels in new:%d\n",countnew);
					if(countOld==countnew){
						status=true;
						printf("number of white objects:%d\n",countnew);
						sizeOfArray=countnew;
					}
					countOld=0;countnew=0;
					count++;
	};
	unsigned char *OutputImage1D=obj.DynamicMemoryAllocation2d_2_1d(OutPutImage,height,width);
		obj.FileWrite(argv,OutputImage1D,2,height,width);

	int *arrayCoor=new int[31];int arrayCounter=0; arrayCoor[30]=sizeOfArray;
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			if(OutPutImage[i][j]==255){
				arrayCoor[arrayCounter]=i;arrayCoor[arrayCounter+1]=j;
				//printf("coordinates y and x :%d,%d\n",i,j);
				arrayCounter+=2;
			}
		}
	}
obj.CountOfSquares_Circles(InputImage,height,width,arrayCoor);









	return 0;
}





