// tutorial1.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include "opencv.hpp"

int _tmain(int argc, _TCHAR* argv[])
{
	
	cv::UMat imgSrc;		// declare variables
	cv::UMat imgDst;
	


	cv::imread("lab0.bmp").copyTo(imgSrc);	// load the image

	/*Alternative way
	cv::Mat read;
	read = cv::imread("lab0.bmp");
	read.copyTo(imgSrc);*/

	cv::threshold(imgSrc, imgDst, 10, 255, 0);	//Threshold

	cv::namedWindow("Src");		// declare the window
	cv::namedWindow("Dst");
	cv::imshow("Src", imgSrc);		// show image
	cv::imshow("Dst", imgDst);

	cv::waitKey(0);// press any key to close the window
	cv::destroyWindow("Src");// close window
	cv::destroyWindow("Dst");
	return 0;

}

