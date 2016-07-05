#include "Mathematics.h"
#include <stdio.h>
#define FIRST 1

matrix3x3 skew(matrix3x1 w)
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
	return 1;
}

double vectorNorm4x1(matrix4x1 _r)
{
	return 0.0;
}

double vectorNorm3x1(matrix3x1 _r)
{
	return 0.0;
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
	matrix3x3 eye_3 = { //3x3 identity matrix
		{
			{1, 0, 0},
			{0, 1, 0},
			{0, 0, 1}
		}
	};

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
	matrix3x1 q1_3_multiplied; //every component of q1_3_multiplied will be equal to q1_3 multiplied by Q.m_data[3]*2 
								//in Matlab: q(4) * 2
	for ( i = 0; i < 3; i++)
		q1_3_multiplied.m_data[i] *= Q.m_data[3];

	matrix3x3 A_2nd = skew(q1_3_multiplied); //Second part of the formula
	//=============================================================================================================
#if FIRST == 1
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
#endif //FIRST


//Multiplying quaternions: http://www.mathworks.com/help/aerotbx/ug/quatmultiply.html
//I = eye(n) returns an n - by - n identity matrix3x3 with ones on the main diagonal and zeros elsewhere.

	return A;
}

matrix4x1 q_to_2nd_power(matrix4x1 Q)
{

	return 0;
}



