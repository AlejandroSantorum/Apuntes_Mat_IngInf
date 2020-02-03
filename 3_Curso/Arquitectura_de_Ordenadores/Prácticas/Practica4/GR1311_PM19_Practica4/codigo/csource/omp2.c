// ----------- Arqo P4-----------------------
// Programa que prueba la diferencias en la declaración 
// de la privacidad de variables en OpenMP.
//
#include <omp.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int tid;
	int a,b,c;

	a = 1;
	b = 2;
	c = 3;
	
	omp_set_num_threads(4);

	printf("Inicio: a = %d,\t b = %d,\t c = %d\n", a, b, c);
	printf("\t &a = %p,x\t &b = %p,\t &c = %p\n\n", &a, &b, &c);
	
	#pragma omp parallel shared(b) private(tid,a) firstprivate(c)
	{
		tid = omp_get_thread_num();
		
		printf("[Hilo %d]-1: a = %d,\t b = %d,\t c = %d\n", tid, a, b, c);
		printf("[Hilo %d]\t &a = %p,\t &b = %p,\t &c = %p\n", tid, &a, &b, &c);
	
		b += 2;
		
		c = a*a + 3;
		a = b*3 + c;
		
		printf("[Hilo %d]-2: a = %d,\t b = %d,\t c = %d\n", tid, a, b, c);
		printf("\n");
	}
	
	printf("\nFin: a = %d,\t b = %d,\t c = %d\n", a, b, c);
	printf("\t &a = %p,\t &b = %p,\t &c = %p\n\n", &a, &b, &c);
	
	return 0;
}
