/**
 *
 * Descripcion: Funciones de cabecera para ordenacion
 *
 * Fichero: ordenacion.h
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2016
 *
 */

#ifndef ORDENACION_H
#define ORDENACION_H

#include <stdio.h>
#include <stdlib.h>
/* constantes */

#ifndef ERR
  #define ERR -1
  #define OK (!(ERR))
#endif


/* definiciones de tipos */
typedef int (* pfunc_ordena)(int*, int, int);

/* Funciones */

int mergesort(int* tabla, int ip, int iu);

int merge(int* tabla, int ip, int iu, int imedio);

int quicksort(int* tabla, int ip, int iu);

int partir(int* tabla, int ip, int iu,int *pos);

int medio(int *tabla, int ip, int iu,int *pos);

int medio_avg(int *tabla, int ip, int iu,int *pos);

int medio_stat(int *tabla, int ip, int iu,int *pos);

#endif
