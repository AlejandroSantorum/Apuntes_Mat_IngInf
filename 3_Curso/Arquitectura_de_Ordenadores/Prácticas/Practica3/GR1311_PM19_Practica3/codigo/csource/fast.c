#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "arqo3.h"

tipo compute(tipo **matrix,int n);

int main( int argc, char *argv[]){
	int n;
	tipo **m=NULL;
	struct timeval fin,ini;
	tipo res=0;

	printf("Word size: %ld bits\n",8*sizeof(tipo));

	if( argc!=2 ){
		printf("Error: ./%s <matrix size>\n", argv[0]);
		return -1;
	}
	n=atoi(argv[1]);
	m=generateMatrix(n);
	if( !m ){
		return -1;
	}

	gettimeofday(&ini,NULL);
	/* Main computation */
	res = compute(m,n);
	/* End of computation */
	gettimeofday(&fin,NULL);

	printf("Execution time: %f\n", ((fin.tv_sec*1000000+fin.tv_usec)-(ini.tv_sec*1000000+ini.tv_usec))*1.0/1000000.0);
	printf("Total: %lf\n",res);
	
	freeMatrix(m);
	return 0;
}


tipo compute(tipo **matrix,int n){
	tipo sum=0;
	int i,j;
	
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			sum += matrix[i][j];
		}
	}
	return sum;
}
