#include <stdlib.h>
#include "wavelet.h"


int main(int argc, char **argv){
	int offset = 23;
	if(argc > 1){
		//get the number of the next argument
		offset = atoi(argv[1]);
	}
	int correct = 0;
	// Loop here later
	int length = 1 << offset;
	double *arr = malloc(sizeof(double) * length);
	for(int i = 0; i < length; ++i){
		arr[i] = i;
	}
	liftSplit(arr, length);
	liftMerge(arr, length);
	return 0;
}