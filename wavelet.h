#ifndef WAVELET_H_DWTGN12K
#define WAVELET_H_DWTGN12K

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


#endif /* end of include guard: WAVELET_H_DWTGN12K */
