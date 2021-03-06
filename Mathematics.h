#pragma once
typedef struct matrix3x3Tag {
	double m_data[3][3];
}matrix3x3;

typedef struct matrix4x1Tag {
	double m_data[4];
}matrix4x1; 

typedef struct matrix3x1Tag {
	double m_data[3];
}matrix3x1; //3 columns, 1 row

typedef struct matrix1x3Tag {
	double m_data[3];
}matrix1x3; //1 column, 3 rows

typedef struct matrix6x3Tag {
	double m_data[3][6]; //6 columns, 3 rows
}matrix6x3;

typedef struct matrix2x1Tag {
	double m_data[2]; //2 columns
}matrix2x1;

//3x1 : [1 2 3] three columns, one row
//1x3:  [1] one column, three rows
//		[2]
//		[3]
//Convention: q[0][1] is first row (0) and second column (1)

matrix3x3 skew3x1(matrix3x1 w);
matrix3x3 skew1x3(matrix1x3 w);
double vectorNorm3x3(matrix3x3 _r);
double vectorNorm4x1(matrix4x1 _r);
double vectorNorm3x1(matrix3x1 _r);
double vectorNorm1x3(matrix1x3 _r);
matrix3x3 q2m(matrix4x1 Q);
matrix4x1 m2q(matrix3x3 A);
void quicksort(double table[], int left, int right);
double max(double arg1, double arg2);
matrix1x3 q2euler(matrix4x1 Q); //Calculating Euler angles[deg] from quaternion[q1 q2 q3 q0]'
