#include "wavelet.h"


int main(){
	double arr[8] = {0, 1, 2, 3, 4, 5, 6, 7};

	double *result = liftSplit(arr, 8);

	printf("array = { %f", result[0]);
	for(int i = 1; i < 8; ++i){
		printf(", %f", result[i]);
	}
	printf("}\n");
	return 0;
}