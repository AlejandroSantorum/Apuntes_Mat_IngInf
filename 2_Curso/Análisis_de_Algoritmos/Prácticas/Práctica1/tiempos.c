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
#include "ordenacion.h"
#include "permutaciones.h"
#include <limits.h>
#include <time.h>
#include <math.h>


/**********************************************************/
/* Funcion: tiempo_medio_ordenación     Fecha: 30/09/2017 */
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
short tiempo_medio_ordenacion(pfunc_ordena metodo, int n_perms, int N, TIEMPO *ptiempo){
  int **perms;
  int i, max=0, min=INT_MAX;
  double media = 0, actual, total=0;
  clock_t start, end;
  
  /*Comprobaciones de error----------------------------------------------------*/
  if(metodo == NULL){
    printf("Error. Puntero a función nulo.\n");
    return ERR;
  }
  if(ptiempo == NULL){
    printf("Error. Puntero a la estructura tiempo nulo.\n");
    return ERR;
  }
  if(n_perms<=0){
    printf("Error. Número de permutaciones nulo o negativo.\n");
    return ERR;
  }
  if(N<=0){
    printf("Error. Tamaño de las permutaciones negativo o nulo.\n");
    return ERR;
  }
  
  /*El grueso del programa------------------------------------------------------*/
  ptiempo->N = N;
  ptiempo->n_elems = n_perms;
  
  perms = genera_permutaciones(n_perms, N);
  if(perms == NULL){
    printf("Error en la función tiempo_medio_ordenacion.\n");
    return ERR;
  }
  
  for(i=0; i<n_perms; i++){
    start = clock();
    actual = metodo(perms[i], 0, N-1);
    end = clock();
    
    total = total + (end - start);
    media = media + actual;
    
    if(actual > max){
      max = actual;
    }
    if(actual < min){
      min = actual;
    }
  }
  
  total = (total/(double)CLOCKS_PER_SEC)/n_perms;
  total = total*1000; /* Pasamos el tiempo a milisegundos */
  
  media = media/n_perms;
  
  ptiempo->medio_ob = media;
  ptiempo->max_ob = max;
  ptiempo->min_ob = min;
  ptiempo->tiempo = total;
  
  for(i=0; i<n_perms; i++){
    free(perms[i]);
  }
  free(perms);
  
  return OK;
}





/**********************************************************/
/* Funcion: genera_tiempos_ordenacion    Fecha: 30/09/2017*/
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
short genera_tiempos_ordenacion(pfunc_ordena metodo, char *fichero, int num_min, int num_max, int incr, int n_perms){
  TIEMPO *ptiempo;
  int array_size, i, j;
  double aux;
  
  /*Comprobaciones*/
  if(num_min<0 || num_max < num_min || incr <= 0){
    printf("Error. Mete unos números decentes por favor.\n");
    return ERR;
  }
  if(n_perms<=0){
    printf("Error. Número de permutaciones nulo o negativo.\n");
    return ERR;
  }
  if(fichero == NULL){
    printf("Error. Puntero a fichero nulo.\n");
    return ERR;
  }
  if(metodo == NULL){
    printf("Error. Puntero a función nulo.\n");
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
    if(tiempo_medio_ordenacion(metodo, n_perms, i, &ptiempo[j]) == ERR){
      printf("Error en la función 2 haciendo la 1. del ej5.\n");
      return ERR;
    }
  }
  
  
  if(guarda_tabla_tiempos(fichero, ptiempo, array_size) == ERR){
    return ERR;
  }    
  
  
  free(ptiempo);
  
  return OK;
}





/**********************************************************/
/* Funcion: guarda_tabla_tiempos         Fecha: 30/09/2017*/
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
  
  fprintf(f, "size  time(ms)  avg_ob  max_ob  min_ob.\n");
  
  for(i=0; i<n_tiempos; i++){
    fprintf(f, "%d   %f   %.2f   %d   %d\n", ptiempo[i].N, ptiempo[i].tiempo, ptiempo[i].medio_ob, ptiempo[i].max_ob, ptiempo[i].min_ob);
  }
  
  
  fclose(f);
  
  return OK;
}
