/*
 *	Copyright (c) 2011, William Ross
 *	All rights reserved
 *	This software is licensed under a modified BSD license. Please see COPYING for the full text.
 *
 *	circ_array.c
 *
 */

#include "circ_array.h"

// Creation/Destruction
circular_array * createArray(int length){
	circular_array *arr = (circular_array *)malloc(sizeof(circular_array));
	arr->length = length;
	arr->arr = (double *)malloc(sizeof(double) * length);
	return arr;
}

circular_array * createArrayFromArray(int length, double *arr){
	circular_array *c = createArray(length);
	memcpy(c->arr, arr, sizeof(double) * length);
	return c;
}

circular_array * copyArray(circular_array *arr){
	return createArrayFromArray(arr->length, arr->arr);
}

circular_array * createArrayfromArrayNoCopy(int length, double *arr){
	circular_array *c = (circular_array *)malloc(sizeof(circular_array));
	c->length = length;
	c->arr = arr;
	return c;
}

void destroyArray(circular_array *arr){
	free(arr->arr);
	free(arr);
}

void destroyNoCopyArray(circular_array *arr){
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
	int newIndex = i;
	if(i < 0 || i >= arr->length){
		if(i > 0){
			newIndex = i % arr->length;
		}else{
			newIndex = (i % arr->length) + arr->length;
		}
	}
	return arr->arr[newIndex];
}


//Resizing
void ca_resize(circular_array *arr, int newSize){
	if(newSize != arr->length){
		arr->arr = (double *)realloc(arr->arr, sizeof(double) * newSize);
	}
}

// Printing
void ca_print(circular_array *arr){
	ca_fprint(arr, stdout);
}

void ca_fprint(circular_array *arr, FILE *f){
	for(int i = 0; i < arr->length; ++i){
		fprintf(f, "arr[%3d] = % 3.8f\n", i, arr->arr[i]);
	}
}
