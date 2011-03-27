#include "tests.h"
#include <math.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0

int main(int arcg, char **argv){
	errorMessage = "";
	errorValue = 1337;
	if(!testAll()){
		printf("Test Failed: %s with value: %f\n", errorMessage, errorValue);
	}else{
		printf("Tests Passed\n");
	}
}

int testAll(){
	return testHaar() && testLog2();
}

// Haar tests
int testHaarWave(){
	if(haar_wavelet(-1.0) != 0.0){
		errorValue = haar_wavelet(-1.0);
		errorMessage = "Haar Wavelet function for -1.0";
		return FALSE;
	}else if(haar_wavelet(-0.0) != 1.0){
		errorValue = haar_wavelet(-0.0);
		errorMessage = "Haar Wavelet function for -0.0";
		return FALSE;
	}else if(haar_wavelet(0.25) != 1.0){
		errorValue = haar_wavelet(0.25);
		errorMessage = "Haar Wavelet function for 0.25";
		return FALSE;
	}else if(haar_wavelet(0.5) != -1.0){
		errorValue = haar_wavelet(0.5);
		errorMessage = "Haar Wavelet function for 0.5";
		return FALSE;
	}else if(haar_wavelet(0.75) != -1.0){
		errorValue = haar_wavelet(0.75);
		errorMessage = "Haar Wavelet function for 0.75";
		return FALSE;
	}else if(haar_wavelet(1.0) != 0.0){
		errorValue = haar_wavelet(1.0);
		errorMessage = "Haar Wavelet function for 1.0";
		return FALSE;
	}else if(haar_wavelet(HUGE_VAL) != 0.0){
		errorValue = haar_wavelet(HUGE_VAL);
		errorMessage = "Haar Wavelet function for infinty";
		return FALSE;
	}
	return TRUE;
}

int testHaarScale(){
	if(haar_scaling(-1.0) != 0){
		errorValue = haar_scaling(-1.0);
		errorMessage = "Haar Scale function for -1.0";
		return FALSE;
	}else if(haar_scaling(0.0) != 1){
		errorValue = haar_scaling(0.0);
		errorMessage = "Haar Scale function for 0.0";
		return FALSE;
	}else if(haar_scaling(-0.0) != 1){
		errorValue = haar_scaling(-0.0);
		errorMessage = "Haar Scale function for -0.0";
		return FALSE;
	}else if(haar_scaling(0.25) != 1){
		errorValue = haar_scaling(0.25);
		errorMessage = "Haar Scale function for 0.25";
		return FALSE;
	}else if(haar_scaling(1.0) != 0){
		errorValue = haar_scaling(1.0);
		errorMessage = "Haar Scale function for 1.0";
		return FALSE;
	}
	return TRUE;
}

int testHaar(){
	return testHaarScale() && testHaarWave();
}

int testLog2(){
	int position = 32;
	for(int i = 0x100000000; i > 0; i >>= 1){
		if(logBase2(i) != position){
			errorValue = logBase2(i);
			errorMessage = "logBase2 Failed";
			return FALSE;
		}
		--position;
	}
	return TRUE;
}
