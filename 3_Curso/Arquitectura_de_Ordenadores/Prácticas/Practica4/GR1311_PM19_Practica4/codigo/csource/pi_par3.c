/*********************************************************/
/* Cálculo PI: Método de integración - Version OpenMP	 */
/* false sharing 					 */
/*********************************************************/

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>

int main( int argc, char *argv[] ) 
{
	int i, n = 100000000, numProcs, numThreads;
	int datasz, linesz, padsz;
	double h, pi, *sum = NULL,t = 0;
	struct timeval t1,t2;
	FILE *f;
	char buf[512];

	// Obtenemos el numero de cores del equipo
	numProcs = omp_get_num_procs();
	printf("Numero de cores del equipo: %d\n", numProcs);
	omp_set_num_threads( numProcs );

	datasz = sizeof(double);
	printf("Double size: %d bytes\n", datasz);
	f = popen("getconf -a | grep CACHE | grep \"3_CACHE_LINESIZE\" | awk '{print $2}'", "r");
	fgets(buf, sizeof(buf), f);
	pclose(f);
	linesz = atoi(buf);
	padsz = linesz / datasz;
	printf("Cache line size: %d bytes => padding: %d elementos\n", linesz, padsz);
	
	// Solicitamos memoria para la suma de cada proceso
	sum = (double*) malloc (sizeof(double)*numProcs*padsz);	

	gettimeofday(&t1,NULL);

	h = 1.0 / (double)n;
	#pragma omp parallel default(shared) private(numThreads)
	{
		double x;
		int i, tid;
	
		// Obtenemos el numero de procesos lanzados	
        numThreads = omp_get_num_threads();
	
		// Obtenemos nuestro identificador de thread
		tid = omp_get_thread_num();
	
		sum[tid*padsz] = 0.0;
		for(i = tid + 1; i <= n; i += numThreads) 
		{
			x = h * ((double) i - 0.5);
			sum[tid*padsz] += 4.0 / (1.0 + x*x);
		}
	}
	
	pi = 0.0;
	for(i = 0; i < numProcs; i++)
		pi += sum[i*padsz];
	pi = h * pi;
	
	gettimeofday(&t2,NULL);
	
	t = (t2.tv_sec - t1.tv_sec) + (t2.tv_usec - t1.tv_usec)/(double)1000000;
	printf("Resultado pi: %f\nTiempo %lf\n", pi, t);

	// Liberamos memoria
	free(sum);

	return 0;
}
