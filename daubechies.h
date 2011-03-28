#ifndef DAUBECHIES_H_4IFSHX8
#define DAUBECHIES_H_4IFSHX8

#include <stdlib.h>
#include "circ_array.h"
#include "haar.h"

#define DAUBECHIES_2_WAVELET 32036
#define DAUBECHIES_4_WAVELET 31573
#define DAUBECHIES_6_WAVELET 32423
#define DAUBECHIES_8_WAVELET 23163
#define DAUBECHIES_10_WAVELET 26856

double computeGeneralDaubechiesScaling(const double *coeffs, int daubechiesNum, circular_array *arr, int i);
double computeGeneralDaubechiesWavelet(const double *coeffs, int daubechiesNum, circular_array *arr, int i);

double daubechies_2_wavelet(circular_array *arr, int i);
double daubechies_2_scaling(circular_array *arr, int i);

double daubechies_4_wavelet(circular_array *arr, int i);
double daubechies_4_scaling(circular_array *arr, int i);

double daubechies_6_wavelet(circular_array *arr, int i);
double daubechies_6_scaling(circular_array *arr, int i);

double daubechies_8_wavelet(circular_array *arr, int i);
double daubechies_8_scaling(circular_array *arr, int i);

double daubechies_10_wavelet(circular_array *arr, int i);
double daubechies_10_scaling(circular_array *arr, int i);

#endif /* end of include guard: DAUBECHIES_H_4IFSHX8 */
