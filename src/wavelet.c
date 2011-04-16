/*
 *	Copyright (c) 2011, William Ross
 *	All rights reserved
 *	This software is licensed under a modified BSD license. Please see COPYING for the full text.
 *
 *	wavelet.c
 *
 */

#include "wavelet.h"

#ifdef USE_PTHREADS
#warning Using POSIX threads
#include "pthreads_wavelet.c"
#elif defined(USE_OPENMP)
#warning Using OpenMP
#include "openmp_wavelet.c"
#else
#warning Defaulting to a single thread
#include "single_wavelet.c"
#endif

typedef enum{
	FORWARD_TR = 0,
	INVERSE_TR = 1
} transformDirection;

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
		liftTransform(w, inputArray);
	}else{
		standardTransform(w, inputArray);
	}
	//destroyNoCopyArray(inputArray);
	return inputArray->arr;
}

double * inverseTransform(wavelet w, double *input, int length){
	// Assume it's already padded
	circular_array *inputArray = createArrayFromArray(length, input);
	if(w.isLifting){
		liftInverse(w, inputArray);
	}
	return inputArray->arr;
}

void standardTransform(wavelet w, circular_array *inputArray){
	classicFunctions funcs = w.wavelet.classic;
	// Actually run the transform
	for(int i = inputArray->length; i >= w.minimumData; i >>= 1){
		circular_array *constrainedArray = createArrayfromArrayNoCopy(i, inputArray->arr);
		size_t tempSize = sizeof(double) * i;
		double *temp = (double *)malloc(tempSize);
		int split = i >> 1;
		int k = 0;
		for(int j = 0; j < i; j += w.stride){
			double scaleVal = funcs.scaling(constrainedArray, j);
			double waveVal = funcs.wavelet(constrainedArray, j);
			temp[k] = scaleVal;
			temp[k + split] = waveVal;
			++k;
		}
		destroyNoCopyArray(constrainedArray);
		memcpy(inputArray->arr, temp, tempSize);
		free(temp);
	}
}

void liftTransform(wavelet w, circular_array *inputArray){
	int length = inputArray->length;
	int half = length >> 1; // length / 2
	circular_array *even = createArrayfromArrayNoCopy(half, inputArray->arr);
	liftSplit(inputArray->arr, inputArray->length);
	liftPredict(w, inputArray, FORWARD_TR);
	liftUpdate(w, inputArray, FORWARD_TR);
	
	//Debugging stuff
	printf("\n");
	for(int i = 0; i < 8; ++i){
		printf("\t[%d] = %2.5f\n", i, inputArray->arr[i]);
	}
	printf("\n");
	
	if(half >= w.minimumData){
		liftTransform(w, even);
	}
	destroyNoCopyArray(even);
}

void liftInverse(wavelet w, circular_array *inputArray){
	int length = inputArray->length;
	int half = length >> 1; // length / 2
	circular_array *odd = createArrayfromArrayNoCopy(half, (inputArray->arr) + half);
	
	if(half >= w.minimumData){
		liftInverse(w, odd);
	}
	destroyNoCopyArray(odd);
	
	liftUpdate(w, inputArray, INVERSE_TR);
	liftPredict(w, inputArray, INVERSE_TR);
	liftMerge(inputArray->arr, inputArray->length);
}

void liftPredict(wavelet w, circular_array *inputArray, int dir){
	int length = inputArray->length;
	double *vals = inputArray->arr;
	int half = length >> 1; // length / 2
	circular_array *odd = createArrayfromArrayNoCopy(half, vals + half);
	circular_array *even = createArrayfromArrayNoCopy(half, vals);
	// Predict
	for(int i = 0; i < half; ++i){
		//predict(a, b) == b - a
		ca_set(odd, i, w.wavelet.lifting.predict(even, odd, i, dir));
	}
	destroyNoCopyArray(odd);
	destroyNoCopyArray(even);
}

void liftUpdate(wavelet w, circular_array *inputArray, int dir){
	int length = inputArray->length;
	double *vals = inputArray->arr;
	int half = length >> 1; // length / 2
	circular_array *odd = createArrayfromArrayNoCopy(half, vals + half);
	circular_array *even = createArrayfromArrayNoCopy(half, vals);
	// Update
	for(int i = 0; i < half; ++i){
		ca_set(even, i, w.wavelet.lifting.update(even, odd, i, dir));
	}
	destroyNoCopyArray(odd);
	destroyNoCopyArray(even);
}

static inline void liftShuffle(double *vals, int length){
	int half = length / 2;
	for(int i = 0; i < (half / 2); ++i){
		int even = i * 2;
		int odd = even + 1;
		double t = vals[odd];
		vals[odd] = vals[half + even];
		vals[half + even] = t;
	}
}

void liftSplit(double *vals, int length){
#ifdef USE_PTHREADS
	// POSIX threads
	liftSplit_pthread(vals, length);
#elif defined(USE_OPENMP)
	// OpenMP
	liftSplit_openmp(vals, length);
#else
	// Single threaded
	liftSplit_single(vals, length);
#endif
}

void liftMerge(double *vals, int length){
#ifdef USE_PTHREADS
	// POSIX threads
	liftMerge_pthread(vals, length);
#elif defined(USE_OPENMP)
	// OpenMP
	liftMerge_openmp(vals, length);
#else
	// Single threaded
	liftMerge_single(vals, length);
#endif
}
