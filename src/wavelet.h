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
#include <stdbool.h>
#include <stdarg.h>
#include "circ_array.h"

// Wavelet and scaling funtions
typedef double (*waveletFunction)(circular_array *arr, int i);
typedef double (*scalingFunction)(circular_array *arr, int i);

typedef double (*liftingForward)(double *vals, int length);
typedef double (*liftingInverse)(double *vals, int length);

typedef double (*liftingUpdate)(circular_array *even, circular_array *odd, int n, int dir);
typedef double (*liftingPredict)(circular_array *even, circular_array *odd, int n, int dir);

typedef struct{
	liftingUpdate update;
	liftingPredict predict;
} liftingFunctions;

typedef struct{
	waveletFunction wavelet;
	scalingFunction scaling;
} classicFunctions;


typedef struct{
	// Wavelet functions
	union{
		classicFunctions classic;
		liftingFunctions lifting;
	}wavelet;
	
	bool isLifting;
	int stride;
	int minimumData;
} wavelet;

int logBase2(uint32_t num);
double * transform(wavelet w, double *input, int length);

// Standard transforms
void standardTransform(wavelet w, circular_array *inputArray);

// Lifting functions
void liftTransform(wavelet w, circular_array *inputArray);
void liftSplit(double *vals, int length);
void liftMerge(double *vals, int length);

#endif /* end of include guard: WAVELET_H_DWTGN12K */
