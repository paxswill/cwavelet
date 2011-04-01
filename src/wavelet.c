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
	// Run the appripriate transform
	if(w.isLifting){
		liftTransform(w, inputArray->arr, inputArray->length);
	}else{
		standardTransform(w, inputArray);
	}
	//destroyNoCopyArray(inputArray);
	return inputArray->arr;
}

void standardTransform(wavelet w, circular_array *inputArray){
	// Actually run the transform
	for(int i = inputArray->length; i >= w.minimumData; i >>= 1){
		circular_array *constrainedArray = createArrayfromArrayNoCopy(i, inputArray->arr);
		size_t tempSize = sizeof(double) * i;
		double *temp = (double *)malloc(tempSize);
		int split = i >> 1;
		int k = 0;
		for(int j = 0; j < i; j += w.stride){
			double scaleVal = w.detail.scaling(constrainedArray, j);
			double waveVal = w.coarse.wavelet(constrainedArray, j);
			temp[k] = scaleVal;
			temp[k + split] = waveVal;
			++k;
		}
		destroyNoCopyArray(constrainedArray);
		memcpy(inputArray->arr, temp, tempSize);
		free(temp);
	}
}



void liftTransform(wavelet w, double *vals, int length){
	liftSplit(vals, length);
	int half = length >> 1; // length / 2
	for(int i = 0; i < half; ++i){
		vals[half + i] = w.detail.predict(vals[i], vals[half + i]);
		vals[i] = w.coarse.update(vals[i], vals[half + i]);
	}
	if(half > w.minimumData){
		liftTransform(w, vals, half);
	}
}

void liftSplit(double *vals, int length){
	int half = length / 2;
	// shuffle
	for(int i = 0; i < (half / 2); ++i){
		int even = i * 2;
		int odd = even + 1;
		double t = vals[odd];
		vals[odd] = vals[half + even];
		vals[half + even] = t;
	}
	// Now recurse on each half
	if(half >= 4){
		liftSplit(vals, half);
		liftSplit(vals + half, half);
	}
}

void liftMerge(double *vals, int length){
	int half = length / 2;
	// Fix the sub-halves first
	if(half >= 4){
		liftMerge(vals, half);
		liftMerge(vals + half, half);
	}
	// shuffle
	for(int i = 0; i < (half / 2); ++i){
		int even = i * 2;
		int odd = even + 1;
		double t = vals[odd];
		vals[odd] = vals[half + even];
		vals[half + even] = t;
	}
}

