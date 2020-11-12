/**
* @brief Ejercicio6
* Comprobación de si dos procesos (padre e hijo)
* comparten la misma zona de memoria una vez lanzados.
* @file ejercicio6.c
* @author Alejandro Santorum & David Cabornero (G2202)
* @version 1.0
* @date 02-03-2018
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#define LEN 80 /*!< Longitud cadena de caracteres */

/**
* @brief Estructura programa
*
* Esta estructura contiene una cadena de caracteres y un entero.
*/
typedef struct{
  char str[LEN]; /*!< cadena de caracteres */
  int n; /*!< numero entero */
} Structure;


int main(){
  Structure *est=NULL;
  int pid;

  est = (Structure *) malloc(sizeof(Structure));
  if(!est){ /* Error de memoria */
    printf("%s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  /* Guardamos esto para ver que se imprima */
  /* en el caso en que solo hayamos modificado */
  /* la cadena en el proceso hijo */
  if(strcpy(est->str, "TEXTO GUARDADO ANTES DEL FORK\n")==NULL){
    printf("%s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  pid = fork();

  if(!pid){
    /* Esto se encarga de solo guardar los 79 primeros caracteres + \0
       en el caso que el usuario no haya seguido lo especificado */
    printf("Introduzca un nombre de maximo %d caracteres: ", LEN-1);
    fgets(est->str, LEN-1, stdin);
  }

  wait(NULL);

  printf("%s", est->str); /* Esta intrucción se realiza tanto en el hijo como en el padre */

  free(est); /* Liberamos memoria en ambos */

  exit(EXIT_SUCCESS);
}
