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
		container->padding = 0;
	}else if(wavelet == DAUBECHIES_4_WAVELET){
		container->wavelet = daubechies_4_wavelet;
		container->scaling = daubechies_4_scaling;
		container->stride = 2;
		container->padding = 2;
	}else if(wavelet == DAUBECHIES_6_WAVELET){
		container->wavelet = daubechies_6_wavelet;
		container->scaling = daubechies_6_scaling;
		container->stride = 2;
		container->padding = 4;
	}else if(wavelet == DAUBECHIES_8_WAVELET){
		container->wavelet = daubechies_8_wavelet;
		container->scaling = daubechies_8_scaling;
		container->stride = 2;
		container->padding = 6;
	}else if(wavelet == DAUBECHIES_10_WAVELET){
		container->wavelet = daubechies_10_wavelet;
		container->scaling = daubechies_10_scaling;
		container->stride = 2;
		container->padding = 8;
	}
	// Pad to a value of 2^n
	int l2 = logBase2(length);
	int base2Length = pow(2, l2);
	if(l2 > base2Length){
		base2Length<<=1;
	}
	double *realInput;
	realInput = (double *)malloc(sizeof(double) * base2Length);
	memcpy(realInput, input, sizeof(double) * base2Length);
	// Fill in the rest with zeros
	for(int i = length; i < base2Length; ++i){
		realInput[i] = 0;
	}
	// In the case of the D* wavelets, we need to add some overflow so we 
	// don't get null pointers when they go off the far edge (have them act periodic)
	if(container->padding != 0){
		double *newInput = createPaddedInput(realInput, base2Length, container->padding);
		free(realInput);
		realInput = newInput;
	}
	container->input = realInput;
	container->length = base2Length + (container->padding * 2);
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

void transform(waveletContainer *wavelet){
	recursiveTransform(wavelet, wavelet->input, logBase2(wavelet->length));
}

void recursiveTransform(waveletContainer *container, double *input, int currentBand){
	int currentLength = pow(2, currentBand);
	int padding = container->padding;
	double *scalingFactors = (double *)malloc(sizeof(double) * (currentLength / 2));
	// Go through the input array, jumping (stride) elements each step
	for(int i = padding; i < (currentLength + padding); i += container->stride){
		// Position in the scaling factors
		int position = (i / container->stride);
		// Create the wavelet coeffcients for this band
		double value = container->wavelet(input + i);
		container->bands[currentBand - 1][position] = value;
		// Create the scaling coeffcients for this band
		scalingFactors[position] = container->scaling(input + i);
	}
	// Run the next step
	int nextLength = logBase2(pow(2, currentBand - 1));
	double *temp = createPaddedInput(scalingFactors, currentLength / 2, padding);
	free(scalingFactors);
	scalingFactors = temp;
	if(nextLength > 1){
		recursiveTransform(container, scalingFactors, nextLength);
		free(scalingFactors);
	}
}

double * createPaddedInput(double *unpadded, int length, int padding){
	// Create the new array
	double *padded = (double *)malloc(sizeof(double) * (length + padding + padding));
	// Copy the old data in
	memcpy(padded + padding, unpadded, length);
	// Fill in the padding
	for(int i = 0; i < padding; ++i){
		// Front
		padded[i] = padded[length + i];
		// Back
		padded[length + padding + i] = padded[i + padding];
	}
	return padded;
}

