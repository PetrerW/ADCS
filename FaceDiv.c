#include "Mathematics.h"
#include <math.h>
struct faceTag {
	double v[3][6], cp[3][6];
	double s[6], diffuse[6], spec[6], absorpt[6];
}face;

double almn_abs = 0.06;
double almn_spec = 0.1;
double almn_diff = 0.84;

double mli_abs = 0.05;
double mli_spec = 0;
double mli_diff = 0.95;

double arr_abs = 0.92;
double arr_spec = 0.04;
double arr_diff = 0.04;

matrix1x3 r_cm = { //I don't know what's this, just mock it.
	{1, 2, 3}
};

void faceDiv()
{
	face.v[0][0] = 1;
	face.v[0][1] = 0;
	face.v[0][2] = 0;
	face.v[0][3] = -1;
	face.v[0][4] = -sqrt(2) / 2;
	face.v[0][5] = face.v[0][4];

	face.v[1][0] = face.v[1][1] = face.v[1][2] = face.v[1][3] = 0;
	face.v[1][4] = -sqrt(2) / 2;
	face.v[1][5] = sqrt(2) / 2;

	face.v[2][0] = face.v[2][3] = face.v[2][4] = 0;
	face.v[2][1] = 1;
	face.v[2][2] = -1;
	// GO ON HERE

	face =
	{

		{//cp
			{ 0.05 - r_cm.m_data[0], 0 - r_cm.m_data[0], 0 - r_cm.m_data[0], -0.05 - r_cm.m_data[0], 0- r_cm.m_data[0], 0 - r_cm.m_data[0] },
			{ 0 - r_cm.m_data[1], 0 - r_cm.m_data[1],0 - r_cm.m_data[1], 0 - r_cm.m_data[1], -0.1 - r_cm.m_data[1], 0.1 - r_cm.m_data[1] },
			{ 0 - r_cm.m_data[2],0.1 - r_cm.m_data[2],-0.1 - r_cm.m_data[2],0 - r_cm.m_data[2],0 - r_cm.m_data[2],0 - r_cm.m_data[2] },
		},

		{ 0.2 * 0.3 ,0.1 * 0.1,0.1 * 0.1, 01 * 0.2, sqrt(2) * 0.1 * 0.2, sqrt(2) * 0.1 * 0.2 },
		{ 0.9*arr_diff + 0.1*almn_diff, almn_diff , almn_diff, 0.5*arr_diff + 0.5*almn_diff , 
			0.5*mli_diff + 0.45*arr_diff + 0.05*almn_diff, 0.5*mli_diff + 0.45*arr_diff + 0.05*almn_diff },
		{ 0.9*arr_spec + 0.1*almn_spec,almn_spec,almn_spec,0.5*arr_spec + 0.5*almn_spec,
			0.5*mli_spec + 0.45*arr_spec + 0.05*almn_spec,0.5*mli_spec + 0.45*arr_spec + 0.05*almn_spec },
		{ 0.9*arr_abs + 0.1*almn_abs,almn_abs,almn_abs,0.5*arr_abs + 0.5*almn_abs,
			0.5*mli_abs + 0.45*arr_abs + 0.05*almn_abs,0.5*mli_abs + 0.45*arr_abs + 0.05*almn_abs },

	};
}
