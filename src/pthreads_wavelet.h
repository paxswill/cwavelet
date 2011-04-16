/*
 *	Copyright (c) 2011, William Ross
 *	All rights reserved
 *	This software is licensed under a modified BSD license. Please see COPYING for the full text.
 *
 *	pthreads_wavelet.h
 *
 */

#ifndef PTHREADS_WAVELET_H_9B318X34
#define PTHREADS_WAVELET_H_9B318X34

#include "wavelet.h"

void * liftSplit_pthread_Task(void *arg);
void * liftMerge_pthread_Task(void *arg);
void liftSplit_pthread(double *vals, int length);
void liftMerge_pthread(double *vals, int length);

#endif /* end of include guard: PTHREADS_WAVELET_H_9B318X34 */
