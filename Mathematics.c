#include "Mathematics.h"

double q2m(double* _q) { //I don't know what it should do, so I mock it.
	return 1;
}

matrix* skew(matrix w)
{
	w.q = malloc(sizeof(double) * 3);
	matrix A;
	A.length = 3;
	A.width = 3;
	double* ptr[3];

	int i, j;
	for (i = 0; i < A.length; i++) //Allocating memory for 2D array of pointers.
								   //www.geeksforgeeks.org/dynamically-allocate-2d-array-c/
	{
		ptr[i] = (double *)calloc(A.width, sizeof(double)); //I use calloc, because every element in an array should be initially zero.
	}
	A.q = ptr; //assign allocated memory to the A.q pointer.

	//Assigning adequate values so that A is skew-symmetric matrix
	A.q[1][2] = -*(w.q[3]);
	A.q[1][3] = *(w.q[2]);

	A.q[2][1] = *(w.q[3]);
	A.q[2][3] = -*(w.q[1]); 

	A.q[3][1] = -*(w.q[2]);
	A.q[3][2] = *(w.q[1]);

	return &A;
}

double vectorNorm(matrix _r)  //Mocked it - Pablo has wrtitten the function
{
	return 1;
}


