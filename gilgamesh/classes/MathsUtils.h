#pragma once

#include "stdafx.h"

class MathsUtils {
public:
	static void printMatrix(mat4 matrix) {
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				printf("%f,", matrix[x][y]);
			}
			printf("\n");
		}
	}

	static void printMatrix(mat3 matrix) {
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				printf("%f,", matrix[x][y]);
			}
			printf("\n");
		}
	}

	static void matrixToEulerAngles(mat4 matrix) {

	}
};