#include "circ_array.h"

int main(){
	circular_array *c = createArray(7);
	for(int i = 0; i < 7; ++i){
		ca_set(c, i, i);
	}
	int isCorrect = 0;
	//Check
	for(int i = 0; i < 7; ++i){
		if(ca_get(c, i) != i){
			isCorrect = 1;
			printf("Failure in Circular array, piecewise, function access. Should be %d, is %f\n", i, ca_get(c, i));
		}
		if(c->arr[i] != i){
			isCorrect = 1;
			printf("Failure in Circular array, piecewise, raw access. Should be %d, is %f\n", i, ca_get(c, i));
		}
	}
	for(int i = 7; i < 14; ++i){
		double testVal = i - 7.0;
		if(ca_get(c, i) != testVal){
			isCorrect = 1;
			printf("Failure in Circular array, piecewise, function access, overflow. Should be %f, is %f\n", testVal, ca_get(c, i));
		}
	}
	return isCorrect;
}
