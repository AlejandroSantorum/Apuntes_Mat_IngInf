/**************************************************/
/* Programa: ejercicio4       Fecha: 22/09/2017   */
/* Autores: David Cabornero Pascual               */
/*          Alejandro Santorum Varela             */
/*                                                */
/* Programa que Comprueba Mergesort y/o           */
/* Quicksort                                      */
/* Entrada: Linea de comandos                     */
/* -tamanio: numero elementos permutacion         */
/* Salida: 0: OK, -1: ERR                         */
/**************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "permutaciones.h"
#include "ordenacion.h"

int main(int argc, char** argv)
{
  int tamano, i, j, k, ret;
  int* perm = NULL;

  srand(time(NULL));

  if (argc != 3) {
    fprintf(stderr, "Error en los parametros de entrada:\n\n");
    fprintf(stderr, "%s -tamanio <int>\n", argv[0]);
    fprintf(stderr, "Donde:\n");
    fprintf(stderr, " -tamanio : numero elementos permutacion.\n");
    return 0;
  }
  printf("Practica numero 2, apartado 1\n");
  printf("Realizada por: Alejandro Santorum & David Cabornero\n");
  printf("Grupo: 1201\n");

  /* comprueba la linea de comandos */
  for(i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-tamanio") == 0) {
      tamano = atoi(argv[++i]);
    } else {
      fprintf(stderr, "Parametro %s es incorrecto\n", argv[i]);
    }
  }

  perm = genera_perm(tamano);

  if (perm == NULL) { /* error */
    printf("Error: No hay memoria\n");
    exit(-1);
  }

  ret = mergesort(perm, 0, tamano-1); /*Sustituir "quicksort por "mergesort"
                                    dependiendo del algoritmo que desee usar*/

  if (ret == ERR) {
    printf("Error: Error en mergesort\n");
    free(perm);
    exit(-1);
  }

  for(j = 0, k=0; j < tamano; j++, k++) {
    printf("%d \t", perm[j]);
    if(k==12){/*Para una salida por pantalla más clara*/
      printf("\n");
      k=-1;
    }
  }
  printf("\n");

  free(perm);

  return 0;
}
