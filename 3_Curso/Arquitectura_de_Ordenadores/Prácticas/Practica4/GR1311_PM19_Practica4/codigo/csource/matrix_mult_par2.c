#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

#include "arqo4.h"

float** compute_matrix_mult(float **m1, float **m2, float **res, int n);

int main(int argc, char **argv){
	int n, n_thr;
	float **m1=NULL;
	float **m2=NULL;
	float **res=NULL;
	struct timeval fin,ini;

	printf("Word size: %ld bits\n",8*sizeof(float));

	if(argc<2){
		printf("Error: introduce matrix size and, optionally, number of threads:\n");
		printf("---> %s <matrix size> [<# threads>]\n", argv[0]);
		return -1;
	}
	else if(argc == 3){
		printf("Number of threads introduced: %d\n", (n_thr=atoi(argv[2])));
		omp_set_num_threads(n_thr);
	}
	n = atoi(argv[1]);

	m1 = generateMatrix(n);
	if(!m1){
		printf("ERROR: unable to allocate memory for matrix 1\n");
		return -1;
	}
	m2 = generateMatrix(n);
	if(!m2){
		printf("ERROR: unable to allocate memory for matrix 2\n");
		return -1;
	}
	res = generateEmptyMatrix(n);
	if(!res){
		printf("ERROR: unable to allocate memory for matrix result\n");
		return -1;
	}

	gettimeofday(&ini,NULL);
	/* Main computation */
	res = compute_matrix_mult(m1, m2, res, n);
	/* End of computation */
	gettimeofday(&fin,NULL);
	if(!res){
		printf("ERROR: unable to compute the matrix multiplication of size %d.\n", n);
		return -1;
	}

	printf("Execution time: %f\n", ((fin.tv_sec*1000000+fin.tv_usec)-(ini.tv_sec*1000000+ini.tv_usec))*1.0/1000000.0);

	freeMatrix(m1);
	freeMatrix(m2);
	freeMatrix(res);
	
	return 0;
}

float** compute_matrix_mult(float **m1, float **m2, float **res, int n){
	int i,j,k;

	for(i=0; i<n; i++){
		#pragma omp parallel for private(k)
		for(j=0; j<n; j++){
			res[i][j] = 0.0;
			for(k=0; k<n; k++){
				res[i][j] += m1[i][k]*m2[k][j];
			}
		}
	}
	return res;
}