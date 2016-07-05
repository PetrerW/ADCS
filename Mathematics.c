#include "Mathematics.h"
#include <stdio.h>

matrix3x3 skew(matrix3x1 w)
{
	matrix3x3 A;
	int i, j;
	for (i = 0; i < 3; i++) //A = zeros(3)
		for (j = 0; j < 3; j++)
			A.m_data[i][j] = 0;

	//Assigning values so that A is skew-symmetric matrix3x3
	A.m_data[1][2] = -*(w.m_data[3]);
	A.m_data[1][3] = *(w.m_data[2]);

	A.m_data[2][1] = *(w.m_data[3]);
	A.m_data[2][3] = -*(w.m_data[1]); 

	A.m_data[3][1] = -*(w.m_data[2]);
	A.m_data[3][2] = *(w.m_data[1]);

	return A;
}

double vectorNorm(matrix3x3 _r)  //Mocked it - Pablo has wrtitten the function
{
	return 1;
}

double vectorNorm(matrix4x1 _r)
{
	return 0.0;
}

double vectorNorm(matrix3x1 _r)
{
	return 0.0;
}

matrix3x3 * q2m(matrix4x1 Q)
{
	// Calculating rotation matrix3x3 from quaternion[q1 q2 q3 q4]' where q4 is
	// scalar part
	/*
	function A = q2m(q)
		A = (q(4) ^ 2 - vectorNorm(q(1:3)) ^ 2) * eye(3) - 2 * q(4) * skew(q(1:3)) + 2 * q(1:3) * q(1:3)';
		end
	*/
	matrix3x3 eye_3 = { //3x3 identity matrix
		{
			{1, 0, 0},
			{0, 1, 0},
			{0, 0, 1}
		}
	};


	matrix3x3 A;
	A = ( (Q.m_data[3])*(Q.m_data[3]) ) //START HERE


//Multiplying quaternions: http://www.mathworks.com/help/aerotbx/ug/quatmultiply.html
//I = eye(n) returns an n - by - n identity matrix3x33x3 with ones on the main diagonal and zeros elsewhere.

	return 0;
}

matrix4x1 q_to_2nd_power(matrix4x1 Q)
{

	return 0;
}



