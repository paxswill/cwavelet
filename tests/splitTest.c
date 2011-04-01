#include "wavelet.h"


int main(){
	int correct = 0;
	// Loop here later
	int length = 1 << 20;
	double *arr = malloc(sizeof(double) * length);
	for(int i = 0; i < length; ++i){
		arr[i] = i;
	}

	liftSplit(arr, length);
	
	liftMerge(arr, length);
	return 0;
}