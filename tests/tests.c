/*
 *	Copyright (c) 2011, William Ross
 *	All rights reserved
 *	This software is licensed under a modified BSD license. Please see COPYING for the full text.
 *
 *	tests.c
 *
 */

#include "tests.h"

const double test1[16] = 
{
	32.0, 10.0, 20.0, 38.0,
 	37.0, 28.0, 38.0, 34.0,
 	18.0, 24.0, 18.0,  9.0, 
 	23.0, 24.0, 28.0, 34.0
};

const double test2[16] =
{
	19770.0, 1965.0, 90.0, 28257.0,
	24564.0, 16716.0, 12115.0, 7514.0,
	13411.0, 25648.0, 8752.0, 4151.0, 
	32318.0, 29534.0, 4480.0, 10782.0 
};

int main(int arcg, char **argv){
	errorMessage = "";
	errorValue = 1337;
	bool allPassed = true;
	allPassed = testLog2() ? allPassed : false;
	allPassed = testHaar() ? allPassed : false;
	allPassed = testDaubechies() ? allPassed : false;
	allPassed = testCircPiecewise() ? allPassed : false;
	allPassed = testSplit() ? allPassed : false;
	
	if(allPassed){
		printf("Tests Passed\n");
	}else{
		printf("Some tests failed,  check the error log\n");
	}
}

void testFail(){
	printf("Test Failed: %s with value: %f\n", errorMessage, errorValue);
}

bool testLog2(){
	int position = 32;
	for(uint32_t i = 0x100000000; i > 0; i >>= 1){
		if(logBase2(i) != position){
			errorValue = logBase2(i);
			errorMessage = "logBase2 Failed";
			return false;
		}
		--position;
	}
	return true;
}

bool testHaar(){
	// Expected response
	double testResults1[16] =
	{
		25.9375, 3.6875, -4.625, -5.0, -4.0, -1.75, 3.75, -3.75, 11.0, -9.0, 4.5, 2.0, -3.0, 4.5, -0.5, -3.0
	};
	// Testing
	waveletContainer *c = createWavelet((double *)test1, 16, HAAR_WAVELET);
	transform(c);
	bool correct = true;
	for(int i = 0; i < c->input->length; ++i){
		if(doubleEquality(c->output->arr[i], testResults1[i])){
			correct = false;
			printf("Incorrect for Haar, test1: [%d] = %f, not %f\n", i, c->output->arr[i], testResults1[i]);
		}
	}
	destroyWavelet(c);
	return true;
}


bool testDaubechies(){
	double testResults1[16] =
	{
		81.68678160629223, 65.03787548991632, -21.99687911409188, -3.5887080697348566, 1.5744373529102234, 1.0693920339161327, -3.64054445662277, -17.71257707372464, -8.004808026796608, 6.322484233630213, 4.302699855549527, -9.072269818564628, 3.0018030100487243, 3.3020988521999524, -1.3541543939428546, 10.69453444330076
	};
	waveletContainer *c = createWavelet((double *)test1, 16, DAUBECHIES_4_WAVELET);
	transform(c);
	bool correct = true;
	for(int i = 0; i < c->input->length; ++i){
		if(doubleEquality(c->output->arr[i], testResults1[i])){
			correct = false;
			printf("Incorrect for Daubechies, test1: [%d] = %f, not %f\n", i, c->output->arr[i], testResults1[i]);
		}
	}
	destroyWavelet(c);
	return true;
}


bool testCircPiecewise(){
	circular_array *c = createArray(7);
	for(int i = 0; i < 7; ++i){
		ca_set(c, i, i);
	}
	bool isCorrect = true;
	//Check
	for(int i = 0; i < 7; ++i){
		if(ca_get(c, i) != i){
			isCorrect = false;
			printf("Failure in Circular array, piecewise, function access. Should be %d, is %f\n", i, ca_get(c, i));
		}
		if(c->arr[i] != i){
			isCorrect = false;
			printf("Failure in Circular array, piecewise, raw access. Should be %d, is %f\n", i, ca_get(c, i));
		}
	}
	for(int i = 7; i < 14; ++i){
		double testVal = i - 7.0;
		if(ca_get(c, i) != testVal){
			isCorrect = false;
			printf("Failure in Circular array, piecewise, function access, overflow. Should be %f, is %f\n", testVal, ca_get(c, i));
		}
	}
	return isCorrect;
}

bool testSplit(){
	double arr[8] = {0, 1, 2, 3, 4, 5, 6, 7};
	circular_array *c = createArrayFromArray(8, arr);


	double *array = c->arr;
	int length = c->length;
	int half = length / 2;
	for(int i = 0; i < half; ++i){
		int even = i;
		int odd = even + 1;
		if(odd < length){
			double t = array[odd];
			printf("temp: %f\n", t);
			array[odd] = array[even + half];
			array[even + half] = t;
		}
	}

	printf("array = { %f", array[0]);
	for(int i = 1; i < 8; ++i){
		printf(", %f", array[0]);
	}
	printf("}\n");
	return true;
}
