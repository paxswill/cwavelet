#ifndef CIRC_ARRAY_H_1DJIM3I8
#define CIRC_ARRAY_H_1DJIM3I8

#include <stdlib.h>
#include <assert.h>

typedef struct{
	double *arr;
	int length;
}circular_array;

// Creation/Destruction
circular_array * createArray(int length);
void destroyArray(circular_array *arr);

// Access
void set(int i, circular_array *arr, double d);
double get(int i, circular_array *arr);

//Resizing
void resize(circular_array *arr, int newSize);

#endif /* end of include guard: CIRC_ARRAY_H_1DJIM3I8 */
