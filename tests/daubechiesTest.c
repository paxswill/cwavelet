#include "wavelet.c"
#include "testingCommon.h"

int main(){
	double testResults1[16] =
	{
		81.68678160629223, 65.03787548991632, -21.99687911409188, -3.5887080697348566, 1.5744373529102234, 1.0693920339161327, -3.64054445662277, -17.71257707372464, -8.004808026796608, 6.322484233630213, 4.302699855549527, -9.072269818564628, 3.0018030100487243, 3.3020988521999524, -1.3541543939428546, 10.69453444330076
	};
	waveletContainer *c = createWavelet((double *)test1, 16, DAUBECHIES_4_WAVELET);
	transform(c);
	int correct = 0;
	for(int i = 0; i < c->input->length; ++i){
		if(doubleEquality(c->output->arr[i], testResults1[i])){
			correct = 1;
			printf("Incorrect for Daubechies, test1: [%d] = %f, not %f\n", i, c->output->arr[i], testResults1[i]);
		}
	}
	destroyWavelet(c);
	return correct;
}
