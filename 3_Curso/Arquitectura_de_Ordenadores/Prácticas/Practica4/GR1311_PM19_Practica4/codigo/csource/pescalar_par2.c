// ----------- Arqo P4-----------------------
// pescalar_par2
//
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "arqo4.h"

int main(int argc, char **argv)
{
	float *A=NULL, *B=NULL;
	long long k=0;
	struct timeval fin,ini;
	float sum=0;
	int size;

	if(argc == 3){
		size = atoi(argv[1]);
		printf("--> Se ha introducido el tamanio deseado para los vectores: %d\n", size);
		int n_thr = atoi(argv[2]);
		printf("--> Se ha introducido el numero de hilos deseado: %d\n", n_thr);
		omp_set_num_threads(n_thr);
	}else{
		printf("--> No se ha introducido un tamanio para los vectores y/o el numero de hilos, se tomaran valores por defecto\n");
		size = M;
	}
	
	A = generateVector(size);
	B = generateVector(size);
	if ( !A || !B )
	{
		printf("Error when allocationg matrix\n");
		freeVector(A);
		freeVector(B);
		return -1;
	}
	
	gettimeofday(&ini,NULL);
	/* Bloque de computo */
	sum = 0;
	#pragma omp parallel for reduction(+:sum)
	for(k=0;k<size;k++)
	{
		sum = sum + A[k]*B[k];
	}
	/* Fin del computo */
	gettimeofday(&fin,NULL);

	printf("Resultado: %f\n",sum);
	printf("Tiempo: %f\n", ((fin.tv_sec*1000000+fin.tv_usec)-(ini.tv_sec*1000000+ini.tv_usec))*1.0/1000000.0);
	freeVector(A);
	freeVector(B);

	return 0;
}
