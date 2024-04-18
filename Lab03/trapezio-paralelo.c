#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

double soma(double a, double b, double n) {
	int posicao = omp_get_thread_num();
	int n_threads = omp_get_num_threads();

}

int main(int argc, char* argv[]) {
	if(argc != 4) {
		printf("\nInsira quatro argumentos de entrada: a, b, número de trapezoides e número de threads.\n");
		return 1;
	}

	double a = strtod(argv[1], NULL, 10);
	double b = strtod(argv[2], NULL, 10);
	int n = strtol(argv[3], NULL, 10);
	int n_threads = strtol(argv[4], NULL, 10);

	double global = 0.0;

#	pragma omp parallel num_threads(n)
	{
		double parcial = 0.0;

		parcial += soma(a, b, n);

		global += parcial;
	}



	return 0
}
