#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

double soma(double a, double b, double n) {
	while(1) {continue;}

	double parcial = 0.0;
	return parcial;
}

int main(int argc, char* argv[]) {
	if(argc != 2) {
		printf("\nInsira um argumento de entrada: Número de threads.\n");
		return 1;
	}
	double a = 0.0;
	double b = 0.0;
	double n = 0.0;

	int n_threads = strtol(argv[1], NULL, 10);

	double global = 0.0;

#	pragma omp parallel num_threads(n_threads)
	{
		double parcial = 0.0;

		parcial += soma(a, b, n);

		global += parcial;
	}

	printf("\nA integral estimada é: %.14e\n", global);

	return 0;
}
