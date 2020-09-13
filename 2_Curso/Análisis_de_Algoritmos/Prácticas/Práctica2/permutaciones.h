/**
 *
 * Descripcion: Funciones de cabecera para generaciónde permutaciones
 *
 * Fichero: permutaciones.h
 * Autor: Carlos Aguirre 
 * Version: 1.0
 * Fecha: 16-09-2017
 *
 */

#ifndef PERMUTACIONES_H
#define PERMUTACIONES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

/* constantes */

#ifndef ERR
  #define ERR -1
  #define OK (!(ERR))
#endif

#define MAX_TAM INT_MAX /* Límite máximo de seguridad para los parámetros de entrada de las funciones siguientes */

int aleat_num(int inf, int sup);
int* genera_perm(int N);
int** genera_permutaciones(int n_perms, int N);

#endif