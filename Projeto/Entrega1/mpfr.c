#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <gmp.h>
#include <mpfr.h>



int main(int argc, char* argv[]) {
	if(argc != 2) {
		printf("\nEntre um argumento: 1. Quantidade de threads a serem executadas\n");
		return 1;
	}

	mpfr_t x, y, z;
	
	mpfr_init2(x, 100);
	mpfr_out_str(stdout, 10, 0, x, MPFR_RNDU);

	return 0;
}
