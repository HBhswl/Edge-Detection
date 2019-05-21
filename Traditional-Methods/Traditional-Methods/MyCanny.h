#pragma once
#include <core/core.hpp>
#include <highgui/highgui.hpp>
#include "Operator.h"
#include "utils.h"


class MyCanny {
private:
	int cols = 0;
	int rows = 0;

	int limit1 = 0;
	int limit2 = 0;

	int* M;
	double* a;

	double* gn;
	double* gnh;
	double* gnl;
	double* result;

public:
	MyCanny(cv::Mat image, int num1, int num2);
	double* getGnl();
	double* getGnh();
	double* getresult();

private:
	void calculateMandA(cv::Mat image);
	void calculateGN();
	void calculateGnhandGnl();
	void edgeconnect();
};