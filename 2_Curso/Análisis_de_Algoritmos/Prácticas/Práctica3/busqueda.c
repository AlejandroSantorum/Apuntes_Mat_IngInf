/**
 *
 * Descripcion: Implementacion funciones para busqueda
 *
 * Fichero: busqueda.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 11-11-2016
 *
 */

#include "busqueda.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

/**
 *  Funciones de geracion de claves
 *
 *  Descripcion: Recibe el numero de claves que hay que generar
 *               en el parametro n_claves. Las claves generadas
 *               iran de 1 a max. Las claves se devuelven en
 *               el parametro claves que se debe reservar externamente
 *               a la funcion.
 */

/**
 *  Funcion: generador_claves_uniforme
 *               Esta fucnion genera todas las claves de 1 a max de forma
 *               secuencial. Si n_claves==max entonces se generan cada clave
 *               una unica vez.
 */
void generador_claves_uniforme(int *claves, int n_claves, int max){
  int i;

  for(i = 0; i < n_claves; i++) claves[i] = 1 + (i % max);

  return;
}

/**
 *  Funcion: generador_claves_potencial
 *               Esta funcion genera siguiendo una distribucion aproximadamente
 *               potencial. Siendo los valores mas pequenos mucho mas probables
 *               que los mas grandes. El valor 1 tiene una probabilidad del 50%,
 *               el dos del 17%, el tres el 9%, etc.
 */
void generador_claves_potencial(int *claves, int n_claves, int max){
  int i;

  for(i = 0; i < n_claves; i++) {
    do{
      claves[i] = (1+max) / (1 + max*((double)rand()/RAND_MAX));
    }while(claves[i]==(1+max)); /*Se hace este cambio porque hay una posibilidad
                                entre RAND_MAX que rand()=0 y por lo tanto
                                claves[i] = max+1 lo cual no es lo que se quiere*/
  }

  return;
}

/*-------------------NUESTRAS FUNCIONES----------------------*/


PDICC ini_diccionario (int tamanio, int orden){
	DICC *dic = NULL;

	/* Comprobaciones de error */
	if(tamanio < 0){
	    fprintf(stdout, "Error. Tamaño del diccionario menor que cero.\n");
	    return NULL;
	}

	if(tamanio == 0){
	    fprintf(stdout, "Aviso. Tamaño del diccionario igual a cero.\n");
	    return NULL;
	}

	if(orden != ORDENADO && orden != NO_ORDENADO){
	    fprintf(stdout, "Error. Argumento orden incorrecto\n");
	    return NULL;
	}
	/*-------------------------------------------------------*/
	dic = (DICC *) malloc(sizeof(DICC));
	if(dic == NULL){
	    fprintf(stdout, "Error en la reserva de memoria de ini_diccionario.\n");
	    return NULL;
	}

	dic->tabla = (int*) malloc (tamanio*sizeof(int));
	if(dic->tabla == NULL){
	    fprintf(stdout, "Error en la reserva de memoria de la tabla de ini_diccionario.\n");
	    return NULL;
	}

	dic->tamanio = tamanio;
	dic->orden = orden;
	dic->n_datos = 0;

	return dic;
}



void libera_diccionario(PDICC pdicc){
	if(pdicc == NULL){
	    fprintf(stdout, "Error. Se está intentando liberar un diccionario a NULL.\n");
	    return;
	}

	if(pdicc->tabla != NULL){
		free(pdicc->tabla);
	}

	free(pdicc);
}



int inserta_diccionario(PDICC pdicc, int clave){
    int aux, j, ncdc=0;

	/* Comprobaciones de error */
	/* Suponemos que la clave que se aporta cabe en el tamaño de una variable de tipo int*/
	if(pdicc == NULL){
	    fprintf(stdout,"Error. pdicc en inserta_diccionario recibido como NULL.\n");
	    return ERR;
	}
	if(pdicc->tamanio == pdicc->n_datos){
		fprintf(stdout,"Error. pdicc en inserta_diccionario está lleno.\n");
	    return ERR;
	}
	/*---------------------------------------------*/

	if(pdicc->orden == NO_ORDENADO){
	    pdicc->tabla[pdicc->n_datos] = clave;
	    pdicc->n_datos++;
	    return 0;
	}

	else if(pdicc->orden == ORDENADO){
	    pdicc->tabla[pdicc->n_datos] = clave;


	    aux = pdicc->tabla[pdicc->n_datos];
	    j = pdicc->n_datos - 1;
	    while(j >= 0 && pdicc->tabla[j] > aux){
	        pdicc->tabla[j+1] = pdicc->tabla[j];
	        j--;
	        ncdc++;
	    }
	    pdicc->tabla[j+1] = aux;
	    ncdc++;
	    pdicc->n_datos++;
	}

	return ncdc;
}



int insercion_masiva_diccionario (PDICC pdicc, int *claves, int n_claves){
	int i, ncdc=0, aux=0;

	/* Comprobaciones */
	if(pdicc == NULL){
	    fprintf(stdout,"Error. pdicc en inserta_masiva_diccionario recibido como NULL.\n");
	    return ERR;
	}

	if(claves == NULL){
	    fprintf(stdout,"Error. claves en insercion_masiva_diccionario recibido como NULL.\n");
	    return ERR;
	}

	if(n_claves <= 0){
	    fprintf(stdout,"Error. n_claves en insercion_masiva_diccionario negativo o nulo.\n");
	    return ERR;
	}

	if(n_claves == 0){
	    return 0;
	}
	/*-----------------------------------------------------------------------*/

	for(i=0;i<n_claves;i++){
		aux = inserta_diccionario(pdicc, claves[i]);
		if(aux == ERR){
			fprintf(stdout,"Error. retorno de inserta_diccionario en insercion_masiva erróneo.\n");
	    	return ERR;
		}
	    ncdc += aux;
	}

	return ncdc;
}

int busca_diccionario(PDICC pdicc, int clave, int *ppos, pfunc_busqueda metodo){
    int ncdc=0;
    /* Comprobaciones de error */
	if(pdicc == NULL){
	    fprintf(stdout,"Error. pdicc en busca_diccionario recibido como NULL.\n");
	    return ERR;
	}
	/* OBSERVACIÓN: No se necesita una comprobación para ppos ya que este
	   puede que sea igual a NULL, dependiendo de como se pase en el programa principal.*/
	if(metodo == NULL){
	    fprintf(stdout,"Error. metodo en busca_diccionario recibido como NULL.\n");
	    return ERR;
	}
	/* ---------------------------------------------------------- */

	ncdc = metodo(pdicc->tabla, 0, pdicc->n_datos-1, clave, ppos);
	if(ncdc == ERR || ncdc < 0){ /* ERROR */
		fprintf(stdout, "Error en la función de búsqueda en busca_diccionario.\n");
		return ERR;
	}
	if(ppos == NULL){ /* ERROR */
	    fprintf(stdout, "ppos es igual a NULL despues de una función de búsqueda, lo cual es imposible.\n");
	    return ERR;
	}

	return ncdc;
}


/* Funciones de busqueda del TAD Diccionario */
int bbin(int *tabla,int P,int U,int clave,int *ppos){
    int m, ncdc=0;

	/* Comprobaciones de error*/
	if(tabla == NULL){
	    fprintf(stdout,"Error. tabla en bbin recibida como NULL.\n");
	    return ERR;
	}
	if(P > U){
	    fprintf(stdout,"Error. primero mayor que último en bbin.\n");
	    return ERR;
	}
	/*--------------------------------------------------*/
	while(P <= U){
	    m = (P+U)/2;

	    ncdc++;
	    if(tabla[m] == clave){
	        *ppos = m;
	        return ncdc;
	    }
	    else if(clave < tabla[m]){
	        U = m-1;
	    }

	    else{
	        P = m+1;
	    }
	}

	*ppos = NO_ENCONTRADO;

	return ncdc;
}



int blin(int *tabla,int P,int U,int clave,int *ppos){
	int ncdc=0, i;

	/* Comprobaciones de error*/
	if(tabla == NULL){
	    fprintf(stdout,"Error. tabla en bbin recibida como NULL.\n");
	    return ERR;
	}
	if(P > U){
	    fprintf(stdout,"Error. primero mayor que último en bbin.\n");
	    return ERR;
	}
    /*--------------------------------------------------*/
	for(i=P; i<=U; i++){
	    ncdc++;
	    if(tabla[i] == clave){
	        *ppos = i;
	        return ncdc;
	    }
	}
	*ppos = NO_ENCONTRADO;

	return ncdc;
}



int blin_auto(int *tabla,int P,int U,int clave,int *ppos){
    int ncdc=0, i, aux;
	/*Podríamos haber utilizado el algoritmo anterior blin en este código, pero nos parece
	más claro en lo que respecta a comprobaciones volver a representar todo el algoritmo aquí*/

    /* Comprobaciones de error*/
	if(tabla == NULL){
	    fprintf(stdout,"Error. tabla en bbin recibida como NULL.\n");
	    return ERR;
	}
	if(P > U){
	    fprintf(stdout,"Error. primero mayor que último en bbin.\n");
	    return ERR;
	}
    /*--------------------------------------------------*/

    for(i=P; i<=U; i++){
	    ncdc++;
	    if(tabla[i] == clave){
	    	*ppos = i;
	        if(i != P){
	        	aux = tabla[i]; /*Swap*/
	        	tabla[i] = tabla[i-1];
	        	tabla[i-1] = aux;
	        }
	        return ncdc;
	    }
	}
    *ppos = NO_ENCONTRADO;

	return ncdc;
}
