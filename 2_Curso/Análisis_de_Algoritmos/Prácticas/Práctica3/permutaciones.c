/**
 *
 * Descripcion: Implementacion de funciones de generacion de permutaciones
 *
 * Fichero: permutaciones.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2017
 *
 */


#include "permutaciones.h"

/***************************************************/
/* Funcion: aleat_num Fecha: 22/09/2017            */
/* Autores: David Cabornero Pascual                */
/*          Alejandro Santorum Varela              */
/* Rutina que genera un numero aleatorio           */
/* entre dos numeros dados                         */
/*                                                 */
/* Entrada:                                        */
/* int inf: limite inferior                        */
/* int sup: limite superior                        */
/* Salida:                                         */
/* int: numero aleatorio                           */
/***************************************************/
int aleat_num(int inf, int sup){
    int result = 0;
    
    if(inf == sup){
        return sup;
    }
    
    else if (inf > sup){
        printf("ERROR: Límite inferior mayor que el límite superior.\n");
        exit(-1);
    }

    result = (inf + ((int) ((((double)(sup-inf+1)) * rand())/(RAND_MAX + 1.0))));
    
    return result;
}

/***************************************************/
/* Funcion: genera_perm Fecha: 22/09/2017          */
/* Autores: David Cabornero Pascual                */
/*          Alejandro Santorum Varela              */
/* Rutina que genera una permutacion               */
/* aleatoria                                       */
/*                                                 */
/* Entrada:                                        */
/* int n: Numero de elementos de la                */
/* permutacion                                     */
/* Salida:                                         */
/* int *: puntero a un array de enteros            */
/* que contiene a la permutacion                   */
/* o NULL en caso de error                         */
/***************************************************/
int* genera_perm(int N){
    int i, aux1, aux2;
    int *perm;
    
    if(N<=0){
        printf("ERROR: Tamanio del array de la permutación menor o igual a cero.\n");
        return NULL;
    }
    else if(N>MAX_TAM){
        printf("MEDIDA DE SEGURIDAD: Tamanio del array de la permutación excesivo (superior a INT_MAX).\n");
        return NULL;
    }
    
    perm = (int  *) malloc(N * sizeof(int));
    if(perm == NULL){
        return NULL;
    }
    
    for(i=0; i<N; i++){
        perm[i] = i+1;
    }
    
    for(i=0; i<N; i++){
        aux1 = perm[i];
        aux2 = aleat_num(i, N-1);
        perm[i] = perm[aux2];
        perm[aux2] = aux1;
    }
    
    return perm;
}

/***************************************************/
/* Funcion: genera_permutaciones Fecha: 22/09/2017 */
/* Autores: David Cabornero Pascual                */
/*          Alejandro Santorum Varela              */
/*                                                 */
/* Funcion que genera n_perms permutaciones        */
/* aleatorias de tamanio elementos                 */
/*                                                 */
/* Entrada:                                        */
/* int n_perms: Numero de permutaciones            */
/* int N: Numero de elementos de cada              */
/* permutacion                                     */
/* Salida:                                         */
/* int**: Array de punteros a enteros              */
/* que apuntan a cada una de las                   */
/* permutaciones                                   */
/* NULL en caso de error                           */
/***************************************************/
int** genera_permutaciones(int n_perms, int N){
    int i,j;
    int **pp=NULL;
    
    if(N<=0 || n_perms<=0){
        printf("ERROR: El número de permutaciones y/o el tamanio de las mismas menor o igual que cero.\n");
        return NULL;
    }
    else if(N>MAX_TAM||n_perms>MAX_TAM){
        printf("MEDIDA DE SEGURIDAD: El número de permutaciones y/o el tamanio de las mismas es demasiado grande.\n");
    }
    
    pp = (int **) malloc(n_perms * sizeof(int*));
    if(pp == NULL){
        return NULL;
    }
    
    for(i=0; i<n_perms; i++){
        pp[i] = genera_perm(N);
        if(pp[i] == NULL){
            for(j=0; j<i; j++){
                free(pp[j]);
            }
            free(pp);
            return NULL;
        }
    }
    return pp;
}