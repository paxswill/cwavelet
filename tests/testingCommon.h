#include <math.h>
#include <stdbool.h>

const double test1[16] = 
{
	32.0, 10.0, 20.0, 38.0,
 	37.0, 28.0, 38.0, 34.0,
 	18.0, 24.0, 18.0,  9.0, 
 	23.0, 24.0, 28.0, 34.0
};

const double test2[16] =
{
	19770.0, 1965.0, 90.0, 28257.0,
	24564.0, 16716.0, 12115.0, 7514.0,
	13411.0, 25648.0, 8752.0, 4151.0, 
	32318.0, 29534.0, 4480.0, 10782.0 
};

bool doubleEquality(double a, double b){
	double d = fabs(a - b);
	return d >= 0.0000000000001;
}
