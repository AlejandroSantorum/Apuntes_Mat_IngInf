/**
* @brief Ejercicio12b
* Creacion de 100 hilos y en cada uno se calculan
* los primeros N numeros primos, siendo N pasado como argumento
* entrada al programa
* @file ejercicio12b.c
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
#define N_THREADS 100 /*!< Numero de procesos hijo */


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
* @param arg, estructura con todos los argumentos de la fuincion que queramos
* @return void*, debido a la utilizacion de hilos (threads)
*/
void* calculate_primes(void *arg);


int main(int argc, char const *argv[]) {
  pthread_t thr[N_THREADS];
  Structure *est=NULL;
  double total_time=0;
  struct timespec start, end, aux;
  int i, check1, check2;

  if(argc != 2){ /* Error de parámetros de entrada */
    printf("Parámetros de entrada erróneos.\n");
    printf("Introduzca nombre del programa y el número de primos a calcular.\n");
    exit(EXIT_FAILURE);
  }

  est = (Structure *) malloc(sizeof(Structure));
  if(!est){
    printf("%s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  est->n = atoi(argv[1]);

  check1 = clock_gettime(CLOCK_REALTIME, &start); /* Obtenemos el tiempo inicial */

  for(i=0; i<N_THREADS; i++){
    pthread_create(&thr[i], NULL, calculate_primes, (void *)est); /* Creacion de threads*/
  }

  for(i=0; i<N_THREADS; i++){
    pthread_join(thr[i], NULL); /* Esperamos por todas las threads */
  }

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

  printf("El tiempo necesitado para crear %d HILOS y calcular los\n", N_THREADS);
  printf("%d primos primos en cada uno de ellos ha sido de:\n", atoi(argv[1]));
  printf("%0.1f nanosegundos = %0.4f segundos\n", total_time, (total_time/TENTOTHENINE));

  free(est);

  exit(EXIT_SUCCESS);

  exit(EXIT_SUCCESS);
}



int is_prime(int n){
  int k;

  for(k=2; k<=sqrt(n); k++){
    if(!(n % k)) return 0;
  }
  return 1;
}



void* calculate_primes(void *arg){
  Structure *est;
  int *primes=NULL;
  int counter=0, i;
  int n;

  if(!arg){
    printf("Error de memoria. Estructura de argumentos de entrada a NULL.\n");
    return NULL;
  }

  est = (Structure *) arg;
  n = est->n;

  primes = (int *) malloc(n * sizeof(int));
  if(!primes){
    printf("Error de memoria.\n");
    return NULL;
  }

  primes[0] = 2; /* El 2 no es necesario de calcular */
  counter++;

  i = 3;
  while(counter < n){
    if(is_prime(i)){
      primes[counter] = i;
      counter++;
    }
    i++;
  }
  free(primes);
  return NULL;
}
