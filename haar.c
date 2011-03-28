#include "haar.h"


double haar_wavelet(circular_array *arr, int i){
	return (ca_get(arr, i) - ca_get(arr, i + 1)) / 2;
}

double haar_scaling(circular_array *arr, int i){
	return (ca_get(arr, i) + ca_get(arr, i + 1)) / 2;
}

