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
#include "circ_array.h"
#include "haar.h"

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

static const wavelet DAUBECHIES_2_WAVELET = {daubechies_2_wavelet, daubechies_2_scaling, 2, 2};
static const wavelet DAUBECHIES_4_WAVELET = {daubechies_4_wavelet, daubechies_4_scaling, 2, 4};
static const wavelet DAUBECHIES_6_WAVELET = {daubechies_6_wavelet, daubechies_6_scaling, 2, 6};
static const wavelet DAUBECHIES_8_WAVELET = {daubechies_8_wavelet, daubechies_8_scaling, 2, 8};
static const wavelet DAUBECHIES_10_WAVELET = {daubechies_10_wavelet, daubechies_10_scaling, 2, 10};

#endif /* end of include guard: DAUBECHIES_H_4IFSHX8 */
