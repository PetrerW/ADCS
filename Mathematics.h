#pragma once
typedef struct matrix matrix;
struct matrix {
	double **q;
	int width, length;
};

//Convention: q[0][1] is first row (0) and second column (1)

matrix* skew(matrix w);
double vectorNorm(matrix _r);


