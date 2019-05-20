#pragma once
class Operator {
public:
	int Prewitt_x[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1 };
	int Prewitt_y[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1 };
	int Sobel_x[9] = {1, 2, 1, 0, 0, 0, -1, -2, -1 };
	int Sobel_y[9] = {1, 0, -1, 2, 0, -2, 1, 0, -1 };

public:
	Operator();
	void df(int* input, int* operators, int* output, int cols, int rows);
private:
	int dot(int* input1, int* input2);
};