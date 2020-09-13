/**
 *
 * Descripcion: Implementacion de funciones de tiempo
 *
 * Fichero: tiempos.c
 * Autor: Carlos Aguirre Maeso
 * Version: 1.0
 * Fecha: 16-09-2017
 *
 */

#include "tiempos.h"
#include "busqueda.h"
#include "permutaciones.h"
#include <limits.h>
#include <time.h>
#include <math.h>

#define TENTOTHENINE 1000000000
#define TENTOTHESIX 1000000
/**********************************************************/
/* Funcion: tiempo_medio_ordenación     Fecha: 20/10/2017 */
/* Autores: David Cabornero Pascual                       */
/*          Alejandro Santorum Varela                     */
/*                                                        */
/* Entrada:                                               */
/* int n_perms: Numero de permutaciones                   */
/* int N: Numero de elementos de cada                     */
/* ptiempo: puntero a estructura Tiempo                   */
/* permutacion                                            */
/* metodo: puntero a función de ordenación                */
/* Salida:                                                */
/* short: OK en caso de éxito, ERR en caso de ERROR       */
/**********************************************************/
short tiempo_medio_busqueda(pfunc_busqueda metodo, pfunc_generador_claves generador, int orden, int N, int n_veces, PTIEMPO ptiempo){
  DICC *dicc = NULL;
  int *perm=NULL, *tabla_claves=NULL;
  int pos, clave, check1, check2;
  long i, nob, max=0, min=INT_MAX, n_claves;
  double media = 0, actual, total=0;
  struct timespec start, end, aux;

  /*Comprobaciones de error----------------------------------------------------*/
  if(metodo == NULL){
    printf("Error. Puntero a función nulo (metodo).\n");
    return ERR;
  }
  if(generador == NULL){
    printf("Error. Puntero a función nulo (generador).\n");
    return ERR;
  }
  if(ptiempo == NULL){
    printf("Error. Puntero a la estructura tiempo nulo.\n");
    return ERR;
  }
  if(n_veces<=0){
    printf("Error. Número de veces que se busca cada una de las claves nulo o negativo.\n");
    return ERR;
  }
  if(N<=0){
    printf("Error. Tamaño de las permutaciones negativo o nulo.\n");
    return ERR;
  }
  if(orden != ORDENADO && orden != NO_ORDENADO){
    printf("Error. Orden no especificado.\n");
    return ERR;
  }

  /*El grueso del programa------------------------------------------------------*/
  n_claves = N*n_veces;
  ptiempo->N = N;
  ptiempo->n_elems = n_claves;

  dicc = ini_diccionario(N, orden);
  if(dicc == NULL){
    printf("Error al crear un diccionario\n");
    return ERR;
  }

  perm = genera_perm(N);
  if (perm == NULL) {
    /* error */
    printf("Error: No hay memoria en perm.\n");
    libera_diccionario(dicc);
    return ERR;
  }

  nob = insercion_masiva_diccionario(dicc, perm, N);
  if (nob == ERR) {
    /* error */
    printf("Error al llamar a insercion_masiva_diccionario\n");
    free(perm);
    libera_diccionario(dicc);
    return ERR;
  }

  tabla_claves = (int *) malloc(n_claves*sizeof(int));
  if(tabla_claves==NULL){
    /* error */
    printf("Error al llamar a insercion_masiva_diccionario\n");
    free(perm);
    libera_diccionario(dicc);
    return ERR;
  }

  generador(tabla_claves, n_claves, N);
  if(tabla_claves == NULL){
    printf("Error al generar claves\n");
    free(perm);
    libera_diccionario(dicc);
    return ERR;
  }

  for(i=0; i<n_claves; i++){
    clave = tabla_claves[i];
    check1 = clock_gettime(CLOCK_REALTIME, &start);
    actual = busca_diccionario(dicc, clave, &pos, metodo);
    check2 = clock_gettime(CLOCK_REALTIME, &end);

    if(check1 == -1){
      printf("Error en clock_gettime (start) en tiempo_medio_busqueda.\n");
      libera_diccionario(dicc);
      free(tabla_claves);
      free(perm);
      return ERR;
    }
    if(check2 == -1){
      printf("Error en clock_gettime (end) en tiempo_medio_busqueda.\n");
      libera_diccionario(dicc);
      free(tabla_claves);
      free(perm);
      return ERR;
    }
    if(actual == ERR){
      printf("Error en busca_diccionario en tiempo_medio_busqueda (ERR).\n");
      libera_diccionario(dicc);
      free(tabla_claves);
      free(perm);
      return ERR;
    }
    if(pos == NO_ENCONTRADO){
      printf("Error en busca_diccionario en tiempo_medio_busqueda (NO_ENCONTRADO).\n");
      libera_diccionario(dicc);
      free(tabla_claves);
      free(perm);
      return ERR;
    }

    aux.tv_sec = end.tv_sec - start.tv_sec; /* Calculamos los segundos */
    aux.tv_nsec = end.tv_nsec - start.tv_nsec; /* Calculamos los nanosegundos */
    total = total + aux.tv_sec*TENTOTHENINE + aux.tv_nsec; /* Guardamos el tiempo en nanosegundos */

    media = media + actual;
    if(actual > max){
      max = actual;
    }
    if(actual < min){
      min = actual;
    }
  }
  total = total/n_claves; /* Recordemos que n_claves = n_elems = N * n_veces */

  media = media/n_claves;

  ptiempo->medio_ob = media;
  ptiempo->max_ob = max;
  ptiempo->min_ob = min;
  ptiempo->tiempo = total/TENTOTHENINE; /*Guardamos el tiempo en la struct en segundos
                                      tal y como se indica en la documentación */

  free(tabla_claves);
  free(perm);
  libera_diccionario(dicc);

  return OK;
}





/**********************************************************/
/* Funcion: genera_tiempos_busqueda    Fecha: 20/10/2017*/
/* Autores: David Cabornero Pascual                       */
/*          Alejandro Santorum Varela                     */
/*                                                        */
/* Entrada:                                               */
/* int n_perms: Numero de permutaciones                   */
/* int num_min: tamaño mínimo permutación                 */
/* int num_max: tamaño máximo de permutación              */
/* permutacion                                            */
/* int incr: incremento del tamaño.                       */
/* metodo: puntero a función de ordenación                */
/* fichero: puntero a un fichero donde se imprimirán datos*/
/* Salida:                                                */
/* short: OK en caso de éxito, ERR en caso de ERROR       */
/**********************************************************/
short genera_tiempos_busqueda(pfunc_busqueda metodo, pfunc_generador_claves generador, int orden, char* fichero, int num_min, int num_max, int incr, int n_veces){
  TIEMPO *ptiempo;
  int array_size, i, j;
  double aux;

  /*Comprobaciones*/
  if(num_min<0 || num_max < num_min || incr <= 0){
    printf("Error. Meta unos números decentes por favor.\n");
    return ERR;
  }
  if(n_veces<=0){
    printf("Error. Número de permutaciones nulo o negativo.\n");
    return ERR;
  }
  if(orden != ORDENADO && orden != NO_ORDENADO){
    printf("Error. Orden no especificado.\n");
    return ERR;
  }
  if(fichero == NULL){
    printf("Error. Puntero a fichero nulo.\n");
    return ERR;
  }
  if(metodo == NULL){
    printf("Error. Puntero a función nulo (metodo).\n");
    return ERR;
  }
  if(generador == NULL){
    printf("Error. Puntero a función nulo (generador).\n");
    return ERR;
  }
  /*-------------------------------------------*/


  /*Grueso del programa*/
  aux = num_max - num_min;
  aux = aux/incr; /* ya nos hemos asegurado anteriormente que incr != 0 */
  array_size = ceil(aux);
  printf("array = %d\n", array_size);
  /*El anterior printf, intuitivamente, te dice el número
  de filas que se van a imprimir en el fichero de salida*/

  ptiempo = (TIEMPO *) malloc(array_size * sizeof(TIEMPO));
  if(ptiempo == NULL){
    printf("Error. Reserva de memoria en PTIEMPO.\n");
    return ERR;
  }

  for(i=num_min, j=0; j<array_size; i = i + incr, j++){
    if(tiempo_medio_busqueda(metodo, generador, orden, i, n_veces, &ptiempo[j]) == ERR){
      printf("Error en la función 2 haciendo la 1. del ej2.\n");
      return ERR;
    }
  }

  if(guarda_tabla_tiempos(fichero, ptiempo, array_size) == ERR){
    free(ptiempo);
    return ERR;
  }

  free(ptiempo);

  return OK;
}





/**********************************************************/
/* Funcion: guarda_tabla_tiempos         Fecha: 20/10/2017*/
/* Autores: David Cabornero Pascual                       */
/*          Alejandro Santorum Varela                     */
/*                                                        */
/* Entrada:                                               */
/* int n_tiempos: tamaño del array                        */
/* fichero: puntero a un fichero donde se imprimirán datos*/
/* ptiempo: array de punteros a estructura tiempo          */
/*                                                        */
/* Salida:                                                */
/* short: OK en caso de éxito, ERR en caso de ERROR       */
/**********************************************************/
short guarda_tabla_tiempos(char *fichero, TIEMPO *ptiempo, int n_tiempos){
  FILE *f=NULL;
  int i;

  /*Comprobaciones*/
  if(fichero == NULL){
    printf("Error. Puntero a fichero nulo.\n");
    return ERR;
  }
  if(ptiempo == NULL){
    printf("Error. Puntero a la estructura tiempo nulo.\n");
    return ERR;
  }
  if(n_tiempos <= 0){
    printf("Error. Tamaño del array tiempo negativo o nulo.\n");
    return ERR;
  }


  /*Grueso del programa*/
  f = (FILE *) fopen(fichero, "a");
  if(f == NULL){
    return ERR;
  }

  fprintf(f, "size   time(us)   avg_ob   max_ob   min_ob.\n");

  for(i=0; i<n_tiempos; i++){
    fprintf(f, "%d   %f   %.2f   %d   %d\n", ptiempo[i].N, ptiempo[i].tiempo * TENTOTHESIX, ptiempo[i].medio_ob, ptiempo[i].max_ob, ptiempo[i].min_ob);
  } /* Multiplicamos el tiempo por 10^6 para pasar de segundos a microsegundos. Así su interpretación es más sencilla en la gráfica */


  fclose(f);

  return OK;
}
