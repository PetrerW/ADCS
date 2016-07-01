double aeroDragTorque(double r_eci, double v_eci, double* q, double face, double R_z) //I don't know global value R_z so i'll set this as parameter
{
	double w_ez = 7.2921158553e-5; //[rad/s]
	double w_e[3] = { w_ez * 1, 0, 0 }; //earth rate vector in eci
	double vi_rel = v_eci - skew(w_e) * r_eci; //relative satellite velocity to the atmosphere in eci [km/s]
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

