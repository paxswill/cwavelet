#ifndef WAVELET_H_DWTGN12K
#define WAVELET_H_DWTGN12K

#include <stdlib.h>
#include <stdint.h>
#include "haar.h"

typedef double (*waveletFunction)(double);
typedef double (*scalingFunction)(double);
typedef const int waveletName;

typedef struct{
	waveletFunction wavelet;
	scalingFunction scaling;
	double *inputVector;
	int size;
	double *outputVector;
} waveletContainer;


waveletContainer createWavelet();

int logBase2(uint32_t num);

#endif /* end of include guard: WAVELET_H_DWTGN12K */
