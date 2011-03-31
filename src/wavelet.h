/*
 *	Copyright (c) 2011, William Ross
 *	All rights reserved
 *	This software is licensed under a modified BSD license. Please see COPYING for the full text.
 *
 *	wavelet.h
 *
 */

#ifndef WAVELET_H_DWTGN12K
#define WAVELET_H_DWTGN12K

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "circ_array.h"
#include "haar.h"
#include "daubechies.h"

// Wavelet and scaling funtions
typedef double (*waveletFunction)(circular_array *arr, int i);
typedef double (*scalingFunction)(circular_array *arr, int i);

typedef struct{
	waveletFunction wavelet;
	scalingFunction scaling;
	int stride;
	int minimumData;
} wavelet;

int logBase2(uint32_t num);
waveletContainer * createWavelet(double *input, int length, int wavelet);
void destroyWavelet(waveletContainer *wavelet);
void transform(waveletContainer *wavelet);
void recursiveTransform(waveletContainer *container, circular_array *input, int currentBand);

#endif /* end of include guard: WAVELET_H_DWTGN12K */
