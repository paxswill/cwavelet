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

double haar_predict(double even, double odd){
	return odd - even;
}

double haar_update(double even, double odd){
	return even + (odd / 2);
}
