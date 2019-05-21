#include "MyCanny.h"
#include <iostream>
#include <math.h>
#include <stack>
#include <queue>

#define PI acos(-1)

MyCanny::MyCanny(cv::Mat image, int num1, int num2)
{
	cols = image.cols;
	rows = image.rows;

	limit1 = num1;
	limit2 = num2;

	M = (int*)malloc(sizeof(int) * (rows * cols));
	a = (double*)malloc(sizeof(double) * (rows * cols));

	gn = (double*)malloc(sizeof(double) * (rows * cols));
	gnh = (double*)malloc(sizeof(double) * (rows * cols));
	gnl = (double*)malloc(sizeof(double) * (rows * cols));
	result = (double*)malloc(sizeof(double) * (rows * cols));

	calculateMandA(image);
	calculateGN();
	calculateGnhandGnl();
	edgeconnect();
}

void MyCanny::calculateMandA(cv::Mat image) {
	int* input = (int*)malloc(sizeof(int) * (rows * cols));
	int* gx = (int *)malloc(sizeof(int) * (rows * cols));
	int* gy = (int *)malloc(sizeof(int) * (rows * cols));

	Utils utils;
	Operator o;

	utils.Mat2Vec(image, input);
	o.df(input, o.Sobel_x, gx, cols, rows);
	o.df(input, o.Sobel_y, gy, cols, rows);
	
	utils.SumPowSqrt(gx, gy, M, cols * rows);
	// utils.Normalize(M, cols * rows);
	utils.actan(gx, gy, a, cols * rows);
}

void MyCanny::calculateGnhandGnl() {
	double value = 0.0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			value = gn[i * cols + j];
			if (value > limit1 && value < limit2) {
				gnl[i * cols + j] = value;
			}
			else {
				gnl[i * cols + j] = 0;
			}
			if (value >= limit2) {
				gnh[i * cols + j] = value;
			}
			else {
				gnh[i * cols + j] = 0;
			}
		}
	}
}

void MyCanny::edgeconnect() {
	int* masked = (int*)malloc(sizeof(int) * (rows * cols));
	for (int i = 0; i < (rows * cols); i++) {
		masked[i] = 0;
	}

	std::stack<int> stk;
	std::queue<int> q;

	int x[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
	int y[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

	int num;
	int m;
	int n;
	bool connected = false;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (masked[i * cols + j] == 0 && gnl[i * cols + j] > 0) {
				stk.push(i * cols + j);
				q.push(i * cols + j);
				masked[i * cols + j] = 1;
				connected = false;
				while (!stk.empty()) {
					num = stk.top();
					stk.pop();
					m = num / cols;
					n = num % cols;
					for (int k = 0; k < 8; k++) {
						int mm = m + x[k];
						int nn = n + y[k];
						if (mm >= 0 && mm < rows && nn >= 0 && nn < cols) {
							if (masked[mm * cols + nn] == 0 && gnl[mm * cols + nn] > 0) {
								stk.push(mm * cols + nn);
								q.push(mm * cols + nn);
								masked[mm * cols + nn] = 1;
							}
							if (gnh[mm * cols + nn] > 0) {
								connected = true;
							}
						}
					}
				}
				if (connected) {
					while (!q.empty()) {
						num = q.front();
						q.pop();
						gnh[num] = gnl[num];
					}
				}
				else {
					while (!q.empty()) {
						q.pop();
					}
				}
			}
		}
	}
}

void MyCanny::calculateGN() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			double theta = a[i * cols + j];
			gn[i * cols + j] = 0.0;
			if ((theta >= -0.125 * PI && theta <= 0.125 * PI) || (theta <= -0.875 * PI) || (theta >= 0.875 * PI)) {
				if (i > 0) {
					if (M[i * cols + j] < M[(i - 1) * cols + j]) {
						continue;
					}
				}
				if (i < rows - 1) {
					if (M[i * cols + j] < M[(i + 1) * cols + j]) {
						continue;
					}
				}
				gn[i * cols + j] = (double)M[i * cols + j];
			}
			else if ((theta >= 0.375 * PI && theta <= 0.625 * PI) || (theta >= -0.625 * PI && theta <= -0.375 * PI)) {
				if (j > 0) {
					if (M[i * cols + j] < M[i * cols + j - 1]) {
						continue;
					}
				}
				if (j < cols - 1) {
					if (M[i * cols + j] < M[i * cols + j + 1]) {
						continue;
					}
				}
				gn[i * cols + j] = (double)M[i * cols + j];
			}
			else if ((theta >= 0.625 * PI && theta <= 0.875 * PI) || (theta >= -0.375 * PI && theta <= -0.125 * PI)) {
				if (i > 0 && j < cols - 1) {
					if (M[i * cols + j] < M[(i - 1) * cols + j + 1]) {
						continue;
					}
				}
				if (i < rows - 1 && j > 0) {
					if (M[i * cols + j] < M[(i + 1) * cols + j - 1]) {
						continue;
					}
				}
				gn[i * cols + j] = (double)M[i * cols + j];
			}
			else {
				if (i > 0 && j > 0) {
					if (M[i * cols + j] < M[(i - 1) * cols + j - 1]) {
						continue;
					}
				}
				if (i < rows - 1 && j < cols - 1) {
					if (M[i * cols + j] < M[(i + 1) * cols + j + 1]) {
						continue;
					}
				}
				gn[i * cols + j] = (double)M[i * cols + j];
			}
		}
	}
}

double* MyCanny::getGnl() {
	return gnl;
}

double* MyCanny::getGnh() {
	return gnh;
}

double* MyCanny::getresult() {
	for (int i = 0; i < rows * cols; i++) {
		if (gnh[i] > 0) {
			result[i] = 255;
		}
		else {
			result[i] = 0;
		}
	}
	return result;
}