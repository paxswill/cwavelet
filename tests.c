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
	for(int i = 0x100000000; i > 0; i >>= 1){
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
	// Expected responses
	double band10[1] = {3.6875};
	double band11[2] = {-4.625, -5.0};
	double band12[4] = {-4.0, -1.75, 3.75, -3.75};
	double band13[8] = {11.0, -9.0, 4.5, 2.0, -3.0, 4.5, -0.5, -3.0};
	double *testBands1[4] = {band10, band11, band12, band13};
	// Testing
	waveletContainer *c = createWavelet((double *)test1, 16, HAAR_WAVELET);
	transform(c);
	bool correct = true;
	for(int i = 0; i < logBase2(c->input->length); ++i){
		int currLength = pow(2, i);
		for(int j = 0; j < currLength; ++j){
			if(c->bands[i][j] != testBands1[i][j]){
				correct = false;
				printf("Incorrect for Haar, test1: [%d][%d] = %f, not %f\n", i, j, c->bands[i][j], testBands1[i][j]);
			}
		}
	}
	destroyWavelet(c);
	return correct;
}

bool testDaubechies(){
	waveletContainer *c = createWavelet((double *)test1, 16, DAUBECHIES_4_WAVELET);
	transform(c);
	for(int i = 0; i < logBase2(c->input->length); ++i){
		int currLength = pow(2, i);
		for(int j = 0; j < currLength; ++j){
			printf("[%d][%d] = %f\n", i, j, c->bands[i][j]);
		}
		printf("\n");
	}
	destroyWavelet(c);
	return TRUE;
}


