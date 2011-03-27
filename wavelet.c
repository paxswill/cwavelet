#include "wavelet.h"

int logBase2(uint32_t num){
	/*
	 *	Uses the method described here:
	 *	http://graphics.stanford.edu/~seander/bithacks.html#IntegerLogDeBruijn
	 *	Retrieved March 27, 2011
	 */
	static const int DeBruijn[32] = 
	{
	 0,  9,  1, 10,
	13, 21,  2, 29,
	11, 14, 16, 18,
	22, 25,  3, 30,
	 8, 12, 20, 28,
	15, 17, 24,  7,
	19, 27, 23,  6,
	26,  5,  4, 31	
	};
	
	num |= num >> 1;
	num |= num >> 2;
	num |= num >> 4;
	num |= num >> 8;
	num |= num >> 16;
	return DeBruijn[(uint32_t)(num * 0x07C4ACDDU) >> 27];
}


waveletContainer * createWavelet(double *input, int length, int wavelet){
	waveletContainer *container = (waveletContainer *)malloc(sizeof(waveletContainer));
	if(wavelet == HAAR_WAVELET){
		// Haar Wavelet
		container->wavelet = haar_wavelet;
		container->scaling = haar_scaling;
	}
	// Pad to a value of 2^n
	int l2 = logBase2(length);
	int paddedLength = pow(2, l2);
	if(l2 > paddedLength){
		paddedLength<<=1;
	}
	double *realInput = (double *)malloc(sizeof(double) * paddedLength);
	memcpy(realInput, input, length);
	// Fill in the rest with zeros
	for(int i = length; i < paddedLength; ++i){
		realInput[i] = 0;
	}
	container->input = realInput;
	container->length = paddedLength;
	// Create the output bands
	int numBands = paddedLength / 2;
	double **bands = (double **)malloc(numBands * sizeof(double *));
	for(int i = 0; i < numBands; ++i){
		double *band = calloc(pow(2, i), sizeof(double));
	}
	container->bands = bands;
	return container;
}

void destroyWavelet(waveletContainer *wavelet){
	// Free the input
	free(wavelet->input);
	// Free the bands
	int numBands = wavelet->length / 2;
	for(int i = 0; i < numBands; ++i){
		free(wavelet->bands[i]);
	}
	free(wavelet->bands);
	free(wavelet);
}
