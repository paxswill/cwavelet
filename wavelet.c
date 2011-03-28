/*
 *	Copyright (c) 2011, William Ross
 *	All rights reserved
 *	This software is licensed under a modified BSD license. Please see COPYING for the full text.
 *
 *	wavelet.c
 *
 */

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
	// Identify the wavelet
	if(wavelet == HAAR_WAVELET || wavelet == DAUBECHIES_2_WAVELET){
		// Haar Wavelet
		container->wavelet = haar_wavelet;
		container->scaling = haar_scaling;
		container->stride = 2;
		container->minimumData = 2;
	}else if(wavelet == DAUBECHIES_4_WAVELET){
		container->wavelet = daubechies_4_wavelet;
		container->scaling = daubechies_4_scaling;
		container->stride = 2;
		container->minimumData = 4;
	}else if(wavelet == DAUBECHIES_6_WAVELET){
		container->wavelet = daubechies_6_wavelet;
		container->scaling = daubechies_6_scaling;
		container->stride = 2;
		container->minimumData = 6;
	}else if(wavelet == DAUBECHIES_8_WAVELET){
		container->wavelet = daubechies_8_wavelet;
		container->scaling = daubechies_8_scaling;
		container->stride = 2;
		container->minimumData = 8;
	}else if(wavelet == DAUBECHIES_10_WAVELET){
		container->wavelet = daubechies_10_wavelet;
		container->scaling = daubechies_10_scaling;
		container->stride = 2;
		container->minimumData = 10;
	}
	// Pad to a value of 2^n
	int l2 = logBase2(length);
	int base2Length = pow(2, l2);
	if(l2 > base2Length){
		base2Length<<=1;
	}
	circular_array *arr = createArrayFromArray(length, input);
	ca_resize(arr, base2Length);
	// Fill in the rest with zeros
	for(int i = length; i < base2Length; ++i){
		ca_set(arr, i, 0.0);
	}
	container->input = arr;
	// Copy the input to the working output
	double *out = (double *)malloc(base2Length * sizeof(double));
	memcpy(out, arr, base2Length * sizeof(double));
	container->output = out;
	return container;
}

void destroyWavelet(waveletContainer *wavelet){
	// Free the output
	free(wavelet->out);
	// Free the input
	destroyArray(wavelet->input);
	free(wavelet);
}

void transform(waveletContainer *wavelet){
	recursiveTransform(wavelet, wavelet->input, logBase2(wavelet->input->length));
}

void recursiveTransform(waveletContainer *container, circular_array *input, int currentBand){
	circular_array *scalingFactors = createArray(input->length / 2);
	// Go through the input array, jumping (stride) elements each step
	for(int i = 0; i < input->length; i += container->stride){
		// Position in the scaling factors
		int position = (i / container->stride);
		// Create the wavelet coeffcients for this band
		double waveVal = container->wavelet(input, i);
		container->bands[currentBand - 1][position] = waveVal;
		// Create the scaling coeffcients for this band
		double scaleVal = container->scaling(input, i);
		ca_set(scalingFactors, position, scaleVal);
		printf("Wave: %3.8f\tScale: %3.8f\n", waveVal, scaleVal);
	}
	printf("\n");
	// Run the next step
	int nextLength = currentBand - 1;
	if(nextLength >= container->minimumData / 2){
		recursiveTransform(container, scalingFactors, nextLength);
	}else{
		size_t size = sizeof(double) * container->minimumData / 2;
		double *finals = malloc(size);
		memcpy(finals, scalingFactors->arr, size);
		container->finalScales = finals;
	}
	destroyArray(scalingFactors);
}

