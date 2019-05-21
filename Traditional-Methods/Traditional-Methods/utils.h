#pragma once
#include <core/core.hpp>
#include <highgui/highgui.hpp>

class Utils {
public:
	cv::Mat Rgb2Gray(cv::Mat img);
	void Mat2Vec(cv::Mat img, int* vec);
	cv::Mat Vec2Mat(int* vec, int rows, int cols);
	cv::Mat Vec2Mat(double* vec, int rows, int cols);
	void SumAbs(int* vec1, int* vec2, int* vec3, int size);
	void SumPowSqrt(int* vec1, int* vec2, int* vec3, int size);
	void Normalize(int* vec, int size);
	void actan(int* vec1, int* vec2, double* vec3, int size);
};