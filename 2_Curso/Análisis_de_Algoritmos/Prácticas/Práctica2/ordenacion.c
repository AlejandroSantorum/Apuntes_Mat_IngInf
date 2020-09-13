#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "ordenacion.h"
#include "permutaciones.h"


/*-----------------------------MERGESORT----------------------*/
/*
Creadores: Alejandro Santorum y David Cabornero
Fecha: 25/09/2017
Pareja. 10
Función: mergesort
    Recive:
        -tabla: array de enteros
        -ip: índice del primer elemento de la tabla
        -iu: índice del último elemento de la tabla
    Devuelve:
        -int: número de comparaciones de clave o ERR en
            caso de error.
*/
int mergesort(int* tabla, int ip, int iu){
    int M, a=0, b=0, c=0;
    double aux;

    /*Comprobaciones de error*/
    if(tabla == NULL){
        printf("Error. Memoria de la tabla perdida.\n");
        return ERR;
    }

    if(ip > iu){
        printf("Error. Último menor que primero.\n");
        return ERR;
    }
    if(ip<0 || iu<0){
        printf("Error. ip o iu menor que cero.\n");
        return ERR;
    }
    /*--------------------------------*/

    /*Comprobación de parada de la recursión*/
    if(ip == iu){  
        return 0;
    }
    /*---------------------------------*/

    aux = (iu + ip)/2;
    M = floor(aux);

    a = mergesort(tabla, ip, M);
    b = mergesort(tabla, M+1, iu);

    c = merge(tabla, ip, iu, M);

    return (a+b+c);
}


/*Función auxiliar de mergesort*/
int merge(int *tabla, int ip, int iu, int M){
     int *tablaAux=NULL;
     int tam, i, j, k, ncdc=0;

     /*Comprobaciones*/
     if(tabla == NULL){
         printf("Error. Memoria de la tabla perdida II (merge).\n");
         return ERR;
     }
     if(iu<ip || ip > M || iu < M){
         printf("Error en los índices en la función de combinar.\n");
         return ERR;
     }
     /*-------------------------------------*/

     tam = (iu - ip)+1;

     tablaAux = (int *) malloc(tam * sizeof(int));
     if(tablaAux == NULL){
         printf("Error. Problemas de reserva de memoria tabla auxiliar.\n");
         return ERR;
     }

     i=ip;
     j=M+1;
     k=0;

     while(i<= M && j<=iu){
         if(tabla[i]<tabla[j]){
             tablaAux[k] = tabla[i];
             i++;
         }
         else{
             tablaAux[k]=tabla[j];
             j++;
         }
         k++;
         ncdc++;
     }

     if(i>M){
         while(j<=iu){
             tablaAux[k] = tabla[j];
             j++;
             k++;
         }
     }
     else if(j>iu){
         while(i<=M){
             tablaAux[k] = tabla[i];
             i++;
             k++;
         }
     }

     for(i=0, j=ip; j<=iu ;i++, j++){
         tabla[j] = tablaAux[i];
     }

     free(tablaAux);

     return ncdc;
}



/*----------------------------QUICKSORT----------------------------*/
/*
Creadores: Alejandro Santorum y David Cabornero
Fecha: 25/09/2017
Pareja. 10
Función: quicksort
    Recive:
        -tabla: array de enteros
        -ip: índice del primer elemento de la tabla
        -iu: índice del último elemento de la tabla
    Devuelve:
        -int: número de comparaciones de clave o ERR en
            caso de error.
*/
int quicksort(int *tabla, int ip, int iu){
    int a=0, b=0, c=0;
    int pos;

    /*Comprobaciones de error*/
    if(tabla == NULL){
        printf("Error. Memoria de la tabla perdida (qs).\n");
        return ERR;
    }
    if(ip > iu){
        printf("Error. Primero mayor que último (qs).\n");
        return ERR;
    }
    if(ip<0 || iu<0){
        printf("Error. ip o iu menor que cero.\n");
        return ERR;
    }
    /*--------------------------*/

    if(ip == iu){  /*Condición de parada de la recursión */
        return 0;
    }

    c = partir(tabla, ip, iu, &pos);

    if(ip < pos-1){
        a = quicksort(tabla, ip, pos-1);
        if(a == ERR){
            printf("Error en QS parte recursiva (a).\n");
            return ERR;
        }
    }
    if(pos+1 < iu){
        b = quicksort(tabla, pos+1, iu);
        if(b == ERR){
            printf("Error en QS parte recursiva (b).\n");
            return ERR;
        }
    }


    return (a+b+c);
}


/*Función auxiliar de quicksort*/
int partir(int *tabla, int ip, int iu,int *pos){
    int k, i, ncdc=0, aux, mid;

    /*Comprobaciones de error*/
    if(tabla == NULL){
        printf("Error. Memoria de la tabla perdida (partir) o de pos.\n");
        return ERR;
    }
    if(ip > iu){
        printf("Error. Primero mayor que último (partir).\n");
        return ERR;
    }
    if(ip<0 || iu<0){
        printf("Error. ip o iu menor que cero.\n");
        return ERR;
    }
    /*--------------------------*/

    /* IMPORTANTE: Se recomienda sustituir aqui debajo la función
    que calcula el pivote para poder comparar la eficacia del algoritmo
    dependiendo de la correcta elección del pivote.*/
    ncdc = medio(tabla, ip, iu, pos);
    if(ncdc == ERR){
      printf("Error en el retorno de la función medio.\n");
      return ERR;
    }
    mid = *pos;

    k = tabla[mid];

    aux = tabla[mid];
    tabla[mid] = tabla[ip];
    tabla[ip] = aux;

    mid = ip;

    for(i=ip+1; i<=iu; i++){
        ncdc++;
        if(tabla[i] < k){
            mid++;
            aux = tabla[i];
            tabla[i] = tabla[mid];
            tabla[mid] = aux;
        }
    }

    aux = tabla[ip];
    tabla[ip] = tabla[mid];
    tabla[mid] = aux;

    *pos = mid;

    return ncdc;
}

/* --------------Funciónes axuliares de partir--------------------------*/
int medio(int *tabla, int ip, int iu, int *pos){
    /*A pesar de que las mismas comprobaciones se han realizado en la función anterior,
    nos cercionamos de que el paso de argumentos entre funciones es correcto y no
    hay ninguna anomalía*/

    /*Comprobaciones de error*/
    if(tabla == NULL){
        printf("Error. Memoria de la tabla perdida (partir) o de pos.\n");
        return ERR;
    }
    if(ip > iu){
        printf("Error. Primero mayor que último (partir).\n");
        return ERR;
    }
    if(ip<0 || iu<0){
        printf("Error. ip o iu menor que cero.\n");
        return ERR;
    }
    /*--------------------------*/

    *pos = ip;

    return 0;
}


int medio_avg(int *tabla, int ip, int iu,int *pos){
    int avg;

    /*A pesar de que las mismas comprobaciones se han realizado en la función anterior,
    nos cercionamos de que el paso de argumentos entre funciones es correcto y no
    hay ninguna anomalía*/

    /*Comprobaciones de error*/
    if(tabla == NULL){
        printf("Error. Memoria de la tabla perdida (partir) o de pos.\n");
        return ERR;
    }
    if(ip > iu){
        printf("Error. Primero mayor que último (partir).\n");
        return ERR;
    }
    if(ip<0 || iu<0){
        printf("Error. ip o iu menor que cero.\n");
        return ERR;
    }
    /*--------------------------*/

    avg = floor((ip+iu)/2);
    *pos = avg;

    return 0;
}


int medio_stat(int *tabla, int ip, int iu,int *pos){
    int avg;

    /*A pesar de que las mismas comprobaciones se han realizado en la función anterior,
    nos cercionamos de que el paso de argumentos entre funciones es correcto y no
    hay ninguna anomalía*/

    /*Comprobaciones de error*/
    if(tabla == NULL){
        printf("Error. Memoria de la tabla perdida (partir) o de pos.\n");
        return ERR;
    }
    if(ip > iu){
        printf("Error. Primero mayor que último (partir).\n");
        return ERR;
    }
    if(ip<0 || iu<0){
        printf("Error. ip o iu menor que cero.\n");
        return ERR;
    }
    /*--------------------------*/

    avg = floor((ip+iu)/2);

    if(tabla[ip] < tabla[iu]){
        if(tabla[avg] < tabla[ip]){
            *pos = ip;
            return 2;
        }
        else if(tabla[avg] < tabla[iu]){
            *pos = avg;
            return 3;
        }
        else{
            *pos = iu;
            return 3;
        }
    }

    else{
        if(tabla[avg] < tabla[iu]){
            *pos = iu;
            return 2;
        }
        else if(tabla[avg] < tabla[ip]){
            *pos = avg;
            return 3;
        }
        else{
            *pos = ip;
            return 3;
        }
    }
}
