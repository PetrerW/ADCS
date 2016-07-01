#include <math.h>
#include <conio.h>
#include <time.h>

int main()
{
    time_t t = time(NULL);
struct tm tm = *gmtime(&t);

// http://en.cppreference.com/w/c/chrono/tm
// http://en.cppreference.com/w/c/chrono/gmtime
// http://stackoverflow.com/questions/1442116/how-to-get-date-and-time-value-in-c-program

//Julian Date
double jd = 1721013.5 + 367 * (tm.tm_year + 1900)// adding 1900, because tm_year gives year since 1900
				- floor(7/4 * (tm.tm_year + 1900 + floor((tm.tm_mon +1 + 9) / 12))) // adding 1 to tm_mon, because January is 0th month there. + 9 - that was in Matlab algorithm
				+ floor(275 * tm.tm_mon / 9) + tm.tm_mday
				+ (60 * tm.tm_hour + tm.tm_min + (tm.tm_sec + (double)t ) / 60) / 1440; //Here is (tm.tm_sec +t ), but I don't know where does the 't' come from.

// Number of Julian centuries from epoch J2000
double T_uti = (jd - 2451545) / 36525;

double sun_long = 280.460 + 36000.771 * T_uti; // Mean Sun longitude
double sun_anom = 357.5277233 + 35999.05034 * T_uti; // Mean anomaly of the Sun

// Converting mean sun longitude and mean sun anomaly to the range <0,360> [deg]
sun_long = sun_long - floor(sun_long / 360) * 360;
sun_anom = sun_anom - floor(sun_anom / 360) * 360;

// Longitude of ecliptic [rad]
double ecl_long = (sun_long + 1.914666471 * sin(sun_anom * M_PI / 180) + 0.019994643 * sin(2 * sun_anom * M_PI / 180)) * M_PI / 180;
// Obliquity of the ecliptic [rad]
double eps = (23.439291 - 0.0130042 * T_uti) * M_PI / 180;

// earth to sun unit vector
double e2s_unit[3] = {  cos(ecl_long),
                        cos(eps) * sin(ecl_long),
                        sin(eps) * sin(ecl_long)    };

// vectorNorm(e2s_unit):
double e2s_unit_vectorNorm = sqrt(e2s_unit[0]*e2s_unit[0] + e2s_unit[1]*e2s_unit[1] + e2s_unit[2]*e2s_unit[2]); //Sth like lenght of a vector

//Dividing the e2s_unit matrix by it's norm
int i;
for(i=0;i<3;i++)
    e2s_unit[i] = e2s_unit[i] / e2s_unit_vectorNorm;

return 0;
}
