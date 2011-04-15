/*
 *	Copyright (c) 2011, William Ross
 *	All rights reserved
 *	This software is licensed under a modified BSD license. Please see COPYING for the full text.
 *
 *	haar.h
 *
 */

#ifndef HAAR_H_VZI4HXRC
#define HAAR_H_VZI4HXRC

#include "wavelet.h"
#include "circ_array.h"

double haar_wavelet(circular_array *arr, int i);
double haar_scaling(circular_array *arr, int i);

double haar_predict(circular_array *even, circular_array *odd, int n, int dir);
double haar_update(circular_array *even, circular_array *odd, int n, int dir);

static const wavelet HAAR_WAVELET = {{.classic = {haar_wavelet, haar_scaling}}, false, 2, 2};
static const wavelet HAAR_LIFTING_WAVELET = {{.lifting = {haar_update, haar_predict}}, true, 2, 2};

#endif /* end of include guard: HAAR_H_VZI4HXRC */
