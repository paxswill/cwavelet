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

double haar_predict(double even, double odd);
double haar_update(double even, double odd);

static const wavelet HAAR_WAVELET = {{.wavelet = haar_wavelet}, {.scaling = haar_scaling}, false, 2, 2};
static const wavelet HAAR_LIFTING_WAVELET = {{.update = haar_update}, {.predict = haar_predict}, true, 2, 2};

#endif /* end of include guard: HAAR_H_VZI4HXRC */
