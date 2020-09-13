/**************************************************/
/* Programa: ejercicio3       Fecha: 22/09/2017   */
/* Autores: David Cabornero Pascual               */
/*          Alejandro Santorum Varela             */
/*                                                */
/* Programa que genera permutaciones N            */
/* aleatorias de M elementos                      */
/*                                                */
/* Entrada: Linea de comandos                     */
/* -tamanio: numero elementos permutacion         */
/* -numP: numero de permutaciones                 */
/* Salida: 0: OK, -1: ERR                         */
/**************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "permutaciones.h"

int main(int argc, char** argv)
{
  int i;
  unsigned int n_perms, tamanio, j, k;
  int** perms = NULL;

  srand(time(NULL));

  if (argc != 5) {
    fprintf(stderr, "Error en los parametros de entrada:\n\n");
    fprintf(stderr, "%s -tamanio <int> -numP <int>\n", argv[0]);
    fprintf(stderr, "Donde:\n");
    fprintf(stderr, " -tamanio : numero elementos permutacion.\n");
    fprintf(stderr, " -numP : numero de permutaciones.\n");
    exit(-1);
  }

  printf("Practica numero 1, apartado 3\n");
  printf("Realizada por: Alejandro Santorum & David Cabornero\nPareja 10.\n");
  printf("Grupo: 1201\n");

  /* comprueba la linea de comandos */
  for(i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-tamanio") == 0) {
      tamanio = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-numP") == 0) {
      n_perms = atoi(argv[++i]);
    } else {
      fprintf(stderr, "Parametro %s es incorrecto\n", argv[i]);
    }
  }

  perms = genera_permutaciones(n_perms, tamanio);

  if (perms == NULL) { /* error */
    printf("Error: No hay memoria\n");
    exit(-1);
  } else {
    for(j = 0; j < n_perms; j++) { /* para cada permutacion */
      for(k = 0; k < tamanio; k++) {
        printf("%d ", perms[j][k]); /* imprimimos cada elemento */
      }
      printf("\n");
      free(perms[j]); /* liberamos la permutacion */
    }

    free(perms); /* liberamos el array de permutaciones */
  }

  return 0;
}
