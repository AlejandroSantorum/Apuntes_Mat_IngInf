// ----------- Arqo P4-----------------------
// Programa que crea hilos utilizando OpenMP
//
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int tid,nthr,nproc;
	int arg;

	if(argc != 2){
		printf("Numero de parametros de entrada erroneo.\n");
		printf("Por favor, introduzca el numero de hilos deseado para su lanzamiento\n");
		exit(EXIT_FAILURE);
	}
	
	nproc = omp_get_num_procs();
	printf("Hay %d cores disponibles\n", nproc);

	arg = atoi( argv[1] );	
	omp_set_num_threads(arg);
	nthr = omp_get_max_threads();
	printf("Me han pedido que lance %d hilos\n", nthr);
	
	#pragma omp parallel private(tid)
	{	
		tid = omp_get_thread_num();
		nthr = omp_get_num_threads();
		printf("Hola, soy el hilo %d de %d\n", tid, nthr);
	}
	
	return 0;
}
