#include <iostream>
#include "Operator.h"
#include "utils.h"
#include <core/core.hpp>
#include <highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main()
{
	Utils utils;
	Operator o;

	Mat img = imread("C:\\Users\\lenovo\\Desktop\\lena.png");
	// imshow("img", img);
	Mat Gray = utils.Rgb2Gray(img);
	// imshow("Gray", Gray);
	Mat dst;
	resize(Gray, dst, Size(256, 256));
	// imshow("dst", dst);
	// ========================================
	//             OpenCv
	// ========================================
	
	
	Mat grad_x, grad_y, opencvsobel;
	Mat abs_grad_x, abs_grad_y;

	Sobel(dst, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);

	Sobel(dst, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);

	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, opencvsobel);
	imshow("OpencvSobel", opencvsobel);
	

	int input[256 * 256] = { 0 };
	int outputx[256 * 256] = { 0 };
	int outputy[256 * 256] = { 0 };
	int output[256 * 256] = { 0 };
	utils.Mat2Vec(dst, input);
	
	o.df(input, o.Sobel_x, outputx, 256, 256);
	o.df(input, o.Sobel_y, outputy, 256, 256);

	// utils.SumAbs(outputx, outputy, output, 256 * 256);
	utils.SumPowSqrt(outputx, outputy, output, 256 * 256);

	utils.Normalize(output, 256 * 256);
	Mat sobel = utils.Vec2Mat(output, 256, 256);
	imshow("MySobel", sobel);
	waitKey(0);

	return 0;
}
