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
		container->stride = 2;
	}
	// Pad to a value of 2^n
	int l2 = logBase2(length);
	int paddedLength = pow(2, l2);
	if(l2 > paddedLength){
		paddedLength<<=1;
	}
	double *realInput = (double *)malloc(sizeof(double) * paddedLength);
	memcpy(realInput, input, sizeof(double) * paddedLength);
	// Fill in the rest with zeros
	for(int i = length; i < paddedLength; ++i){
		realInput[i] = 0;
	}
	container->input = realInput;
	container->length = paddedLength;
	// Create the output bands
	double **bands = (double **)malloc(l2 * sizeof(double *));
	for(int i = 0; i < l2; ++i){
		int length = pow(2, i);
		double *band = calloc(length, sizeof(double));
		bands[i] = band;
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

void runWavelet(waveletContainer *wavelet){
	recursiveWavelet(wavelet, wavelet->input, logBase2(wavelet->length));
}

void recursiveWavelet(waveletContainer *container, double *input, int currentBand){
	int currentLength = pow(2, currentBand);
	double *scalingFactors = (double *)malloc(sizeof(double) * (currentLength / 2));
	// GO through the input array, jumping stride elements each step
	for(int i  = 0; i < currentLength; i += container->stride){
		int position = i / container->stride;
		// Create the wavelet coeffcients for this band
		double value = container->wavelet(input + i);
		container->bands[currentBand - 1][position] = value;
		// Create the scaling coeffcients for this band
		scalingFactors[position] = container->scaling(input + i);
	}
	// Run the next step
	int nextLength = logBase2(pow(2, currentBand - 1));
	printf("Next length: %d\n", nextLength);
	if(nextLength > 1){
		recursiveWavelet(container, scalingFactors, nextLength);
		free(scalingFactors);
	}
}


