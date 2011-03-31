#include "wavelet.h"
#include "haar.h"
#include "testingCommon.h"

int main(){
	// Expected response
	double testResults1[16] =
	{
		25.9375, 3.6875, -4.625, -5.0, -4.0, -1.75, 3.75, -3.75, 11.0, -9.0, 4.5, 2.0, -3.0, 4.5, -0.5, -3.0
	};
	// Testing
	int length = 16;
	double *results = transform(HAAR_WAVELET, test1, length);
	int correct = 0;
	for(int i = 0; i < length; ++i){
		if(doubleEquality(results[i], testResults1[i])){
			correct = 1;
			printf("Incorrect for Haar, test1: [%d] = %f, not %f\n", i, results[i], testResults1[i]);
		}
	}
	return correct;
}
