#pragma once
#include <core/core.hpp>
#include <highgui/highgui.hpp>

class MySobel {
public:
	cv::Mat sobel_x(cv::Mat image);
	cv::Mat sobel_y(cv::Mat imgae);
	cv::Mat sobel(cv::Mat image);
};