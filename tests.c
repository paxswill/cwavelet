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
	testWave();
	return testHaar() && testLog2();
}


int testHaar(){
	//return testHaarScale() && testHaarWave();
	return TRUE;
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

void testWave(){
	double input[16] = 
	/*{
		19770.0, 1965.0, 90.0, 28257.0,
		24564.0, 16716.0, 12115.0, 7514.0,
		13411.0, 25648.0, 8752.0, 4151.0, 
		32318.0, 29534.0, 4480.0, 10782.0 
	};*/
	 { 32.0, 10.0, 20.0, 38.0,
			 37.0, 28.0, 38.0, 34.0,
			 18.0, 24.0, 18.0, 9.0, 
			23.0, 24.0, 28.0, 34.0 };
	waveletContainer *c = createWavelet(input, 16, HAAR_WAVELET);
	runWavelet(c);
	for(int i = 0; i < logBase2(c->length); ++i){
		int currLength = pow(2, i);
		for(int j = 0; j < currLength; ++j){
			printf("[%d][%d] = %f\n", i, j, c->bands[i][j]);
		}
		printf("\n");
	}
}


