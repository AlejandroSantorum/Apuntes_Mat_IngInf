/*********************************************************/
/*Cálculo PI: Método de integración - Version OpenMP	 */
/*********************************************************/

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main( int argc, char *argv[] ) 
{
	int i, n=100000000, numProcs, numThreads;
	double h, pi, *sum = NULL,t = 0;
	struct timeval t1,t2;

	// Obtenemos el numero de cores del equipo
	numProcs = omp_get_num_procs();
	printf("Numero de cores del equipo: %d\n", numProcs);
	omp_set_num_threads( numProcs );
	
	// Solicitamos memoria para la suma de cada proceso
	sum = (double*) malloc (sizeof(double)*numProcs);

	gettimeofday(&t1,NULL);

	h = 1.0 / (double)n;

	#pragma omp parallel default(shared) private(numThreads)
	{
		double x, priv_sum;
		int i, tid;
	
		// Obtenemos el numero de procesos lanzados	
        numThreads = omp_get_num_threads();
	
		// Obtenemos nuestro identificador de thread
		tid = omp_get_thread_num();

		priv_sum = 0.0;
		for(i = tid + 1; i <= n; i+=numThreads) 
		{
			x = h * ((double) i-0.5);
			priv_sum += 4.0 / (1.0 + x*x);
		}
		sum[tid] = priv_sum;
	}
	pi = 0.0;
	for(i = 0; i < numProcs; i++)
		pi += sum[i];
	pi = h * pi;
	
	gettimeofday(&t2,NULL);

	t = (t2.tv_sec -t1.tv_sec) + (t2.tv_usec - t1.tv_usec)/(double)1000000;
	printf("Resultado pi: %f\nTiempo %lf\n", pi, t);

	// Liberamos memoria
	free(sum);
	return 0;
}
