#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <limits.h>
#include <time.h>
#include <math.h>

#define LEN 50

typedef struct{
  int id;
  int **matrix;
  int dim;
  int scalar;
  char *pos1;
  char *pos2;
} Argum;


/**
* Función que calcula el producto de una matriz por un escalar
* ENTRADA: puntero a void que contendrá una estructura con argumentos,
*          entre ellos el hilo id, la matrix, el escalar, la dimension,
*          y dos cadenas de caracteres que compartiran los hilos
* SALIDA: void.
*/
void* mult_matrix(void *arg);


int main(int argc, char const *argv[]) {
  int **m1=NULL;
  int **m2=NULL;
  int s1;
  int s2;
  int i, j, dim;
  char comunic1[LEN];
  char comunic2[LEN];
  Argum *arg1=NULL;
  Argum *arg2=NULL;
  pthread_t h1, h2;

  printf("Introduzca dimension de la matriz cuadrada:\n");
  scanf("%d", &dim);

  printf("Introduzca multiplicador 1:\n");
  scanf("%d", &s1);
  printf("Introduzca multiplicador 2:\n");
  scanf("%d", &s2);

/* ------- Reservando memoria matriz 1 ---------- */
  m1 = (int **) malloc(dim * sizeof(int *));
  if(!m1){
    printf("Error de memoria matriz 1.\n");
    exit(EXIT_FAILURE);
  }
  for(i=0; i<dim; i++){
    m1[i] = (int *) malloc(dim * sizeof(int));
    if(!m1[i]){
      printf("Error de memoria m1-%d", i);
      for(j=0; j<i; j++){
        free(m1[j]);
      }
      free(m1);
      exit(EXIT_FAILURE);
    }
  }

  printf("MATRIZ 1\n");
  for(i=0; i<dim; i++){
    for(j=0; j<dim; j++){
      printf("Introduzca elemento %d-%d: ", i+1,j+1);
      scanf("%d", &(m1[i][j]));
    }
  }

/* ------- Reservando memoria matriz 2 ---------- */
  m2 = (int **) malloc(dim * sizeof(int *));
  if(!m2){
    printf("Error de memoria matriz 2.\n");
    exit(EXIT_FAILURE);
  }
  for(i=0; i<dim; i++){
    m2[i] = (int *) malloc(dim * sizeof(int));
    if(!m2[i]){
      printf("Error de memoria m2-%d", i);
      for(j=0; j<i; j++){
        free(m2[j]);
      }
      free(m2);
      exit(EXIT_FAILURE);
    }
  }

  printf("MATRIZ 2\n");
  for(i=0; i<dim; i++){
    for(j=0; j<dim; j++){
      printf("Introduzca elemento %d-%d: ", i+1,j+1);
      scanf("%d", &(m2[i][j]));
    }
  }

  /* Memoria para las estructuras de argumentos de los hilos */
  arg1 = (Argum *) malloc(sizeof(Argum));
  if(!arg1){
    printf("Error de memoria estructura de comunicacion.\n");
    exit(EXIT_FAILURE);
  }
  arg2 = (Argum *) malloc(sizeof(Argum));
  if(!arg2){
    printf("Error de memoria estructura de comunicacion.\n");
    exit(EXIT_FAILURE);
  }

  strcpy(comunic1, " - el hilo 1 todavia no ha comenzado.\n");
  strcpy(comunic2, " - el hilo 2 todavia no ha comenzado.\n");

  printf("Realizando producto:\n");

  arg1->id=1;
  arg1->matrix = m1;
  arg1->dim = dim;
  arg1->scalar = s1;
  arg1->pos1 = comunic1;
  arg1->pos2 = comunic2;

  pthread_create(&h1, NULL, mult_matrix, (void *)arg1);

  arg2->id=2;
  arg2->matrix = m2;
  arg2->dim = dim;
  arg2->scalar = s2;
  arg2->pos1 = comunic1;
  arg2->pos2 = comunic2;

  pthread_create(&h2, NULL, mult_matrix, (void *)arg2);

  pthread_join(h1, NULL);
  pthread_join(h2, NULL);

  for(i=0; i<dim; i++){
    free(m1[i]);
    free(m2[i]);
  }
  free(m1);
  free(m2);
  free(arg1);
  free(arg2);

  return EXIT_SUCCESS;
}



void* mult_matrix(void *arg){
  Argum *com;
  int fila, col, res;
  char str[LEN], num[LEN/5], fin[LEN];

  if(!arg){
    printf("Error de memoria. Estructura de argumentos de entrada a NULL.\n");
    return NULL;
  }

  com = (Argum *) arg;

  for(fila=0; fila<com->dim; fila++){
    /* El id impar escribe en com->pos1 y lee de com->pos2 */
    if((com->id % 2)){
      sprintf(com->pos1, " - el hilo %d va por la fila %d\n", com->id, fila);
      strcpy(fin, com->pos2);
    }
    /* El id par escribe en com->pos2 y lee de com->pos1 */
    if(!(com->id % 2)){
      sprintf(com->pos2, " - el hilo %d va por la fila %d\n", com->id, fila);
      strcpy(fin, com->pos1);
    }

    sprintf(str, "Hilo %d multiplicando fila %d resultado", com->id, fila);
    for(col=0; col<com->dim; col++){
      res = com->scalar * com->matrix[fila][col];
      sprintf(num, " %d", res);
      strcat(str, num);
    }
    strcat(str, fin); /* añadimos la informacion del otro hilo */
    printf("%s", str);
    fflush(stdout); /* vaciamos la pila para que se realicen los printf() */
    sleep(1);
  }
  return NULL;
}
