#include "Mathematics.h"
#include <stdio.h>
#include <math.h>
#include "FaceDiv.h"
//ECI - Earth Centered Inertial
matrix1x3 aeroDragTorque(matrix1x3 r_eci, matrix1x3 v_eci, matrix4x1 q, struct faceTag face, double R_z) //I don't know global value R_z so i'll set this as parameter
{
	int i, j;
	double w_ez = 7.2921158553e-5; //[rad/s]
	matrix1x3 w_e = { // earth rate vector in eci
		{ 0, 0, w_ez }
	}; 	//w_e looks like: [0 0 w_ez]' (transposed)


	matrix3x3 A = skew1x3(w_e);

	matrix1x3 vi_rel, second_component; //relative satellite velocity to the atmosphere in eci [km/s]
										//Second component of the vi_rel is: skew(w_e) * r_eci;
										//whole equation is: vi_rel = v_eci - skew(w_e) * r_eci; 

	matrix3x3 A_i2s = q2m(q);
	matrix1x3 vs_rel, aero_torque_component[6], aero_torque;

	for (j = 0; j<3; j++)
		aero_torque.m_data[j] = 0;

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

	int face_s_legth = 6;

	int lenght_face_s = 6;
	double cos[6]; //aero_torque[6];

	matrix1x3 cp_column[6];
	for (i = 0; i < lenght_face_s; i++)
	{
		//cos[i]= face.v(:, i)' * vs_rel / vectorNorm(vs_rel);
		cos[i] = face.v[0][0] * vs_rel.m_data[0] + face.v[1][0] * vs_rel.m_data[1] + face.v[2][0] * vs_rel.m_data[2];
		cos[i] /= vectorNorm1x3(vs_rel);
		//force_i = - 0.5 * ro * cd * vectorNorm(vs_rel) * vs_rel * face.s(i) * max(cos_i, 0) * 1e6; % [N]
		matrix1x3 force;
		matrix1x3 cp_column;
		for (j = 0; j < 3; j++)
		{
			force.m_data[j] = -0.5*ro*cd*vectorNorm(vs_rel)*face.s[i] * max(cos[i], 0) * 1e6 * vs_rel.m_data[j];

			cp_column.m_data[j] = face.cp[j][i];
		}
		matrix3x3 skew_face_cp = skew1x3(cp_column);
		//aero_torque_i = skew(face.cp(:,i)) * force_i;
		for (j = 0; j < 3; j++)
		{
			//multiplying 3x3 by 1x3 (column)
			aero_torque_component[i].m_data[j] = skew_face_cp.m_data[j][0] * force.m_data[0] +
				skew_face_cp.m_data[j][1] * force.m_data[1] + skew_face_cp.m_data[j][2] * force.m_data[2];
		}

		for (j = 0; j < 3; j++)
			aero_torque.m_data[j] += aero_torque_component[i].m_data[j];
	}


	return aero_torque;
}
