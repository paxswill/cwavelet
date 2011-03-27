#ifndef DAUBECHIES_H_4IFSHX8
#define DAUBECHIES_H_4IFSHX8

#include <stdlib.h>
#include "wavelet.h"
#include "haar.h"

#define DAUBECHIES_2_WAVELET 32036
#define DAUBECHIES_4_WAVELET 31573
#define DAUBECHIES_6_WAVELET 32423
#define DAUBECHIES_8_WAVELET 23163
#define DAUBECHIES_10_WAVELET 26856

double computeGeneralDaubechiesScaling(const double *coeffs, int num, double *v);
double computeGeneralDaubechiesWavelet(const double *coeffs, int num, double *v);

double daubechies_2_wavelet(double *v);
double daubechies_2_scaling(double *v);

double daubechies_4_wavelet(double *v);
double daubechies_4_scaling(double *v);

double daubechies_6_wavelet(double *v);
double daubechies_6_scaling(double *v);

double daubechies_8_wavelet(double *v);
double daubechies_8_scaling(double *v);

double daubechies_10_wavelet(double *v);
double daubechies_10_scaling(double *v);

double * generateCoeffcients(int num);

#endif /* end of include guard: DAUBECHIES_H_4IFSHX8 */
