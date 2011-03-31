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

double * transform(wavelet w, double *input, int length){
	// Pad to a value of 2^n
	int l2 = logBase2(length);
	int base2Length = pow(2, l2);
	if(l2 > base2Length){
		base2Length<<=1;
	}
	circular_array *inputArray = createArrayFromArray(length, input);
	ca_resize(inputArray, base2Length);
	// Fill in the rest with zeros
	for(int i = length; i < base2Length; ++i){
		ca_set(inputArray, i, 0.0);
	}
	// Actually run the transform
	for(int i = length; i >= w.minimumData; i >>= 1){
		circular_array *constrainedArray = createArrayfromArrayNoCopy(i, inputArray->arr);
		size_t tempSize = sizeof(double) * i;
		double *temp = (double *)malloc(tempSize);
		int split = i >> 1;
		int k = 0;
		for(int j = 0; j < i; j += w.stride){
			double scaleVal = w.scaling(constrainedArray, j);
			double waveVal = w.wavelet(constrainedArray, j);
			temp[k] = scaleVal;
			temp[k + split] = waveVal;
			++k;
		}
		destroyNoCopyArray(constrainedArray);
		memcpy(inputArray->arr, temp, tempSize);
		free(temp);
	}
	destroyNoCopyArray(inputArray);
	return inputArray->arr;
}