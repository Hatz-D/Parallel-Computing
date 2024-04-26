#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

void fatorial(int n, int* vet) {
	unsigned long long resultado = 1;
        for (int i = 2; i <= n; ++i) {
            	resultado *= i;
		vet[i] = resultado;
        }
       	return;
}

long double soma(int n, int* vet) {
	int posicao = omp_get_thread_num();
	int n_threads = omp_get_num_threads();

	int parcela = n/n_threads;
	int inicio = parcela * posicao;
	int fim = inicio + parcela;

	long double parcial_local = 0.0;

	for(int i = 0; i < fim; i++) {
		parcial_local += 1/vet[inicio+i];
	}
	
	return parcial_local;
}

int main(int argc, char* argv[]) {
	if(argc != 3) {
		printf("\nEntre dois argumentos. 1: Quantidade de threads a serem executadas. 2: Iterações.\n");
		return 1;
	}

	int nThreads = strtol(argv[1], NULL, 10);
	int n = strtol(argv[2], NULL, 10);

	long double global = 0.0;

	int* vet = calloc(n, sizeof(long long));
	vet[0] = 1;
	vet[1] = 1;
	fatorial(n, vet);

#	pragma omp parallel num_threads(nThreads)
	{
		long double parcial = 0.0;
		parcial = soma(n, vet);

#		pragma omp critical
		global += parcial;
	}

	printf("\nResultado da aproximação de Euler: :%Lf\n", global);

	return 0;
}
