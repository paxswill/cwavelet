#ifndef TESTS_H_53CI45QC
#define TESTS_H_53CI45QC

#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include "haar.h"
#include "wavelet.h"

static char *errorMessage;
static double errorValue;

int main(int arcg, char **argv);
void testFail();

// Haar
bool testHaar();

// Daubechies
bool testDaubechies();

// Wavelet tests
bool testLog2();

#endif /* end of include guard: TESTS_H_53CI45QC */
