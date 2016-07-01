#pragma once
typedef struct matrix matrix;
struct matrix {
	double **q;
	int width, length;
};