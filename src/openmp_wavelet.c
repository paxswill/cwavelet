/*
 *	Copyright (c) 2011, William Ross
 *	All rights reserved
 *	This software is licensed under a modified BSD license. Please see COPYING for the full text.
 *
 *	openmp_wavelet.c
 *
 */

#include <omp.h>

void liftSplit_openmp(double *vals, int length){
	int half = length / 2;
	// shuffle
	liftShuffle(vals, length);
	// Now recurse on each half
	if(half >= 4){
		#pragma omp parallel shared(vals)
		{
			liftSplit_openmp(vals, half);
			liftSplit_openmp(vals + half, half);
		}
	}
}

void liftMerge_openmp(double *vals, int length){
	int half = length / 2;
	// Fix the sub-halves first
	if(half >= 4){
		#pragma omp parallel shared(vals)
		{
			liftSplit_openmp(vals, half);
			liftSplit_openmp(vals + half, half);
		}
	}
	// shuffle
	liftShuffle(vals, length);
}
