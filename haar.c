#include "haar.h"


double haar_wavelet(circular_array *arr, int i){
	return (ca_get(i, arr) - ca_get(i + 1, arr)) / 2;
}

double haar_scaling(circular_array *arr, int i){
	return (ca_get(i, arr) + ca_get(i + 1, arr)) / 2;
}

