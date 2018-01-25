// CannyStill.cpp

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
#include<conio.h>           // may have to modify this line if not using Windows
using namespace cv;

///////////////////////////////////////////////////////////////////////////////////////////////////
int main() {

	 Mat imgOriginal;        // input image
	 Mat imgGrayscale;       // grayscale of input image
	 Mat imgBlurred;         // intermediate blured image
	 Mat imgCanny;           // Canny edge image

	imgOriginal =  imread("Boat.jpg");          // open image

	if (imgOriginal.empty()) {                                  // if unable to open image
		std::cout << "error: image not read from file\n\n";     // show error message on command line
		_getch();                                               // may have to modify this line if not using Windows
		return(0);                                              // and exit program
	}

	 cvtColor(imgOriginal, imgGrayscale, CV_BGR2GRAY);       // convert to grayscale

	 GaussianBlur(imgGrayscale,          // input image
		imgBlurred,                         // output image
		 Size(5, 5),                     // smoothing window width and height in pixels
		1.5);                               // sigma value, determines how much the image will be blurred

	 Canny(imgBlurred,           // input image
		imgCanny,                   // output image
		100,                        // low threshold
		200);                       // high threshold

									// declare windows
	 namedWindow("imgOriginal", CV_WINDOW_AUTOSIZE);     // note: you can use CV_WINDOW_NORMAL which allows resizing the window
	 namedWindow("imgCanny", CV_WINDOW_AUTOSIZE);        // or CV_WINDOW_AUTOSIZE for a fixed size window matching the resolution of the image
															// CV_WINDOW_AUTOSIZE is the default
	 imshow("imgOriginal", imgOriginal);     // show windows
	 imshow("imgCanny", imgCanny);

	 waitKey(0);                 // hold windows open until user presses a key

	return(0);
}



