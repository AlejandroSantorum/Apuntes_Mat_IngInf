#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "arqo3.h"

tipo** generateMatrix(int size);
void freeMatrix(tipo **matrix);
void printMatrix(tipo **matrix, int size);

tipo** generateMatrix(int size){
	tipo *array=NULL;
	tipo **matrix=NULL;
	int i=0,j=0;

	matrix=(tipo **)malloc(sizeof(tipo *)*size);
	array=(tipo *)malloc(sizeof(tipo)*size*size);
	if( !array || !matrix){
		printf("Error when allocating matrix of size %d.\n",size);
		if( array )
			free(array);
		if( matrix )
			free(matrix);
		return NULL;
	}

	srand(0);
	for(i=0;i<size;i++){
		matrix[i] = &array[i*size];
		for(j=0;j<size;j++){
			matrix[i][j] = (1.0*rand()) / (RAND_MAX/10);
		}
	}
	return matrix;
}

tipo** generateEmptyMatrix(int size){
	tipo *array=NULL;
	tipo **matrix=NULL;
	int i=0;

	matrix=(tipo **)malloc(sizeof(tipo *)*size);
	array=(tipo *)malloc(sizeof(tipo)*size*size);
	if( !array || !matrix){
		printf("Error when allocating matrix of size %d.\n",size);
		if( array )
			free(array);
		if( matrix )
			free(matrix);
		return NULL;
	}

	for(i=0;i<size;i++){
		matrix[i] = &array[i*size];
	}
	return matrix;
}


void freeMatrix(tipo **matrix){
	if( matrix && matrix[0] )
		free(matrix[0]);
	if( matrix )
		free(matrix);
	return;
}


void printMatrix(tipo **matrix, int size){
	int i,j;
	printf("---------------------\n");
	for(i=0; i<size; i++){
		for(j=0; j<size; j++){
			printf("%lf ", matrix[i][j]);
		}
		printf("\n");
	}
	printf(".....................\n");
}
