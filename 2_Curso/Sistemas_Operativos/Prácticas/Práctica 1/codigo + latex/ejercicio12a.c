/**
* @brief Ejercicio12a
* Creacion de 100 procesos y en cada uno se calculan
* los primeros N numeros primos, siendo N pasado como argumento
* entrada al programa
* @file ejercicio12a.c
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
#include <pthread.h>
#include <limits.h>
#include <time.h>
#include <math.h>

#define LEN 100 /*!< Longitud de las cadenas de caracteres*/
#define TENTOTHENINE 1000000000 /*!< Constante */
#define N_CHILDS 100 /*!< Numero de procesos hijo */

/**
* @brief Estructura programa
*
* Esta estructura contiene una cadena de caracteres y un entero.
*/
typedef struct{
  char str[LEN]; /*!< cadena de caracteres */
  int n; /*!< numero entero */
} Structure;


/**
* @brief evalua si un numero es primo o no.
*
* @param n entero a ser evaluado
* @return true si es primo, false si no.
*/
int is_prime(int n);


/**
* @brief devuelve un array con los n_primes primeros primos
*
* @param n_primes numero de primeros primos a ser calculados
* @return array de primos
*/
int* calculate_primes(int n_primes);


int main(int argc, char const *argv[]) {
  int pid, i, check1, check2;
  int *primes=NULL;
  Structure *est=NULL;
  double total_time=0;
  struct timespec start, end, aux;

  if(argc != 2){ /* Error de parametros de entrada */
    printf("Parámetros de entrada erróneos.\n");
    printf("Introduzca nombre del programa y el número de primos a calcular.\n");
    exit(EXIT_FAILURE);
  }

  est = (Structure *) malloc(sizeof(Structure));
  if(!est){
    printf("%s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  check1 = clock_gettime(CLOCK_REALTIME, &start); /* Obtenemos el tiempo inicial */

  for(i=0; i<N_CHILDS; i++){
    if((pid = fork()) < 0){
      printf("Error haciendo fork en la iteración número %d", i);
      free(est);
      exit(EXIT_FAILURE);
    }
    if(!pid) break;
  }
  if(!pid){
    primes = calculate_primes(atoi(argv[1]));
    if(!primes){
      printf("Error reservando memoria para el array.\n");
      free(est);
      exit(EXIT_FAILURE);
    }
    /* AQUÍ HARÍAMOS ALGO CON EL ARRAY DE PRIMOS CALCULADO
       SI EL ENUNCIADO ESPECIFICARA ALGO */
    free(primes);

    exit(EXIT_SUCCESS);
  }
  while(wait(NULL) >= 0); /* Esperamos a que todos los procesos hijos finalicen */

  check2 = clock_gettime(CLOCK_REALTIME, &end); /* Obtenemos el tiempo final */

  if(check1==-1){
    printf("Error calculando el tiempo inicial.\n");
    free(est);
    exit(EXIT_FAILURE);
  }
  if(check2==-1){
    printf("Error calculando el tiempo final.\n");
    free(est);
    exit(EXIT_FAILURE);
  }

  aux.tv_sec = end.tv_sec - start.tv_sec; /* Calculamos los segundos */
  aux.tv_nsec = end.tv_nsec - start.tv_nsec; /* Calculamos los nanosegundos */
  total_time = total_time + aux.tv_sec*TENTOTHENINE + aux.tv_nsec; /* Guardamos el tiempo en nanosegundos */

  printf("El tiempo necesitado para crear %d procesos y calcular los\n", N_CHILDS);
  printf("%d primes primes en cada uno de ellos ha sido de:\n", atoi(argv[1]));
  printf("%0.1f nanosegundos = %0.4f segundos\n", total_time, (total_time/TENTOTHENINE));

  free(est);

  exit(EXIT_SUCCESS);
}



int is_prime(int n){
  int k;

  for(k=2; k<=sqrt(n); k++){
    if(!(n % k)) return 0;
  }
  return 1;
}



int* calculate_primes(int n_primes){
  int *primes=NULL;
  int counter=0, i;

  primes = (int *) malloc(n_primes * sizeof(int));
  if(!primes){
    printf("Error de memoria.\n");
    return NULL;
  }

  primes[0] = 2; /* El 2 no es necesario de calcular */
  counter++;

  i = 3;
  while(counter < n_primes){
    if(is_prime(i)){
      primes[counter] = i;
      counter++;
    }
    i++;
  }
  return primes;
}
