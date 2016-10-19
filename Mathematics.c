#include "Mathematics.h"
#include <stdio.h>
#include <math.h>
#define SINGLE_NUMBER 0
#define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286

matrix3x3 skew3x1(matrix3x1 w)
{
	matrix3x3 A;

	//Assigning values so that A is skew-symmetric matrix3x3
	A.m_data[0][1] = -w.m_data[3];
	A.m_data[0][2] = w.m_data[2];

	A.m_data[1][0] = w.m_data[3];
	A.m_data[1][2] = -w.m_data[1]; 

	A.m_data[2][0] = -w.m_data[2];
	A.m_data[2][1] = w.m_data[1];

	A.m_data[0][0] = A.m_data[1][1] = A.m_data[2][2] = 0; //Rest of fields in matrix are zeros.

	return A;
}

matrix3x3 skew1x3(matrix1x3 w) //Similar with skew(matrix3x1 w) funciton, because it actually does the same thing, 
							//just the vector is transposed
{
	matrix3x3 A;

	//Assigning values so that A is skew-symmetric matrix3x3
	A.m_data[0][1] = -w.m_data[3];
	A.m_data[0][2] = w.m_data[2];

	A.m_data[1][0] = w.m_data[3];
	A.m_data[1][2] = -w.m_data[1];

	A.m_data[2][0] = -w.m_data[2];
	A.m_data[2][1] = w.m_data[1];

	A.m_data[0][0] = A.m_data[1][1] = A.m_data[2][2] = 0; //Rest of fields in matrix are zeros.

	return A;
}

double vectorNorm3x3(matrix3x3 _r)  //Mocked it - Pablo has wrtitten the function
{
	return 1.0;
}

double vectorNorm4x1(matrix4x1 _r) //Mocked it - Pablo has wrtitten the function
{
	return 0.0;
}

double vectorNorm3x1(matrix3x1 _r) //Mocked it - Pablo has wrtitten the function
{
	return sqrt(_r.m_data[0]*_r.m_data[0] + _r.m_data[1]*_r.m_data[1] + _r.m_data[2]*_r.m_data[2]);
}

double vectorNorm1x3(matrix1x3 _r) //Mocked it - Pablo has wrtitten the function
{
	return sqrt(_r.m_data[0]*_r.m_data[0] + _r.m_data[1]*_r.m_data[1] + _r.m_data[2]*_r.m_data[2]);
}

matrix3x3 q2m(matrix4x1 Q)
{
	// Calculating rotation matrix3x3 from quaternion[q1 q2 q3 q4]' where q4 is
	// scalar part
	/*
	function A = q2m(q)
		A = (q(4) ^ 2 - vectorNorm(q(1:3)) ^ 2) * eye(3) - 2 * q(4) * skew(q(1:3)) + 2 * q(1:3) * q(1:3)';
		end
	*/

	matrix3x1 q1_3; //Instead of q(1:3)
	matrix3x3 A; //It will be returned by the function
	int i, j; //iterators
	for (i = 0; i < 3; i++) //rewriting from Q to q1_3
		q1_3.m_data[i] = Q.m_data[i];
	//=============================================================================================================
	double a1 = ((Q.m_data[3])*(Q.m_data[3]) - vectorNorm3x1(q1_3) * vectorNorm3x1(q1_3));
	matrix3x3 A_1st = {		//First part of the long formula
		{
			{ a1, 0, 0 },
			{ 0, a1, 0 },
			{ 0, 0, a1 }
		}
	};
	//=============================================================================================================
	matrix3x1 q1_3_multiplied; //every component of q1_3_multiplied will be equal to q1_3 multiplied by Q.m_data[3]
								//in Matlab: q(4)
	for (i = 0; i < 3; i++)
		q1_3_multiplied.m_data[i] = Q.m_data[3] * q1_3.m_data[i];

	matrix3x3 A_2nd = skew3x1(q1_3_multiplied); //Second part of the formula
	//=============================================================================================================
#if SINGLE_NUMBER == 1
	matrix3x3 A_3rd = { //Third part of the formula: q(1:3) * q(1:3)'
		{ //It's multiplication of vectors 1x3 and 3x1, product is 3x3. If we multiply 3x1 by 1x3, we get a single number.
			//I don't know which version is correct, but I assumed the first one.
			{ q1_3.m_data[0] * q1_3.m_data[0], q1_3.m_data[0] * q1_3.m_data[1], q1_3.m_data[0] * q1_3.m_data[2] },
			{ q1_3.m_data[1] * q1_3.m_data[0], q1_3.m_data[1] * q1_3.m_data[1], q1_3.m_data[1] * q1_3.m_data[2] },
			{ q1_3.m_data[2] * q1_3.m_data[0], q1_3.m_data[2] * q1_3.m_data[1], q1_3.m_data[2] * q1_3.m_data[2] }
		}
	};


	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			A.m_data[i][j] = A_1st.m_data[i][j] - 2 * A_2nd.m_data[i][j] + 2 * A_3rd.m_data[i][j];

#else
	//Second way - it will be a single value, because it's a product of multiplication 3x1 and 1x3 matrixes.
	double a3 = q1_3.m_data[0] * q1_3.m_data[0] + q1_3.m_data[1] * q1_3.m_data[1] + q1_3.m_data[2] * q1_3.m_data[2];

	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			A.m_data[i][j] = A_1st.m_data[i][j] - 2 * A_2nd.m_data[i][j] + 2 * a3;
#endif //SINGLE_NUMBER


//Multiplying quaternions: http://www.mathworks.com/help/aerotbx/ug/quatmultiply.html
//I = eye(n) returns an n - by - n identity matrix3x3 with ones on the main diagonal and zeros elsewhere.

	return A;
}

matrix4x1 m2q(matrix3x3 A) //% Extract quaternion from attitude matrix
//% Avoid numerical errors by choosing the quaternion with the greatest
//% norm
{
	double trace_A = A.m_data[0][0] + A.m_data[1][1] + A.m_data[2][2]; 
	//%trace(A) ist the sum of diagonal elements of A matrix.
	matrix4x1 q;
	matrix4x1 a = 
	{
		{
			trace_A, A.m_data[0][0], A.m_data[1][1], A.m_data[2][2]
		}
	};
	matrix4x1 a_sorted = a;
	quicksort(a_sorted.m_data, 0, 3); //Sorting the table
	double max_value = a_sorted.m_data[3]; //Assign the maximal value

	
	if (max_value == A.m_data[0][0])
	{
		q.m_data[0] = 0.5 * sqrt(1 + 2 * A.m_data[0][0] - trace_A);
		q.m_data[1] = (A.m_data[0][1] + A.m_data[1][0]) / 4 / q.m_data[0];
		q.m_data[2] = (A.m_data[0][2] + A.m_data[2][0]) / 4 / q.m_data[0];
		q.m_data[3] = (A.m_data[1][2] - A.m_data[2][1]) / 4 / q.m_data[0];
	}
	
	else if (max_value == A.m_data[1][1])
	{
		q.m_data[1] = 0.5 * sqrt(1 + 2 * A.m_data[1][1] - trace_A);
		q.m_data[0] = (A.m_data[0][1] + A.m_data[1][0]) / 4 / q.m_data[1];
		q.m_data[2] = (A.m_data[1][2] + A.m_data[2][1]) / 4 / q.m_data[1];
		q.m_data[3] = (A.m_data[2][0] - A.m_data[0][2]) / 4 / q.m_data[1];
	}
	else if (max_value == A.m_data[2][2])
	{
		q.m_data[2] = 0.5 * sqrt(1 + 2 * A.m_data[2][2] - trace_A);
		q.m_data[0] = (A.m_data[2][0] + A.m_data[0][2]) / 4 / q.m_data[2];
		q.m_data[1] = (A.m_data[1][2] + A.m_data[2][1]) / 4 / q.m_data[2];
		q.m_data[3] = (A.m_data[0][1] - A.m_data[1][0]) / 4 / q.m_data[2];
	}

	else if (max_value == trace_A)
	{
		q.m_data[3] = 0.5 * sqrt(1 + trace_A);
		q.m_data[0] = (A.m_data[1][2] - A.m_data[2][1]) / 4 / q.m_data[3];
		q.m_data[1] = (A.m_data[2][0] - A.m_data[0][2]) / 4 / q.m_data[3];
		q.m_data[2] = (A.m_data[0][1] - A.m_data[1][0]) / 4 / q.m_data[3];
	}

	//q = q' ????? 
	return q;
}

void quicksort(double table[], int left, int right)
{
	double v = table[(left + right) / 2];
	int i, j;
	double x;
	i = left;
	j = right;
	do {
		while (table[i] < v) i++;
		while (table[j] > v) j--;
		if (i <= j) {
			x = table[i];
			table[i] = table[j];
			table[j] = x;
			i++; 
			j--;
		}
	} while (i <= j);
	if (j > left) quicksort(table, left, j);
	if (i< right) quicksort(table, i, right);
}

double max(double arg1, double arg2)
{
	if (arg1 >= arg2)
		return arg1;
	else if (arg1 < arg2)
		return arg2;
	else
		return 0;
}

matrix1x3 q2euler(matrix4x1 Q)
{
	double pitch = asin(-2 * (Q.m_data[0] * Q.m_data[2] - Q.m_data[3] * Q.m_data[1])) * 180 / PI;
	double yaw = atan2(2 * (Q.m_data[0] * Q.m_data[1] + Q.m_data[3] * Q.m_data[2]), Q.m_data[0] * Q.m_data[0] - Q.m_data[1] * Q.m_data[1] - Q.m_data[2] * Q.m_data[2] + Q.m_data[3] * Q.m_data[3]) * 180 / PI;
	double roll = atan2(2 * (Q.m_data[1] * Q.m_data[2] + Q.m_data[0] * Q.m_data[3]), -Q.m_data[0] * Q.m_data[0] - Q.m_data[1] * Q.m_data[1] + Q.m_data[2] * Q.m_data[2] + Q.m_data[3] * Q.m_data[3]) * 180 / PI;

	matrix1x3 euler;
	euler.m_data[0] = pitch;
	euler.m_data[1] = yaw;
	euler.m_data[2] = roll;

	return euler;

}
