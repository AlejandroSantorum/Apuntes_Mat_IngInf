/*********************************************************/
/* Cálculo PI: Método de integración - Version OpenMP	 */
/* Work sharing + Clausula reduction 			 */
/*********************************************************/

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main( int argc, char *argv[] ) 
{
	int i, n = 100000000;
	double h, pi, sum = 0.0, x, t = 0;
	struct timeval t1,t2;

	gettimeofday(&t1,NULL);

	h = 1.0 / (double)n;

	#pragma omp parallel for reduction(+: sum) private(i,x) default(shared)
	for(i=1; i<=n; i++) 
	{
		x = h * ((double)i - 0.5);
		sum += 4.0 / (1.0 + x*x);
	}
	pi = h * sum;

	gettimeofday(&t2,NULL);

	t = (t2.tv_sec -t1.tv_sec) + (t2.tv_usec - t1.tv_usec)/(double)1000000;
	printf("Resultado pi: %f\nTiempo %lf\n", pi, t);
	
	return 0;
}
