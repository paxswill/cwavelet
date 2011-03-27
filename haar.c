#include "haar.h"


double haar_wavelet(double v){
	if(0 <= v && v < 0.5){
		return 1;
	}else if(0.5 <= v && v < 1){
		return -1;
	}else{
		return 0;
	}
}

double haar_scaling(double v){
	if(0 <= v && v < 1){
		return 1;
	}else{
		return 0;
	}
}

