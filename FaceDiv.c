#include "Mathematics.h"
#include <math.h>
struct faceTag {
	double v[3][6], cp[3][6];
	double s[6], diffuse[6], spec[6], absorpt[6];
};

matrix1x3 r_cm = { //I don't know what's this, just mock it.
	{1, 2, 3}
};

void faceDiv() 
{

	struct faceTag face =
	{
		{//v
			{ 1, 0, 0,-1, -sqrt(2) / 2, -sqrt(2) / 2 },
			{ 0, 0, 0, 0, -sqrt(2) / 2,  sqrt(2) / 2 },
			{ 0, 1,-1, 0, 0			  , 0			 },
		},

		{//cp
			{ 0.05 - r_cm.m_data[0], 0 - r_cm.m_data[0], 0 - r_cm.m_data[0], -0.05 - r_cm.m_data[0], 0- r_cm.m_data[0], 0 - r_cm.m_data[0] },
			{ 0 - r_cm.m_data[1], 0 - r_cm.m_data[1],0 - r_cm.m_data[1], 0 - r_cm.m_data[1], -0.1 - r_cm.m_data[1], 0.1 - r_cm.m_data[1] },
			{ 0 - r_cm.m_data[2],0.1 - r_cm.m_data[2],-0.1 - r_cm.m_data[2],0 - r_cm.m_data[2],0 - r_cm.m_data[2],0 - r_cm.m_data[2] },
		},
		//GO ON HERE
		{ 1,2,3,4,5,6 },
		{ 1,2,3,4,5,6 },
		{ 1,2,3,4,5,6 },
		{ 1,2,3,4,5,6 },

	};
	double r_cm;

	double almn_abs = 0.06;
	double almn_spec = 0.1;
	double almn_diff = 0.84;

	double mli_abs = 0.05;
	double mli_spec = 0;
	double mli_diff = 0.95;

	double arr_abs = 0.92;
	double arr_spec = 0.04;
	double arr_diff = 0.04;

}
struct faceTag face =
{
	{
		{ 1, 0, 0,-1,  ,6 }, 
		{ 0, 0, 0, 0, 5,6 },
		{ 0, 1,-1, 0, 5,6 },
	}, 

	{
		{ 1,2,3,4,5,6 },
		{ 1,2,3,4,5,6 },
		{ 1,2,3,4,5,6 },
	},

	{ 1,2,3,4,5,6 },
	{ 1,2,3,4,5,6 },
	{ 1,2,3,4,5,6 },
	{ 1,2,3,4,5,6 },

};
double r_cm;

double almn_abs = 0.06;
double almn_spec = 0.1;
double almn_diff = 0.84;

double mli_abs = 0.05;
double mli_spec = 0;
double mli_diff = 0.95;

double arr_abs = 0.92;
double arr_spec = 0.04;
double arr_diff = 0.04;
