#include "Mathematics.h"
//ECI - Earth Centered Inertial
double aeroDragTorque(matrix r_eci, double v_eci, matrix q, double face, double R_z) //I don't know global value R_z so i'll set this as parameter
{
	double w_ez = 7.2921158553e-5; //[rad/s]
	matrix w_e;
	w_e.q[0] = (double* )malloc(sizeof(double) * 3); 
	w_e.q[0][0] = w_ez * 1;	//First row, first position
	w_e.q[0][1] = 0;	//First row, second position
	w_e.q[0][2] = 0;	//First row, third position

	//w_e looks now like: [0 0 1]' (transposed)

	double w_e[3] = { w_ez * 1, 0, 0 }; //earth rate vector in eci
	matrix *A;
	A->length = 3;
	A->width = 3;
	*A = *skew(w_e);
	matrix vi_rel;// = v_eci - (*A) * r_eci; //relative satellite velocity to the atmosphere in eci [km/s]

	vi_rel.q = (double **)malloc(3 * sizeof(double));
	int i;
	for (i = 0; i < 3; i++) //Multiplying matrice 3x3 (A) and vector (1x3)
	{
		vi_rel.q[i][0] = (A->q[i][0] + A->q[i][1] + A->q[i][2]) * (w_e.q[i][0]);
	}
	vi_rel.length = 3;
	vi_rel.width = 1;
	//vi_rel: [x y z]'
	
	//GO ON HERE finish A_i2s and q2m

	double A_i2s = q2m(q);
	double vs_rel = A_i2s * vi_rel; // relative velocity in satellite frame[km / s]

	double alt = vectorNorm(r_eci) - R_z; //approx altitude above spherical earth[km]

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

}

