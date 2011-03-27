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
	double *input;
	int length;
	double **bands;
} waveletContainer;

int logBase2(uint32_t num);
waveletContainer * createWavelet(double *input, int length, int wavelet);
void destroyWavelet(waveletContainer *wavelet);


#endif /* end of include guard: WAVELET_H_DWTGN12K */
