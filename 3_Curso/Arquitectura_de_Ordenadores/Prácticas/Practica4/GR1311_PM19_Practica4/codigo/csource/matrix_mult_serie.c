#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "arqo4.h"

float** compute_matrix_mult(float **m1, float **m2, float **res, int n);

int main(int argc, char **argv){
	int n;
	float **m1=NULL;
	float **m2=NULL;
	float **res=NULL;
	struct timeval fin,ini;

	printf("Word size: %ld bits\n",8*sizeof(float));

	if(argc!=2){
		printf("Error: format -> %s <matrix size>\n", argv[0]);
		return -1;
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
	float aux;
	int i,j,k;

	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			aux = 0;
			for(k=0; k<n; k++){
				aux += m1[i][k]*m2[k][j];
			}
			res[i][j] = aux;
		}
	}
	return res;
}