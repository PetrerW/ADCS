#pragma once
typedef struct matrix3x3Tag {
	double m_data[3][3];
}matrix3x3;

typedef struct matrix4x1Tag {
	double m_data[4];
}matrix4x1;

typedef struct matrix3x1Tag {
	double m_data[3];
}matrix3x1;

//Convention: q[0][1] is first row (0) and second column (1)

matrix3x3 skew(matrix3x1 w);
double vectorNorm(matrix3x3 _r);
double vectorNorm(matrix4x1 _r);
double vectorNorm(matrix3x1 _r);
matrix3x3* q2m(matrix4x1 Q);
matrix4x1 q_to_2nd_power(matrix4x1 Q);

