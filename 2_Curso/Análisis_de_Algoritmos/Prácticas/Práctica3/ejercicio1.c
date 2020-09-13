/***********************************************/
/* Programa: ejercicio1     Fecha: 13/12/2017  */
/* Autores: Alejandro Santorum                 */
/*          David Cabornero                    */
/*                                             */
/* Programa que comprueba el funcionamiento de */
/* la busqueda lineal                          */
/*                                             */
/* Entrada: Linea de comandos                  */
/*   -tamanio: numero elementos diccionario    */
/*   -clave:   clave a buscar                  */
/*                                             */
/* Salida: 0: OK, -1: ERR                      */
/***********************************************/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>

#include "permutaciones.h"
#include "busqueda.h"

int main(int argc, char** argv)
{
  int i, nob, pos;
  unsigned int clave, tamanio;
  PDICC pdicc;
  int *perm;

  srand(time(NULL));

  if (argc != 5) {
    fprintf(stderr, "Error en los parametros de entrada:\n\n");
    fprintf(stderr, "%s -tamanio <int> -clave <int>\n", argv[0]);
    fprintf(stderr, "Donde:\n");
    fprintf(stderr, " -tamanio : numero elementos de la tabla.\n");
    fprintf(stderr, " -clave : clave a buscar.\n");
    exit(-1);
  }

  printf("Practica numero 3, apartado 1\n");
  printf("Realizada por: Alejandro Santorum y David Cabornero.\n");
  printf("Grupo: 1201\n");
  printf("Pareja 10.\n");

  /* comprueba la linea de comandos */
  for(i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-tamanio") == 0) {
      tamanio = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-clave") == 0) {
      clave = atoi(argv[++i]);
    } else {
      fprintf(stderr, "Parametro %s es incorrecto\n", argv[i]);
    }
  }

  pdicc = ini_diccionario(tamanio, NO_ORDENADO);
  if (pdicc == NULL) {
    /* error */
    printf("Error: No se puede Iniciar el diccionario\n");
    exit(-1);
  }

  perm = genera_perm(tamanio);
  if (perm == NULL) {
    /* error */
    printf("Error: No hay memoria\n");
    libera_diccionario(pdicc);
    exit(-1);
  }

  nob = insercion_masiva_diccionario(pdicc, perm, tamanio);
  if (nob == ERR) {
    /* error */
    printf("Error: No se puede crear el diccionario memoria\n");
    free(perm);
    libera_diccionario(pdicc);
    exit(-1);
  }

  nob = busca_diccionario(pdicc,clave,&pos,blin_auto);
  
  
  if(nob == ERR){ /* Caso de error */
    printf("Error al buscar la clave %d\n", clave);
  }
  else if(pos == NO_ENCONTRADO){ /* CLave no encontrada */
    printf("La clave %d no se encontro en la tabla\n",clave);
  }
  else{ /* Caso en el que la clave se ha encontrado */
    printf("Clave %d encontrada en la posicion %d en %d op. basicas\n", clave, pos, nob);
  }

/*
  if(nob >= 0) {
    printf("Clave %d encontrada en la posicion %d en %d op. basicas\n", clave, pos, nob);
  } else if (nob==NO_ENCONTRADO) {
    printf("La clave %d no se encontro en la tabla\n",clave);
  } else {
    printf("Error al buscar la clave %d\n",clave);
  }
*/

  free(perm);
  libera_diccionario(pdicc);

  return 0;
}

