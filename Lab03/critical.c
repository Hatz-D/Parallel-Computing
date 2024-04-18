#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

double f(double x) {
	return 5.0 + sin(x);
}

double soma(double a, double b, double n) {
	int posicao = omp_get_thread_num();
	int n_threads = omp_get_num_threads();

	double h = (b-a)/n;
	double local_n = n/n_threads;
	double local_a = a + posicao * local_n * h;
	double local_b = local_a + h * local_n;
	double parcial = (f(local_a) + f(local_b))/2.0;
	
	for(int i = 1; i <= local_n-1; i++) {
		double x = local_a + i * h;
		parcial += f(x);
	}

	parcial = parcial*h;
	return parcial;
}

int main(int argc, char* argv[]) {
	if(argc != 5) {
		printf("\nInsira quatro argumentos de entrada: a, b, número de trapezoides e número de threads.\n");
		return 1;
	}

	double a = strtod(argv[1], NULL);
	double b = strtod(argv[2], NULL);
	int n = strtol(argv[3], NULL, 10);
	int n_threads = strtol(argv[4], NULL, 10);

	double global = 0.0;

#	pragma omp parallel num_threads(n_threads)
	{
		double parcial = 0.0;

		parcial += soma(a, b, n);
#		pragma omp critical
		global += parcial;
	}

	printf("\nA integral estimada é: %.14e\n", global);

	return 0;
}
