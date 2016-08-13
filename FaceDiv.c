#include "FaceDiv.h"

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
	//v
	face.v[0][0] = 1; //face.v(:,1) = [1 0 0]';
	face.v[1][0] = 0;
	face.v[2][0] = 0;

	face.v[0][1] = 0; //face.v(:, 2) = [0 0 1]';
	face.v[1][1] = 0;
	face.v[2][1] = 1;

	face.v[0][2] = 0; //face.v(:,3) = [0 0 -1]';
	face.v[1][2] = 0;
	face.v[2][2] = -1;

	face.v[0][3] = -1; //face.v(:,4) = [-1 0 0]';
	face.v[1][3] = 0;
	face.v[2][3] = 0;

	face.v[0][4] = -sqrt(2) / 2; //face.v(:,5) = [-sqrt(2)/2 -sqrt(2)/2 0]';
	face.v[1][4] = -sqrt(2) / 2;
	face.v[2][4] = 0;

	face.v[0][5] = -sqrt(2) / 2; //face.v(:, 6) = [-sqrt(2) / 2 sqrt(2) / 2 0]';
	face.v[1][5] = sqrt(2) / 2;
	face.v[2][5] = 0;
	//s
	face.s[0] = 0.2 * 0.3;
	face.s[1] = 0.1 * 0.1;
	face.s[2] = face.s[1];
	face.s[3] = 0.1 * 0.2;
	face.s[4] = sqrt(2) * 0.1 * 0.2;
	face.s[5] = face.s[4];
	//cp
	face.cp[0][0] = 0.05 - r_cm.m_data[0]; //face.cp(:,1) = [0.05 0 0]' - r_cm;
	face.cp[1][0] = 0 - r_cm.m_data[1];
	face.cp[2][0] = 0 - r_cm.m_data[2];

	face.cp[0][1] = 0 - r_cm.m_data[0]; //face.cp(:,2) = [0 0 0.1]' - r_cm;
	face.cp[1][1] = 0 - r_cm.m_data[1];
	face.cp[2][1] = 0.1 - r_cm.m_data[2];

	face.cp[0][2] = 0 - r_cm.m_data[0]; //face.cp(:,3) = [0 0 -0.1]' - r_cm;
	face.cp[1][2] = 0 - r_cm.m_data[1];
	face.cp[2][2] = -0.1 - r_cm.m_data[2];

	face.cp[0][3] = -0.05 - r_cm.m_data[0]; //face.cp(:,4) = [-0.05 0 0]' - r_cm;
	face.cp[1][3] = 0 - r_cm.m_data[1];
	face.cp[2][3] = 0 - r_cm.m_data[2];

	face.cp[0][4] = 0 - r_cm.m_data[0]; //face.cp(:,5) = [0 -0.1 0]' - r_cm;
	face.cp[1][4] = -0.1 - r_cm.m_data[1];
	face.cp[2][4] = 0 - r_cm.m_data[2];

	face.cp[0][5] = 0 - r_cm.m_data[0]; //face.cp(:,6) = [0 0.1 0]' - r_cm;
	face.cp[1][5] = 0.1 - r_cm.m_data[1];
	face.cp[2][5] = 0 - r_cm.m_data[2];
	//diffuse
	face.diffuse[0] = 0.9*arr_diff + 0.1*almn_diff;
	face.diffuse[1] = almn_diff;
	face.diffuse[2] = face.diffuse[1];
	face.diffuse[3] = 0.5*arr_diff + 0.5*almn_diff;
	face.diffuse[4] = 0.5*mli_diff + 0.45*arr_diff + 0.05*almn_diff;
	face.diffuse[5] = face.diffuse[4];
	//spec
	face.spec[0] = 0.9*arr_spec + 0.1*almn_spec;
	face.spec[1] = almn_spec;
	face.spec[2] = face.spec[1];
	face.spec[3] = 0.5*arr_spec + 0.5*almn_spec;
	face.spec[4] = 0.5*mli_spec + 0.45*arr_spec + 0.05*almn_spec;
	face.spec[5] = face.spec[4];
	//absorpt
	face.spec[0] = 0.9*arr_abs + 0.1*almn_abs;
	face.spec[1] = almn_abs;
	face.spec[2] = face.absorpt[1];
	face.spec[3] = 0.5*arr_abs + 0.5*almn_abs;
	face.spec[4] = 0.5*mli_abs + 0.45*arr_abs + 0.05*almn_abs;
	face.spec[5] = face.absorpt[4];
}
