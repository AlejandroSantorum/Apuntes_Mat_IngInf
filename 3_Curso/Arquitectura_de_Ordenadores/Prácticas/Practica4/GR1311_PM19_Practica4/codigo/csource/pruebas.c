#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

#include "arqo4.h"

void compute();
void print_array(int *array, int n);
void print_matrix(int matrix[4][4], int n);

int main(int argc, char **argv){
	int n_thr;

	if(argc != 2){
		printf("Introduce number of threads\n");
		return -1;
	}
	n_thr = atoi(argv[1]);
	omp_set_num_threads(n_thr);

	compute();

	return 0;
}

void compute(){
	int i,j,k,sum;
	int array1[4] = {0, 1, 2, 10};
	int array2[4] = {0, -1, -2, -10};
	int matrix1[4][4] = {{1, 1, 1, 1}, {10,10,10,10}, {100,100,100,100}, {-1,-1,-1,-1}};
	int matrix2[4][4] = {{10, 10, 10, 10}, {-10,-10,-10,-10}, {100,100,100,100}, {1,1,1,1}};
	int res[4][4] = {{}};

	/* BUCLE 3 */
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			sum = 0;
			#pragma omp parallel for reduction(+:sum)
			for(k=0; k<4; k++){
				sum += matrix1[i][k] * matrix2[k][j];
			}
			res[i][j] = sum;
		}
	}

	print_matrix(res, 4);
	print_array(array1, 4);
	print_array(array2, 4);
	/*
		BUCLE 2

	for(i=0; i<4; i++){
		#pragma omp parallel for private(k)
		for(j=0; j<4; j++){
			res[i][j] = 0;
			for(k=0; k<4; k++){
				res[i][j] += matrix1[i][k] * matrix2[k][j];
			}
		}
	}*/

	/*
		BUCLE 1

	#pragma omp parallel for private(j, k)
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			res[i][j] = 0;
			for(k=0; k<4; k++){
				res[i][j] += matrix1[i][k] * matrix2[k][j];
			}
		}
	}*/
}

void print_array(int *array, int n){
	int i;
	for(i=0; i<n; i++){
		printf("%d ", array[i]);
	}
	printf("\n");
}

void print_matrix(int matrix[4][4], int n){
	int i,j;
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}

