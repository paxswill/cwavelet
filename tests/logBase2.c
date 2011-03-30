// Test logBase2 from wavelet.c

#include "wavelet.h"

int main(){
	int position = 32;
	for(uint32_t i = 0x100000000; i > 0; i >>= 1){
		if(logBase2(i) != position){
			return 1;
		}
		--position;
	}
	return 0;
}