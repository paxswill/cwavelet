/*
 *	Copyright (c) 2011, William Ross
 *	All rights reserved
 *	This software is licensed under a modified BSD license. Please see COPYING for the full text.
 *
 *	circ_array.h
 *
 */

#ifndef CIRC_ARRAY_H_1DJIM3I8
#define CIRC_ARRAY_H_1DJIM3I8

#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct{
	double *arr;
	int length;
}circular_array;

// Creation/Destruction
circular_array * createArray(int length);
circular_array * createArrayFromArray(int length, double *arr);
void destroyArray(circular_array *arr);

// Access
void ca_set(circular_array *arr, int i, double d);
double ca_get(circular_array *arr, int i);

//Resizing
void ca_resize(circular_array *arr, int newSize);

#endif /* end of include guard: CIRC_ARRAY_H_1DJIM3I8 */
