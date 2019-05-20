#include "utils.h"
#include <math.h>

cv::Mat Utils::Rgb2Gray(cv::Mat img)
{
	cv::Mat Gray(img.rows, img.cols, CV_8U, cv::Scalar(0));
	for (int i = 0; i < img.cols; i++) {
		for (int j = 0; j < img.rows; j++) {
			int r = (int)img.at<cv::Vec3b>(i, j)[0];
			int g = (int)img.at<cv::Vec3b>(i, j)[1];
			int b = (int)img.at<cv::Vec3b>(i, j)[2];
			Gray.at<uchar>(i, j) = (int)(r * 0.299 + g * 0.587 + b * 0.114);
		}
	}
	return Gray;
}

void Utils::Mat2Vec(cv::Mat img, int* vec) {
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			vec[i * img.cols + j] = (int)img.at<uchar>(i, j);
		}
	}
}

cv::Mat Utils::Vec2Mat(int* vec, int rows, int cols) {
	cv::Mat Gray(rows, cols, CV_8U, cv::Scalar(0));
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			Gray.at<uchar>(i, j) = (int)vec[i * cols + j];
		}
	}
	return Gray;
}

void Utils::SumAbs(int* vec1, int* vec2, int* vec3, int size) {
	for (int i = 0; i < size; i ++) {
		vec3[i] = abs(vec1[i]) + abs(vec2[i]);
	}
}

void Utils::SumPowSqrt(int* vec1, int* vec2, int* vec3, int size) {
	for (int i = 0; i < size; i++) {
		vec3[i] = (int)sqrt((double)(vec1[i] * vec1[i] + vec2[i] * vec2[i]));
	}
}

void Utils::Normalize(int* vec, int size) {
	int max = vec[0];
	int min = vec[0];
	for (int i = 0; i < size; i++) {
		if (vec[i] > max)
			max = vec[i];
		if (vec[i] < min)
			min = vec[i];
	}
	for (int i = 0; i < size; i++) {
		vec[i] = (int)(255.0 * (((double)vec[i] - (double)min) / (double)max));
	}
}