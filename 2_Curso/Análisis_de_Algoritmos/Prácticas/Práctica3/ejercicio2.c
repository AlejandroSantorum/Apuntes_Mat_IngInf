/***********************************************************/
/* Programa: ejercicio2 Fecha: 13/12/2017                  */
/* Autores:  Alejandro Santorum & David Cabornero          */
/*                                                         */
/* Programa que escribe en un fichero                      */
/* los tiempos medios del algoritmo de                     */
/* busqueda                                                */
/*                                                         */
/* Entrada: Linea de comandos                              */
/* -num_min: numero minimo de elementos de la tabla        */
/* -num_max: numero minimo de elementos de la tabla        */
/* -incr: incremento                                       */
/* -fclaves: numero de claves a buscar                     */
/* -numP: Introduce el numero de permutaciones a promediar */
/* -fichSalida: Nombre del fichero de salida               */
/*                                                         */
/* Salida: 0 si hubo error                                 */
/*        -1 en caso contrario                             */
/***********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "permutaciones.h"
#include "busqueda.h"
#include "tiempos.h"

int main(int argc, char** argv)
{
  int i, num_min,num_max,incr,n_veces;
  char nombre[256];
  short ret;

  srand(time(NULL));

  if (argc != 11) {
    fprintf(stderr, "Error en los parametros de entrada:\n\n");
    fprintf(stderr, "%s -num_min <int> -num_max <int> -incr <int> -n_veces <int> -fichSalida <string>\n", argv[0]);
    fprintf(stderr, "Donde:\n");
    fprintf(stderr, "-num_min: numero minimo de elementos de la tabla\n");
    fprintf(stderr, "-num_max: numero minimo de elementos de la tabla\n");
    fprintf(stderr, "-incr: incremento\n");
    fprintf(stderr, "-n_veces: numero de veces que se busca cada clave\n");
    fprintf(stderr, "-fichSalida: Nombre del fichero de salida\n");
    exit(-1);
  }

  printf("Practica numero 3, apartado 2\n");
  printf("Realizada por: Alejandro Santorum y David Cabornero.\n");
  printf("Grupo: 1201.\n");
  printf("pareja 10.\n");

  /* comprueba la linea de comandos */
  for(i = 1; i < argc ; i++) {
    if (strcmp(argv[i], "-num_min") == 0) {
      num_min = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-num_max") == 0) {
      num_max = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-incr") == 0) {
      incr = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-n_veces") == 0) {
      n_veces = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-fichSalida") == 0) {
      strcpy(nombre, argv[++i]);
    } else {
      fprintf(stderr, "Parametro %s es incorrecto\n", argv[i]);
      exit(-1);
    }
  }

  /* calculamos los tiempos */
  ret = genera_tiempos_busqueda(blin_auto, generador_claves_potencial, NO_ORDENADO, nombre, num_min, num_max, incr, n_veces);
  if (ret == ERR) {
    printf("Error en la funcion genera_tiempos_busqueda\n");
    exit(-1);
  }

  printf("Salida correcta \n");

  return 0;
}
