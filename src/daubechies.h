/*
 *	Copyright (c) 2011, William Ross
 *	All rights reserved
 *	This software is licensed under a modified BSD license. Please see COPYING for the full text.
 *
 *	daubechies.h
 *
 */

#ifndef DAUBECHIES_H_4IFSHX8
#define DAUBECHIES_H_4IFSHX8

#include <stdlib.h>
#include "wavelet.h"

double computeGeneralDaubechiesScaling(const double *coeffs, int daubechiesNum, circular_array *arr, int i);
double computeGeneralDaubechiesWavelet(const double *coeffs, int daubechiesNum, circular_array *arr, int i);

double daubechies_2_wavelet(circular_array *arr, int i);
double daubechies_2_scaling(circular_array *arr, int i);

double daubechies_4_wavelet(circular_array *arr, int i);
double daubechies_4_scaling(circular_array *arr, int i);

double daubechies_6_wavelet(circular_array *arr, int i);
double daubechies_6_scaling(circular_array *arr, int i);

double daubechies_8_wavelet(circular_array *arr, int i);
double daubechies_8_scaling(circular_array *arr, int i);

double daubechies_10_wavelet(circular_array *arr, int i);
double daubechies_10_scaling(circular_array *arr, int i);

static const wavelet DAUBECHIES_2_WAVELET = {{.wavelet = daubechies_2_wavelet}, {.scaling = daubechies_2_scaling}, false, 2, 2};
static const wavelet DAUBECHIES_4_WAVELET = {{.wavelet = daubechies_4_wavelet}, {.scaling = daubechies_4_scaling}, false, 2, 4};
static const wavelet DAUBECHIES_6_WAVELET = {{.wavelet = daubechies_6_wavelet}, {.scaling = daubechies_6_scaling}, false, 2, 6};
static const wavelet DAUBECHIES_8_WAVELET = {{.wavelet = daubechies_8_wavelet}, {.scaling = daubechies_8_scaling}, false, 2, 8};
static const wavelet DAUBECHIES_10_WAVELET = {{.wavelet = daubechies_10_wavelet}, {.scaling = daubechies_10_scaling}, false, 2, 10};

#endif /* end of include guard: DAUBECHIES_H_4IFSHX8 */
