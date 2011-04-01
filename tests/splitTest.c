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
	/*
	printf("array = { %2.2f", arr[0]);
	for(int i = 1; i < length; ++i){
		printf(", %2.2f", arr[i]);
	}
	printf("}\n\n");
	*/
	return 0;
}