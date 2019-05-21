#include "MySobel.h"
#include "utils.h"
#include "Operator.h"

cv::Mat MySobel::sobel_x(cv::Mat image)
{
	Utils utils;
	Operator oper;
	int* input = (int*)malloc(sizeof(int) * image.cols * image.rows);
	int* outputx = (int*)malloc(sizeof(int) * image.cols * image.rows);

	utils.Mat2Vec(image, input);

	oper.df(input, oper.Sobel_x, outputx, image.cols, image.rows);

	utils.Normalize(outputx, image.rows * image.cols);

	cv::Mat sobel = utils.Vec2Mat(outputx, image.rows, image.cols);

	return sobel;
}

cv::Mat MySobel::sobel_y(cv::Mat image)
{
	Utils utils;
	Operator oper;
	int* input = (int*)malloc(sizeof(int) * image.cols * image.rows);
	int* outputy = (int*)malloc(sizeof(int) * image.cols * image.rows);

	utils.Mat2Vec(image, input);

	oper.df(input, oper.Sobel_y, outputy, image.cols, image.rows);

	utils.Normalize(outputy, image.rows * image.cols);

	cv::Mat sobel = utils.Vec2Mat(outputy, image.rows, image.cols);

	return sobel;
}

cv::Mat MySobel::sobel(cv::Mat image)
{
	Utils utils;
	Operator oper;
	int* input = (int*)malloc(sizeof(int) * image.cols * image.rows);
	int* outputx = (int*)malloc(sizeof(int) * image.cols * image.rows);
	int* outputy = (int*)malloc(sizeof(int) * image.cols * image.rows);
	int* output = (int*)malloc(sizeof(int) * image.cols * image.rows);

	utils.Mat2Vec(image, input);

	oper.df(input, oper.Sobel_x, outputx, image.cols, image.rows);
	oper.df(input, oper.Sobel_y, outputy, image.cols, image.rows);

	utils.SumPowSqrt(outputx, outputy, output, image.rows * image.cols);

	utils.Normalize(output, image.rows * image.cols);

	cv::Mat sobel = utils.Vec2Mat(output, image.rows, image.cols);

	return sobel;
}