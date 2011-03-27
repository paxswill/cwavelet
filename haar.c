#include "haar.h"


double haar_wavelet(double *v){
	return (v[0] - v[1]) / 2;
}

double haar_scaling(double *v){
	return (v[0] + v[1]) / 2;
}

