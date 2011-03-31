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

static const wavelet HAAR_WAVELET = 
{
	haar_wavelet,
	haar_scaling,
	2,
	2
};

#endif /* end of include guard: HAAR_H_VZI4HXRC */
