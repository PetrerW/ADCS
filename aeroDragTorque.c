#include "Mathematics.h"
#include <stdio.h>
#include <math.h>
//ECI - Earth Centered Inertial
double aeroDragTorque(matrix1x3 r_eci, matrix1x3 v_eci, matrix4x1 q, double face, double R_z) //I don't know global value R_z so i'll set this as parameter
{
	int i;
	double w_ez = 7.2921158553e-5; //[rad/s]
	matrix1x3 w_e = { // earth rate vector in eci
		{ 0, 0, w_ez }
	}; 	//w_e looks like: [0 0 w_ez]' (transposed)

	matrix3x3 A = skew1x3(w_e);

	matrix1x3 vi_rel, second_component; //relative satellite velocity to the atmosphere in eci [km/s]
											//Second component of the vi_rel is: skew(w_e) * r_eci;
											//whole equation is: vi_rel = v_eci - skew(w_e) * r_eci; 

	matrix3x3 A_i2s = q2m(q);
	matrix1x3 vs_rel;

	for (i = 0; i < 3; i++)
	{//Calculating the second component (multiplying matrix A (3x3) by r_eci (1x3) gives 1x3 too
		second_component.m_data[i] = A.m_data[i][0] * r_eci.m_data[0] + A.m_data[i][1] * r_eci.m_data[1] + A.m_data[i][2] * r_eci.m_data[2];
		vi_rel.m_data[i] = v_eci.m_data[i] - second_component.m_data[i];
		//calculating vs_rel 1x3 vector. 
		//relative velocity in satellite frame [km/s]
		vs_rel.m_data[i] = A_i2s.m_data[i][0] * vi_rel.m_data[0] + A_i2s.m_data[i][1] * vi_rel.m_data[1] + A_i2s.m_data[i][2] * vi_rel.m_data[2];
	}

	double alt = vectorNorm1x3(r_eci) - R_z; //approx altitude above spherical earth[km]

	double ro0, H, h0;
		if (alt >= 450 && alt < 500)
		{
			ro0 = 1.585e-12;
			H = 62.2;
			h0 = 450;
		}

		else if (alt >= 500 && alt < 600)
		{
			ro0 = 6.967e-13;
			H = 65.8;
			h0 = 500;
		}

		else if (alt >= 600 && alt < 700)
		{
			ro0 = 1.454e-13;
			H = 79;
			h0 = 600;
		}

		else if (alt >= 700 && alt <= 800)
		{
			ro0 = 3.614e-14;
			H = 109;
			h0 = 700;
		}
		else
			printf("Altitude only in the range 450 - 800 km \n");

		double ro = ro0 * exp((h0 - alt) / H); //Calculating atmosphere dencity
		double cd = 2.2; // drag coeff

		double aero_torque = 0;
		int face_s_legth = 6;


		//GO ON HERE
		//GO ON HERE
		//GO ON HERE
		//GO ON HERE
		//GO ON HERE

		return 0.0;
}

