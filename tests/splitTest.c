#include "wavelet.h"

extern int threadCount;
int main(){
	int correct = 0;
	// Loop here later
	int length = 1 << 8;
	double *arr = malloc(sizeof(double) * length);
	for(int i = 0; i < length; ++i){
		arr[i] = i;
	}
	printf("thread count: %d\n", threadCount);
	liftSplit(arr, length);
	printf("thread count: %d\n", threadCount);
	liftMerge(arr, length);
	printf("thread count: %d\n", threadCount);
	return 0;
}