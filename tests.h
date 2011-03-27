#ifndef TESTS_H_53CI45QC
#define TESTS_H_53CI45QC

#include "haar.h"
#include "wavelet.h"

static char *errorMessage;
static double errorValue;

int main(int arcg, char **argv);
int testAll();

// Haar tests
int testHaarWave();
int testHaarScale();
int testHaar();

// Wavelet tests
int testLog2();
void testWave();

#endif /* end of include guard: TESTS_H_53CI45QC */
