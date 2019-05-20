#include "Operator.h"

Operator::Operator()
{
}

void Operator::df(int* input, int* operators, int* output, int cols, int rows) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			int matrix[9] = {0};
			for (int m = -1; m < 2; m++) {
				for (int n = -1; n < 2; n++) {
					if (i + m < 0 || i + m >= rows) {
						continue;
					}
					if (j + n < 0 || j + n >= cols) {
						continue;
					}
					matrix[(m + 1) * 3 + n + 1] = input[(i + m) * cols + (j + n)];
				}
			}
			output[i * cols + j] = dot(matrix, operators);
		}
	}
}

int Operator::dot(int* input1, int* input2) {
	int result = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result += input1[i * 3 + j] * input2[i * 3 + j];
		}
	}
	return result;
}