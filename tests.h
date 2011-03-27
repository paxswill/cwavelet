#ifndef TESTS_H_53CI45QC
#define TESTS_H_53CI45QC

#include "haar.h"

static char *errorMessage;
static double errorValue;

int main(int arcg, char **argv);

// Haar tests
int testHaarWave();
int testHaarScale();
int testHaar();

#endif /* end of include guard: TESTS_H_53CI45QC */
