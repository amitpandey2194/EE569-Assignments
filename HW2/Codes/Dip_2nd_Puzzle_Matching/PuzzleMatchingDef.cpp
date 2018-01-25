/*
 * PuzzleMatchingDef.cpp
 *
 *  Created on: Feb 15, 2017
 *      Author: amitp
 */
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "PuzzleMatching.h"
#include<string>
using namespace std;
PuzzleMatchingDec::PuzzleMatchingDec(){
	puts("constructor");
}

PuzzleMatchingDec::PuzzleMatchingDec(const PuzzleMatchingDec & a){
	puts("copy constructor");
	height=a.height;
	width=a.width;
	BytesPerPixel=a.BytesPerPixel;
}
PuzzleMatchingDec::~PuzzleMatchingDec() {
	printf("destructor: height:%d,width:%d and BytesPerPixel:%d\n",height,width,BytesPerPixel );
}

PuzzleMatchingDec & PuzzleMatchingDec::operator=(const PuzzleMatchingDec & o) {
	puts("assignment operator");
	if(this != &o) {
		height = o.height;
		width = o.width;
		BytesPerPixel = o.BytesPerPixel;
	}
	return *this;
}

unsigned char * PuzzleMatchingDec::DynamicMemoryAllocation1d(int height,int width,int BytesPerPixel){
	unsigned char * ImagePointer=new unsigned char [height*width*BytesPerPixel];
	return ImagePointer;

}
unsigned char *** PuzzleMatchingDec::DynamicMemoryAllocation3d(int height,int width,int BytesPerPixel){
	unsigned char *** ImagePointer=new unsigned char **[height];
	for(int i=0;i<height;i++){
		ImagePointer[i]=new unsigned char *[width];
		for(int j=0;j<width;j++){
			ImagePointer[i][j]=new unsigned char[BytesPerPixel];
		}
	}
	return ImagePointer;

}
unsigned char *** PuzzleMatchingDec:: DynamicMemoryAllocation1d_2_3d(unsigned char * pointer,int height,int width,int BytesPerPixel){
	unsigned char ***Image=new unsigned char **[height];
	for(int i=0;i<height;i++){
		Image[i]=new unsigned char *[width];
		for(int j=0;j<width;j++){
			Image[i][j]=new unsigned char[BytesPerPixel];
		}
	}
	int index=0;
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			for(int k=0;k<3;k++){
				Image[i][j][k]=pointer[index];
				index++;
			}
		}
	}

	return Image;
}
unsigned char * PuzzleMatchingDec::DynamicMemoryAllocation3d_2_1d(unsigned char *** pointer,int height,int width,int BytesPerPixel){
	unsigned char *Image=new unsigned char[height*width*BytesPerPixel];
	int index=0;
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			for(int k=0;k<3;k++){
				Image[index]=pointer[i][j][k];
				index++;
			}
		}
	}
	return Image;
}
unsigned char *** PuzzleMatchingDec::FileRead(const char *argv[],int index,int height,int width,int BytesPerPixel){
	FILE *file;
	unsigned char*Image=DynamicMemoryAllocation1d(height,width,BytesPerPixel);
	if (!(file=fopen(argv[index],"rb"))) {
		cout << "Cannot open file: " << argv[index] <<endl;
		exit(1);
	}
	fread(Image, sizeof(unsigned char), height*width*BytesPerPixel, file);
	fclose(file);
	unsigned char *** ImagePointer=DynamicMemoryAllocation1d_2_3d(Image,height,width,BytesPerPixel);
	file=nullptr;delete [] Image;
	return ImagePointer;

}
bool PuzzleMatchingDec::FileWrite(const char *argv[],unsigned char *Image,int index,int height,int width,int BytesPerPixel){
	FILE *file; bool status=false;int success;
	if (!(file=fopen(argv[index],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}

	success=fwrite(Image, sizeof(unsigned char), height*width*BytesPerPixel, file);
	fclose(file);
	if(success==height*width*BytesPerPixel){
		status=true;
	}
	return status;

}
int * PuzzleMatchingDec::CoordinatesMainImage(unsigned char ***OriginalImage,int height,int width,int BytesPerPixel){
	int coorX_1_1,coorY_1_1,coorX_1_2,coorY_1_2,coorX_1_3,coorY_1_3,coorX_1_4,coorY_1_4;
	int *array=new int[8];
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			if((OriginalImage[i][j][0]==255 && OriginalImage[i][j][1]==255 && OriginalImage[i][j][2]==255)){
				coorX_1_1=j;coorY_1_1=i;
				int k=i;
				while((OriginalImage[k][j][0]==255 && OriginalImage[k][j][1]==255 && OriginalImage[k][j][2]==255)){
					k++;
				}
				coorX_1_3=j;coorY_1_3=k-1;
				j=width;i=height;
			}
		}
	}////1st and 3rd coordinates found///
	for(int i=0;i<height;i++){
		for(int j=width-1;j>=0;j--){
			if((OriginalImage[i][j][0]==255 && OriginalImage[i][j][1]==255 && OriginalImage[i][j][2]==255)){
				coorX_1_2=j;coorY_1_2=i;
				int k=i;
				while((OriginalImage[k][j][0]==255 && OriginalImage[k][j][1]==255 && OriginalImage[k][j][2]==255)){
					k++;
				}
				coorX_1_4=j;coorY_1_4=k-1;
				j=0;i=height;
			}
		}
	}///2nd and fourth coordinate///

	printf("the first coordinates are : (%d,%d)\n the second coordinates are:(%d,%d)\n "
			"the third coordinates are:(%d,%d)\n the fourth coordinates are:(%d,%d)\n",coorX_1_1,coorY_1_1,coorX_1_2,coorY_1_2,
			coorX_1_3,coorY_1_3,coorX_1_4,coorY_1_4);
	array[0]=coorX_1_1;array[1]=coorY_1_1;array[2]=coorX_1_2;array[3]=coorY_1_2;array[4]=coorX_1_3;array[5]=coorY_1_3;
	array[6]=coorX_1_4;array[7]=coorY_1_4;
	return array;
}
int * PuzzleMatchingDec::CoordinatesStraightImage(unsigned char***StraightImage,int height,int width,int BytesPerPixel){
	int coorX_1_1=0,coorY_1_1=0,coorX_1_2=0,coorY_1_2=0,coorX_1_3=0,coorY_1_3=0,coorX_1_4=0,coorY_1_4=0;
	int *array=new int[8];
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			if(!((StraightImage[i][j][0]<=255 && StraightImage[i][j][0]>=243) && (StraightImage[i][j][1]<=255 && StraightImage[i][j][1]>=243) && (StraightImage[i][j][2]<=255 && StraightImage[i][j][2]>=243))){
				coorX_1_1=j;coorY_1_1=i;
				j=width;i=height;
			}
		}
	}////1st coordinates found///
	for(int j=width-1;j>=0;j-- ){
		for(int i=0;i<height;i++){
			if(!((StraightImage[i][j][0]<=255 && StraightImage[i][j][0]>=243) && (StraightImage[i][j][1]<=255 && StraightImage[i][j][1]>=243) && (StraightImage[i][j][2]<=255 && StraightImage[i][j][2]>=243))){
				coorX_1_2=j;coorY_1_2=i;
				j=0;i=height;
			}
		}
	}///2nd coordinate///
	for(int i=height-1;i>=0;i-- ){
		for(int j=0;j<width;j++){
			if(!((StraightImage[i][j][0]<=255 && StraightImage[i][j][0]>=243) && (StraightImage[i][j][1]<=255 && StraightImage[i][j][1]>=243) && (StraightImage[i][j][2]<=255 && StraightImage[i][j][2]>=243))){
				coorX_1_3=j;coorY_1_3=i;
				j=width;i=0;
			}
		}
	}///3rd coordinate///
	for(int j=width-1;j>=0;j-- ){
		for(int i=height-1;i>=0;i--){
			if(!((StraightImage[i][j][0]<=255 && StraightImage[i][j][0]>=243) && (StraightImage[i][j][1]<=255 && StraightImage[i][j][1]>=243) && (StraightImage[i][j][2]<=255 && StraightImage[i][j][2]>=243))){
				coorX_1_4=j;coorY_1_4=i;
				j=0;i=0;
			}
		}
	}///4rd coordinate///



	printf("the first coordinates of straight image are : (%d,%d)\n the second coordinates of the straight image are:(%d,%d)\n "
			"the third coordinates of the straight image are:(%d,%d)\n the fourth coordinates of the straight image are:(%d,%d)\n",coorX_1_1,coorY_1_1,coorX_1_2,coorY_1_2,
			coorX_1_3,coorY_1_3,coorX_1_4,coorY_1_4);
	array[0]=coorX_1_1;array[1]=coorY_1_1;array[2]=coorX_1_2;array[3]=coorY_1_2;array[4]=coorX_1_3;array[5]=coorY_1_3;
	array[6]=coorX_1_4;array[7]=coorY_1_4;
	return array;
}
void PuzzleMatchingDec::TranslationPieces(const char *argv[],unsigned char ***PieceImage,unsigned char ***Hillary,int *HillaryCorArray,unsigned char*** Trump,int *TrumpCoor,int heightMain,int widthMain,int height,int width,int BytesPerPixel){
	unsigned char*** FinalImage=DynamicMemoryAllocation3d(heightMain,widthMain,3);
	unsigned char*** FinalImageTrump=DynamicMemoryAllocation3d(heightMain,widthMain,3);
	unsigned char *** Piece_1=DynamicMemoryAllocation3d(height/2,width/2,BytesPerPixel);
	unsigned char *** Piece_2=DynamicMemoryAllocation3d(height/2,width/2,BytesPerPixel);
	int coorX_1_1,coorY_1_1,coorX_1_2,coorY_1_2,coorX_1_3,coorY_1_3,coorX_1_4,coorY_1_4;
	int coorX_2_1,coorY_2_1,coorX_2_2,coorY_2_2,coorX_2_3,coorY_2_3,coorX_2_4,coorY_2_4;
	//first and second piece out off the Main Piece Image//
	for(int i=0;i<height/2;i++){
		for(int j=0;j<width/2;j++){
			for(int k=0;k<3;k++){
				Piece_1[i][j][k]=PieceImage[i][j][k];
				Piece_2[i][j][k]=PieceImage[i+250][j+250][k];
			}
		}
	}//first and second piece out off the Main Piece Image//

	// Identifying the First of the First Piece and Second coordinates of the Second Piece//

	for(int i=0;i<height/2;i++){
		for(int j=0;j<width/2;j++){
			if(!(Piece_1[i][j][0]==255 && Piece_1[i][j][1]==255 && Piece_1[i][j][2]==255 )){
				coorX_1_1=j;coorY_1_1=i;
				j=width/2;i=height/2;/// to break the loop///
			}
		}
	}// Identifying the First of the First Piece

	// Identifying the Second of the First Piece
	for(int j=(width/2-1);j>=0;j--){
		for(int i=0;i<height/2;i++){
			if(!(Piece_1[i][j][0]==255 && Piece_1[i][j][1]==255 && Piece_1[i][j][2]==255 )){
				coorX_1_2=j;coorY_1_2=i;
				j=0;i=height/2;/// to break the loop///
			}
		}
	}// Identifying the Second of the First Piece

	// Identifying the third of the First Piece
	for(int j=0;j<width/2;j++){
		for(int i=(height/2-1);i>=0;i--){
			if(!(Piece_1[i][j][0]==255 && Piece_1[i][j][1]==255 && Piece_1[i][j][2]==255 )){
				coorX_1_3=j;coorY_1_3=i;
				j=width/2;i=0;/// to break the loop///
			}
		}
	}	// Identifying the third of the First Piece

	// Identifying the fourth of the First Piece
	for(int i=(height/2-1);i>=0;i--){
		for(int j=(width/2-1);j>=0;j--){
			if(!(Piece_1[i][j][0]==255 && Piece_1[i][j][1]==255 && Piece_1[i][j][2]==255 )){
				coorX_1_4=j;coorY_1_4=i;
				j=0;i=0;/// to break the loop///
			}
		}
	}	// Identifying the fourth of the First Piece

	// Second Piece///
	// Identifying the First coordinates of the Second Piece//
	for(int j=0;j<width/2;j++ ){
		for(int i=0;i<height/2;i++){
			if(!(Piece_2[i][j][0]==255 && Piece_2[i][j][1]==255 && Piece_2[i][j][2]==255 )){
				coorX_2_1=j;coorY_2_1=i;
				j=width/2;i=height/2;/// to break the loop///
			}
		}
	}// Identifying the First of the First Piece and Second coordinates of the Second Piece//

	// Identifying the Second coordinates of the Second Piece//
	for(int i=0;i<height/2;i++ ){
		for(int j=(width/2-1);j>=0;j--){
			if(!(Piece_2[i][j][0]==255 && Piece_2[i][j][1]==255 && Piece_2[i][j][2]==255 )){
				coorX_2_2=j;coorY_2_2=i;
				j=0;i=height/2;/// to break the loop///
			}
		}
	}// Identifying the Second  coordinates of the Second Piece//

	// Identifying the third of the Second Piece//
	for(int i=(height/2-1);i>=0;i--){
		for(int j=0;j<width/2;j++){
			if(!(Piece_2[i][j][0]==255 && Piece_2[i][j][1]==255 && Piece_2[i][j][2]==255 )){
				coorX_2_3=j;coorY_2_3=i;
				j=width/2;i=0;/// to break the loop///
			}
		}
	}	// Identifying the third coordinates of the Second Piece//

	// Identifying the fourth coordinates of the Second Piece//
	for(int j=(width/2-1);j>=0;j--){
		for(int i=(height/2-1);i>=0;i--){
			if(!(Piece_2[i][j][0]==255 && Piece_2[i][j][1]==255 && Piece_2[i][j][2]==255 )){
				coorX_2_4=j;coorY_2_4=i;
				j=0;i=0;/// to break the loop///
			}
		}
	}	// Identifying the fourth coordinates of the Second Piece//
		printf("the hillary piece first coordinates are : (%d,%d)\n the hillary piece second coordinates are:(%d,%d)\n "
				"the hillary piece third coordinates are:(%d,%d)\n the hillary piece fourth coordinates are:(%d,%d)\n",coorX_1_1,coorY_1_1,coorX_1_2,coorY_1_2,
				coorX_1_3,coorY_1_3,coorX_1_4,coorY_1_4);

		printf("Trump   the first coordinates are : (%d,%d)\n the second coordinates are:(%d,%d)\n "
				"the third coordinates are:(%d,%d)\n the fourth coordinates are:(%d,%d)\n",coorX_2_1,coorY_2_1,coorX_2_2,coorY_2_2,
				coorX_2_3,coorY_2_3,coorX_2_4,coorY_2_4);

	unsigned char ***Piece1_Rotated=DynamicMemoryAllocation3d(height/2,width/2,BytesPerPixel);
	double slope_piece_1;
	slope_piece_1=((coorY_1_2-coorY_1_1)*1.0)/(coorX_1_2-coorX_1_1);
	double theta;
	theta=atan(slope_piece_1);
	printf("%f\n",theta);
	double y,x,del_x,del_y,weight_1,weight_2,weight_3,weight_4;int p,q;
	for(int i=0;i<height/2;i++){
		for(int j=0;j<width/2;j++){
			y=j*sin(theta)+i*cos(theta);
			x=(j*cos(theta))-i*sin(theta);
			if((y<(height/2) && y>=0) && (x<(width/2) && x>=0)){
				p=floor(y);	q=floor(x);del_x=x-q;del_y=y-p;weight_1=(1-del_x)*(1-del_y);weight_2=del_x*(1-del_y);
				weight_3=del_y*(1-del_x);weight_4=del_x*del_y;//four weights
				if(p+1<height/2 && q+1<width/2){
					for(int k=0;k<3;k++){
						Piece1_Rotated[i][j][k]=weight_1*Piece_1[p][q][k]
																	   +weight_2*Piece_1[p][q+1][k]
																								 +weight_3*Piece_1[p+1][q][k]
																														   +weight_4*Piece_1[p+1][q+1][k];
					}
				}
				else{
					for(int k=0;k<3;k++){
						Piece1_Rotated[i][j][k]=Piece_1[p][q][k];
					}
				}
			}
			else{
				for(int k=0;k<3;k++){
					Piece1_Rotated[i][j][k]=255;
				}
			}
		}
	}

	int * array=new int[8];
	array=CoordinatesStraightImage(Piece1_Rotated,height/2,width/2,BytesPerPixel);
	int newH=(array[7]-array[1]+1);
	int newW=(array[6]-array[0]+1);
	unsigned char ***tempImagePointer=DynamicMemoryAllocation3d(newH,newW,BytesPerPixel);
	for(int i=0;i<newH;i++){
		for(int j=0;j<newW;j++){
			for(int k=0;k<3;k++){
				tempImagePointer[i][j][k]=Piece1_Rotated[i+array[1]][j+array[0]][k];
			}

		}
	}
	int hillaryH=HillaryCorArray[2]-HillaryCorArray[0]+1,hillaryW=HillaryCorArray[5]-HillaryCorArray[1]+1;
	unsigned char ***ScalingImage=DynamicMemoryAllocation3d(hillaryH+4,hillaryW+4,BytesPerPixel);
	double factorX,factorY,y_inv,x_inv;
	factorY=(((hillaryH+4)*1.0)/(newH));
	factorX=(((hillaryW+4)*1.0)/(newW));
//	printf("new height:%d,newWidth:%d",newH,newW);
	for(int i=0;i<hillaryH+4;i++){
		y_inv=i/factorY;
		for(int j=0;j<hillaryW+4;j++){
			x_inv=j/factorX;
			p=int(floor(y_inv));
			q=int(floor(x_inv));
			del_x=x_inv-q;
			del_y=y_inv-p;
			weight_1=(1-del_x)*(1-del_y);
			weight_2=del_x*(1-del_y);
			weight_3=del_y*(1-del_x);
			weight_4=del_x*del_y;//four weights calculated;
			if(p+1<newH && q+1<newW){
				for(int k=0;k<3;k++){
					ScalingImage[i][j][k]=weight_1*tempImagePointer[p][q][k]
													 +weight_2*tempImagePointer[p][q+1][k]
															 +weight_3*tempImagePointer[p+1][q][k]
																   +weight_4*tempImagePointer[p+1][q+1][k];
				}
			}
			else{
				for(int k=0;k<3;k++){
					ScalingImage[i][j][k]=tempImagePointer[p][q][k];
				}
			}
		}
	}
//
//		for(int j=0;j<hillaryW;j++){
//			for(int k=0;k<3;k++){
//				ScalingImage[0][j][k]=ScalingImage[1][j][k];
//				//ScalingImage[1][j][k]=ScalingImage[2][j][k];
//				//ScalingImage[2][j][k]=ScalingImage[3][j][k];
//				ScalingImage[hillaryH-1][j][k]=ScalingImage[hillaryH-2][j][k];
//				//ScalingImage[hillaryH-1][j][k]=ScalingImage[hillaryH-3][j][k];
//				//ScalingImage[hillaryH-3][j][k]=ScalingImage[hillaryH-4][j][k];
//			}
//		}
//		for(int i=0;i<hillaryH;i++){
//					for(int k=0;k<3;k++){
//						ScalingImage[i][0][k]=ScalingImage[i][1][k];
//						//ScalingImage[i][1][k]=ScalingImage[i][2][k];
//						//ScalingImage[i][2][k]=ScalingImage[i][3][k];
//						ScalingImage[i][hillaryH-1][k]=ScalingImage[i][hillaryW-2][k];
//						//ScalingImage[i][hillaryH-2][k]=ScalingImage[i][hillaryW-3][k];
//						//ScalingImage[i][hillaryH-3][k]=ScalingImage[i][hillaryW-4][k];
//					}
//				}

FinalImage=Hillary;
for(int i=2;i<hillaryH+2;i++){
	for(int j=2;j<hillaryW+2;j++){
		for(int k=0;k<3;k++){
			FinalImage[i+135-2][j+173-2][k]=ScalingImage[i][j][k];
//			if(j==hillaryW-1){
//				FinalImage[i+135][j+173+1][k]=ScalingImage[i][j][k];
//			}
//			if(i==hillaryH-1){
//				FinalImage[i+135+1][j+173][k]=ScalingImage[i][j][k];
//			}
		}
	}
}
/////take care of the edge on hillary image////

///Trump///
double slope_2=((coorY_2_2-coorY_2_1)*1.0)/(coorX_2_2-coorX_2_1);
double pi =3.141592654;
double theta_trump;
	theta_trump=atan(slope_2);
//	theta_trump=((theta_trump)*(180/pi));
//	theta_trump=90+theta_trump;
//	theta_trump=(theta_trump)*(pi/180);
	printf("\n%f\n",theta_trump);

	unsigned char ***Piece2_Rotated_Trump=DynamicMemoryAllocation3d(height/2,width/2,BytesPerPixel);
	for(int i=0;i<height/2;i++){
		for(int j=0;j<width/2;j++){

			y=j*sin(theta_trump)+i*cos(theta_trump);
			x=(j*cos(theta_trump))-i*sin(theta_trump);
			///cout<<"x is:"<<x<<"  y is:"<<y<<endl;

			if((y<(height/2) && y>=0) && (x<(width/2) && x>=0)){

				p=floor(y);	q=floor(x);del_x=x-q;del_y=y-p;weight_1=(1-del_x)*(1-del_y);weight_2=del_x*(1-del_y);
				weight_3=del_y*(1-del_x);weight_4=del_x*del_y;//four weights
				if(p+1<height/2 && q+1<width/2){
					for(int k=0;k<3;k++){
						Piece2_Rotated_Trump[i][j][k]=weight_1*Piece_2[p][q][k]
																	   +weight_2*Piece_2[p][q+1][k]
																								 +weight_3*Piece_2[p+1][q][k]
																														   +weight_4*Piece_2[p+1][q+1][k];
					}
				}
				else{
					for(int k=0;k<3;k++){
						Piece2_Rotated_Trump[i][j][k]=Piece_2[p][q][k];
					}
				}
			}
			else{
				for(int k=0;k<3;k++){
					Piece2_Rotated_Trump[i][j][k]=255;
				}
			}
		}
	}
	double theta_trump_final;
		theta_trump_final=(-(90)*(pi/180));
		printf("\n%f\n",theta_trump_final);

	unsigned char ***Piece2_Rotated_Trump_Intermediate=DynamicMemoryAllocation3d(height/2,width/2,BytesPerPixel);
		for(int i=0;i<height/2;i++){
			for(int j=0;j<width/2;j++){

				y=(j*sin(theta_trump_final)+i*cos(theta_trump_final))*-1;
				x=(j*cos(theta_trump_final))-i*sin(theta_trump_final);
				//cout<<"x is:"<<x<<"  y is:"<<y<<endl;

				if((y<(height/2) && y>=0) && (x<(width/2) && x>=0)){

					p=floor(y);	q=floor(x);del_x=x-q;del_y=y-p;weight_1=(1-del_x)*(1-del_y);weight_2=del_x*(1-del_y);
					weight_3=del_y*(1-del_x);weight_4=del_x*del_y;//four weights
					if(p+1<height/2 && q+1<width/2){
						for(int k=0;k<3;k++){
							Piece2_Rotated_Trump_Intermediate[i][j][k]=weight_1*Piece2_Rotated_Trump[p][q][k]
																		   +weight_2*Piece2_Rotated_Trump[p][q+1][k]
																									 +weight_3*Piece2_Rotated_Trump[p+1][q][k]
																															   +weight_4*Piece2_Rotated_Trump[p+1][q+1][k];
						}
					}
					else{
						for(int k=0;k<3;k++){
							Piece2_Rotated_Trump_Intermediate[i][j][k]=Piece2_Rotated_Trump[p][q][k];
						}
					}
				}
				else{
					for(int k=0;k<3;k++){
						Piece2_Rotated_Trump_Intermediate[i][j][k]=255;
					}
				}
			}
		}
unsigned char ***Piece2_Rotated_Trump_final=DynamicMemoryAllocation3d(height/2,width/2,BytesPerPixel);
			for(int i=0;i<height/2;i++){
				for(int j=0;j<width/2;j++){
					for(int k=0;k<BytesPerPixel;k++){
						Piece2_Rotated_Trump_final[i][(width/2)-1-j][k]=Piece2_Rotated_Trump_Intermediate[i][j][k];
					}
				}
			}

int * trumpCoorArray=new int [8];
		trumpCoorArray=CoordinatesStraightImage(Piece2_Rotated_Trump_final,height/2,width/2,BytesPerPixel);
		int newHT=(trumpCoorArray[7]-trumpCoorArray[1]+1);
		int newWT=(trumpCoorArray[6]-trumpCoorArray[0]+1);
		//printf("%d,%d,%d,%d",trumpCoorArray[0],trumpCoorArray[1],trumpCoorArray[6],trumpCoorArray[7]);

		unsigned char ***tempImagePointer_Trump=DynamicMemoryAllocation3d(newHT,newWT,BytesPerPixel);
			for(int i=0;i<newHT;i++){
				for(int j=0;j<newWT;j++){
					for(int k=0;k<3;k++){
						tempImagePointer_Trump[i][j][k]=Piece2_Rotated_Trump_final[i+trumpCoorArray[1]+1][j+trumpCoorArray[0]-1][k];
					}

				}
			}
			int TrumpH=TrumpCoor[2]-TrumpCoor[0]+1,TrumpW=TrumpCoor[5]-TrumpCoor[1]+1;
			unsigned char ***ScalingImageTrump=DynamicMemoryAllocation3d(TrumpH+4,TrumpW+4,BytesPerPixel);
			factorY=(((TrumpH+4)*1.0)/(newHT));
			factorX=(((TrumpW+4)*1.0)/(newWT));
		//	printf("new height:%d,newWidth:%d",newH,newW);
			for(int i=0;i<TrumpH+4;i++){
				y_inv=i/factorY;
				for(int j=0;j<TrumpW+4;j++){
					x_inv=j/factorX;
					p=int(floor(y_inv));
					q=int(floor(x_inv));
					del_x=x_inv-q;
					del_y=y_inv-p;
					weight_1=(1-del_x)*(1-del_y);
					weight_2=del_x*(1-del_y);
					weight_3=del_y*(1-del_x);
					weight_4=del_x*del_y;//four weights calculated;
					if(p+1<newHT && q+1<newWT){
						for(int k=0;k<3;k++){
							ScalingImageTrump[i][j][k]=weight_1*tempImagePointer_Trump[p][q][k]
															 +weight_2*tempImagePointer_Trump[p][q+1][k]
																	 +weight_3*tempImagePointer_Trump[p+1][q][k]
																		   +weight_4*tempImagePointer_Trump[p+1][q+1][k];
						}
					}
					else{
						for(int k=0;k<3;k++){
							ScalingImageTrump[i][j][k]=tempImagePointer_Trump[p][q][k];
						}
					}
				}
			}


			FinalImageTrump=Trump;
			for(int i=2;i<TrumpH+2;i++){
				for(int j=2;j<TrumpW+2;j++){
					for(int k=0;k<3;k++){
						FinalImageTrump[i+236-2][j+163-2][k]=ScalingImageTrump[i][j][k];
			//			if(j==hillaryW-1){
			//				FinalImage[i+135][j+173+1][k]=ScalingImage[i][j][k];
			//			}
			//			if(i==hillaryH-1){
			//				FinalImage[i+135+1][j+173][k]=ScalingImage[i][j][k];
			//			}
					}
				}
			}



	unsigned char *PieceImage_1=DynamicMemoryAllocation3d_2_1d(FinalImageTrump,heightMain,widthMain,BytesPerPixel);

	FileWrite(argv,PieceImage_1,16,heightMain,widthMain,BytesPerPixel);
	//printf("%d,%d",newHT,newWT);
////Deleting the Image Pointers//
	for(int i=0;i<heightMain;i++){
		for(int j=0;j<widthMain;j++){
			delete [] FinalImage[i][j];
			delete [] FinalImageTrump[i][j];
		}
		delete [] FinalImage[i];
		delete [] FinalImageTrump[i];
	}
	delete[] FinalImage;delete [] FinalImageTrump;
//
	for(int i=0;i<height/2;i++){
			for(int j=0;j<width/2;j++){
				delete [] Piece_1[i][j];
				delete [] Piece_2[i][j];
				delete [] Piece1_Rotated[i][j];
				delete [] Piece2_Rotated_Trump[i][j];
				delete [] Piece2_Rotated_Trump_Intermediate[i][j];
				delete [] Piece2_Rotated_Trump_final[i][j];

			}
			delete [] Piece_1[i];
			delete [] Piece_2[i];
			delete [] Piece1_Rotated[i];
			delete [] Piece2_Rotated_Trump[i];
			delete [] Piece2_Rotated_Trump_Intermediate[i];
			delete [] Piece2_Rotated_Trump_final[i];
		}
				delete [] Piece_1;delete [] Piece_2;delete [] Piece1_Rotated;delete [] Piece2_Rotated_Trump;delete [] Piece2_Rotated_Trump_Intermediate;
				delete [] Piece2_Rotated_Trump_final;

	for(int i=0;i<100;i++){
		for(int j=0;j<100;j++){
			delete ScalingImage[i][j];
			delete ScalingImageTrump[i][j];
		}delete [] ScalingImage[i];
		delete [] ScalingImageTrump[i];
	}
	delete [] ScalingImage;delete [] ScalingImageTrump;
	for(int i=0;i<newH;i++){
		for(int j=0;j<newW;j++){
			delete tempImagePointer[i][j];
		}	delete tempImagePointer[i];
	}delete tempImagePointer;
	for(int i=0;i<newHT;i++){
		for(int j=0;j<newWT;j++){
			delete tempImagePointer_Trump[i][j];
		}	delete tempImagePointer_Trump[i];
	}delete tempImagePointer_Trump;
	delete [] array;delete [] trumpCoorArray;delete [] TrumpCoor;delete [] HillaryCorArray;


}
