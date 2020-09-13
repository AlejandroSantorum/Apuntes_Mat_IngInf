/**
 *
 * Descripcion: Implementacion de funciones de ordenacion 
 *
 * Fichero: ordenacion.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2017
 *
 */


#include "ordenacion.h"

/***************************************************/
/* Funcion: InsertSort    Fecha: 22/09/2017        */
/*                                                 */
/*Descripción: Rutina que ordena los elementos     */
/* de una tabla                                    */
/*                                                 */
/* Entrada:                                        */
/* tabla: array de enteros a ordenar               */
/* iu: límite superior                             */
/* ip: límite inferior                             */
/*                                                 */
/* Salida:                                         */
/* int: OK si ha sido un éxito la rutina           */
/*  o ERR si ha habido algún fallo/problema        */
/***************************************************/
int BubbleSort(int *tabla, int ip, int iu){
    int i, j,aux, cont=0;
    
    if(tabla == NULL){ /* Error */
        return ERR;
    }
    
    if(ip == iu){
        return cont;
    }
    
    if(ip > iu){
        printf("ERROR: índice primero superior a índice último en la tabla a ordenar. Compruebe los parámetros de entrada.\n");
        return ERR;
    }
    
    for(i=iu; (i>(ip+1)); i--){
        for(j=ip; j<i; j++){
            cont++;
            if(tabla[j]>tabla[j+1]){        /* Si el elemento siguiente es menor que el actual, realizamos un "swap" */
                aux = tabla[j];
                tabla[j] = tabla[j+1];
                tabla[j+1] = aux;
            }
        }
    }
    return cont;
}



int BubbleSort_flag(int *tabla, int ip, int iu){
    int i, j,aux, flag=1, cont=0;
    
    if(tabla == NULL){ /* Error */
        return ERR;
    }
    
    if(ip == iu){
        return cont;
    }
    
    if(ip > iu){
        printf("ERROR: índice primero superior a índice último en la tabla a ordenar. Compruebe los parámetros de entrada.\n");
        return ERR;
    }
    
    
    for(i=iu; (flag == 1) && (i>(ip+1)); i--){
        flag = 0;
        for(j=ip; j<i; j++){
            cont++;
            if(tabla[j]>tabla[j+1]){        /* Si el elemento siguiente es menor que el actual, realizamos un "swap" */
                aux = tabla[j];
                tabla[j] = tabla[j+1];
                tabla[j+1] = aux;
                flag = 1;
            }
        }
    }
    
    return cont;
}





