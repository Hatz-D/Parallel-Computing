#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <mpfr.h>
#include <gmp.h>

void fatorial(int n, mpfr_t* vet, int nBits) {
	long int posicao = omp_get_thread_num();
	long int n_threads = omp_get_num_threads();

	long int parcela = n/n_threads;
	long int inicio = parcela * posicao;
	long int fim = inicio + parcela - 1;

	if(inicio != 0 && inicio != 1) {
		mpfr_init2(vet[inicio], nBits);
		mpfr_set_d(vet[inicio], (inicio+0.0), MPFR_RNDU);
	}

	for(long int i = inicio+1; i <= fim; ++i) {
		mpfr_init2(vet[i], nBits);
		mpfr_mul_si(vet[i], vet[i-1], i, MPFR_RNDU);
	}
}

int main(int argc, char* argv[]) {
	if(argc != 4) {
		printf("\nErro");
		return 1;
	}

	int nThreads = strtol(argv[1], NULL, 10); 
	int n = strtol(argv[2], NULL, 10); 
	int nBits = strtol(argv[3], NULL, 10);

	mpfr_t* vet = (mpfr_t*) malloc(n * sizeof(mpfr_t));

	mpfr_init2(vet[0], nBits);
        mpfr_set_d(vet[0], 1.0, MPFR_RNDU);

        mpfr_init2(vet[1], nBits);
        mpfr_set_d(vet[1], 1.0, MPFR_RNDU);	

#	pragma omp parallel num_threads(nThreads)
	{
	fatorial(n, vet, nBits);
	}

	int parcela = n/nThreads;
	for(int i = 1; i < nThreads; ++i) {
		for(int j = parcela * i; j <= (parcela * i) + parcela - 1; ++j) { 
			mpfr_mul(vet[j], vet[(parcela*i)-1], vet[j], MPFR_RNDU);
		}
	}

	return 0;
}
