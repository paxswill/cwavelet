#ifndef WAVELET_H_DWTGN12K
#define WAVELET_H_DWTGN12K

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "haar.h"

typedef double (*waveletFunction)(double);
typedef double (*scalingFunction)(double);

typedef struct{
	waveletFunction wavelet;
	scalingFunction scaling;
	double *inputVector;
	int length;
	double *outputVector;
} waveletContainer;


waveletContainer createWavelet();

int logBase2(uint32_t num);
waveletContainer createWavelet(double *input, int length, int wavelet);

#endif /* end of include guard: WAVELET_H_DWTGN12K */
