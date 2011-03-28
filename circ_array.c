#include "circ_array.h"

// Creation/Destruction
circular_array * createArray(int length){
	circular_array *arr = (circular_array *)malloc(sizeof(circular_array));
	arr->length = length;
	arr->arr = (double *)malloc(sizeof(double) * length);
	return arr;
}

void destroyArray(circular_array *arr){
	free(arr->arr);
	free(arr);
}

// Access
void ca_set(circular_array *arr, int i, double d){
	assert(arr != NULL);
	assert(i < arr->length);
	arr->arr[i] = d;
}

double ca_get(circular_array *arr, int i){
	assert(arr != NULL);
	int newIndex;
	if(i > 0){
		newIndex = i % arr->length;
	}else{
		newIndex = (i % arr->length) + arr->length;
	}
	return arr->arr[i];
}


//Resizing
void ca_resize(circular_array *arr, int newSize){
	arr->arr = (double *)realloc(arr->arr, sizeof(double) * newSize);
}

