#include <iostream>

#include "Operator.h"
#include "utils.h"
#include "MySobel.h"
#include "MyCanny.h"

#include <core/core.hpp>
#include <highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main()
{
	Utils utils;
	Operator o;
	MySobel mysobel;

	Mat img = imread("lena.png");
	Mat Gray = utils.Rgb2Gray(img);
	Mat dst;
	resize(Gray, dst, Size(256, 256));

	double threshold1 = 100;
	double threshold2 = 200;
	// ========================================
	//             MyCanny
	// ========================================
	MyCanny mycanny(dst, threshold1, threshold2);
	Mat mycannyresult;
	mycannyresult = utils.Vec2Mat(mycanny.getresult(), 256, 256);
	imshow("Mycanny", mycannyresult);

	// ========================================
	//             OpenCv Canny
	// ========================================

	Mat opencvcanny;
	Canny(dst, opencvcanny, threshold1, threshold2);
	imshow("OpencvCanny", opencvcanny);

	// ========================================
	//             OpenCv Sobel
	// ========================================
	Mat grad_x, grad_y, opencvsobel;
	Mat abs_grad_x, abs_grad_y;

	Sobel(dst, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);

	Sobel(dst, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);

	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, opencvsobel);
	imshow("OpencvSobel", opencvsobel);
	
	// ========================================
	//             MySobel
	// ========================================
	Mat mysobelreuslt;
	mysobelreuslt = mysobel.sobel_x(dst);
	mysobelreuslt = mysobel.sobel_y(dst);
	mysobelreuslt = mysobel.sobel(dst);
	imshow("MySobel", mysobelreuslt);
	waitKey(0);
	return 0;
}
