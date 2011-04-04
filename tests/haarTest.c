#include "wavelet.h"
#include "haar.h"
#include "testingCommon.h"

double testResults1[16] =
{
	25.9375, 3.6875, -4.625, -5.0, -4.0, -1.75, 3.75, -3.75, 11.0, -9.0, 4.5, 2.0, -3.0, 4.5, -0.5, -3.0
};

const double testResults3[16] = 
{
	7.5, -4, -2, -2, -1, -1, -1, -1, -0.5, -0.5, -0.5, -0.5, -0.5, -0.5, -0.5, -0.5	
};


int main(){
	// Testing
	int length = 8;
	double test[8] = {50, 20, 90, 40, 5, 60, 35, 80};
	double *results = transform(HAAR_LIFTING_WAVELET, test, length);
	int correct = 0;
	
	for(int i = 0; i < length; ++i){
		if(doubleEquality(results[i], testResults3[i])){
			correct = 1;
			printf("Incorrect for Haar, test1: [%d] = %f, not %f\n", i, results[i], testResults1[i]);
		}
	}
	return correct;
}
