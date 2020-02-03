/*********************************************************/
/*Cálculo PI: Método de integración - Version OpenMP	 */
/*Clausula private + Clausula critical			 */
/*********************************************************/

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main( int argc, char *argv[] ) 
{
	int i, n=100000000, numProcs;
	double x, h, pi, sum = 0.0, t = 0;
	struct timeval t1,t2;
	
	numProcs = omp_get_num_procs();
	omp_set_num_threads( numProcs );

	gettimeofday(&t1,NULL);

	h = 1.0 / (double)n;
	
	#pragma omp parallel private(x, sum) default(shared)
	{
		int tid, numThreads;

		// Obtenemos el numero de procesos lanzados	
        numThreads = omp_get_num_threads();
	
		// Obtenemos nuestro identificador de thread
		tid = omp_get_thread_num();	

		sum = 0.0;
		for(i = tid + 1; i <= n; i += numThreads) 
		{
			x = h * ((double)i - 0.5);
			sum += 4.0 / (1.0 + x*x);
		}
		#pragma omp critical
		pi += sum;
	}	
	pi *= h;

	gettimeofday(&t2,NULL);

	t = (t2.tv_sec -t1.tv_sec) + (t2.tv_usec - t1.tv_usec)/(double)1000000;
	printf("Resultado pi: %f\nTiempo %lf\n", pi, t);
	
	return 0;
}


