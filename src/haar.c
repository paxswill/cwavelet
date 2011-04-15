/*
 *	Copyright (c) 2011, William Ross
 *	All rights reserved
 *	This software is licensed under a modified BSD license. Please see COPYING for the full text.
 *
 *	haar.c
 *
 */

#include "haar.h"

double haar_wavelet(circular_array *arr, int i){
	return (ca_get(arr, i) - ca_get(arr, i + 1)) / 2;
}

double haar_scaling(circular_array *arr, int i){
	return (ca_get(arr, i) + ca_get(arr, i + 1)) / 2;
}

double haar_predict(circular_array *even, circular_array *odd, int n, int dir){
	if(dir == 0){
		return ca_get(odd, n) - ca_get(even, n);
	}else{
		return ca_get(odd, n) + ca_get(even, n);
	}
}

double haar_update(circular_array *even, circular_array *odd, int n, int dir){
	if(dir == 0){
		return ca_get(even, n) + (ca_get(odd, n) / 2);
	}else{
		return ca_get(even, n) - (ca_get(odd, n) / 2);
	}
	
}
