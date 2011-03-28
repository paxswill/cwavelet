#include "daubechies.h"

static const double d4_coeff[4] = {0.6830127, 1.1830127, 0.3169873, 0.1830127};
static const double d6_coeff[6] = {0.47046721, 1.14111692, 0.650365, 0.19093442, 0.12083221, 0.0498175};
static const double d8_coeff[8] = {0.32580343, 1.01094572, 0.8922014, 0.03957503, 0.26450717, 0.0436163, 0.0465036, 0.01498699};
static const double d10_coeff[10] = {0.22641898, 0.85394354, 1.02432694, 0.19576696, 0.34265671, 0.04560113, 0.10970265, 0.00882680, 0.01779187, 0.00471742793};

double computeGeneralDaubechiesScaling(const double *coeffs, int daubechiesNum, circular_array *arr, int i){
	double sum = 0;
	for(int i = 0; i < daubechiesNum - 1; ++i){
		// Wavelet coeffcients are related to the scaling coefficients by reversing
		// the scaling coefficients and inverting every other coefficient
		double wave_coeff = coeffs[daubechiesNum - 1 - i];
		wave_coeff = i % 2 == 0 ? wave_coeff : -1 * wave_coeff;
		sum += wave_coeff * ca_get(arr, i);
	}
	return sum;
}

double computeGeneralDaubechiesWavelet(const double *coeffs, int daubechiesNum, circular_array *arr, int i){
	double sum = 0;
	for(int i = 0; i < daubechiesNum - 1; ++i){
		sum += coeffs[i] * ca_get(arr, i);
	}
	return sum;
}


// D2 is the same as Haar
double daubechies_2_wavelet(circular_array *arr, int i){
	return haar_wavelet(arr, i);
}

double daubechies_2_scaling(circular_array *arr, int i){
	return haar_scaling(arr, i);
}

double daubechies_4_wavelet(circular_array *arr, int i){
	return computeGeneralDaubechiesWavelet(d4_coeff, 4, arr, i);
}

double daubechies_4_scaling(circular_array *arr, int i){
	return computeGeneralDaubechiesScaling(d4_coeff, 4, arr, i);
}

double daubechies_6_wavelet(circular_array *arr, int i){
	return computeGeneralDaubechiesWavelet(d6_coeff, 6, arr, i);
}

double daubechies_6_scaling(circular_array *arr, int i){
	return computeGeneralDaubechiesScaling(d6_coeff, 6, arr, i);
}

double daubechies_8_wavelet(circular_array *arr, int i){
	return computeGeneralDaubechiesWavelet(d8_coeff, 8, arr, i);
}

double daubechies_8_scaling(circular_array *arr, int i){
	return computeGeneralDaubechiesScaling(d8_coeff, 8, arr, i);
}

double daubechies_10_wavelet(circular_array *arr, int i){
	return computeGeneralDaubechiesWavelet(d10_coeff, 10, arr, i);
}

double daubechies_10_scaling(circular_array *arr, int i){
	return computeGeneralDaubechiesScaling(d10_coeff, 10, arr, i);
}
