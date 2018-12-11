#include <stdio.h>
#include <omp.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

void block_matrix_mul(int *A, int *B, int *C, int size, int block_size) {
	for (int jj = 0; jj < size; jj += block_size) {
		for (int kk = 0; kk < size; kk += block_size) {
			for (int i = 0; i < size; i++) {
				for (int j = jj; j < ((jj + block_size) > size ? size : (jj + block_size)); j++) {
					int tmp = 0;
					for (int k = kk; k < ((kk + block_size) > size ? size : (kk + block_size)); k++) {
						tmp += A[i * size + k] * B[k * size + j];
					}
					C[i * size + j] += tmp;
				}
			}
		}
	}
}

void doIt(bool is_optimized) {
	int size = 512 * 3;

	// 256 * 256 * 4 * 3 = 768kb > 256kb (L2)
	// 128 * 128 * 4 * 3 = 196kb < 256kb
	int block_size = int(is_optimized ? 128 : 256);

	printf("size = %d, block = %d\n", size, block_size);

	int *A = new int[size*size];
	int *B = new int[size*size];
	int *C = new int[size*size];

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			A[i*size + j] = rand();
			B[i*size + j] = rand();
			C[i*size + j] = 0;
		}
	}

	double start = omp_get_wtime();

	block_matrix_mul(A, B, C, size, block_size);

	double time = omp_get_wtime() - start;
	printf("Time: %lf\n", time);
}

int main(int argc, char **argv) {
	//doIt(true);
	//return 0;
	if (argc != 2) {
		doIt(false);
		doIt(true);
		getchar();
		return 0;
	}

	bool is_optimized = (strcmp(argv[1], "1") == 0);
	doIt(is_optimized);
	
	return 0;
}
