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

#define LEN 100
#define TENTOTHENINE 1000000000
#define N_HIJOS 100

typedef struct{
  char cad[LEN];
  int n;
} Estruct;


/**
* Función que evalua si un número entero es primo o no
* ENTRADA: n = número entero a evaluar
* SALIDA: 1 si n es primo, 0 si no lo es
*/
int esPrimo(int n);


/**
* Función que calcula los n primeros primos
* ENTRADA: n_primos = el número de primeros primos a calcular
* SALIDA: array de primos calculados, o NULL si ha habiado algún error
*/
int* calcularPrimos(int n_primos);


int main(int argc, char const *argv[]) {
  int pid, i, check1, check2;
  int *primos=NULL;
  Estruct *est=NULL;
  double total_time=0;
  struct timespec start, end, aux;

  if(argc != 2){
    printf("Parámetros de entrada erróneos.\n");
    printf("Introduzca nombre del programa y el número de primos a calcular.\n");
    exit(EXIT_FAILURE);
  }

  est = (Estruct *) malloc(sizeof(Estruct));
  if(!est){
    printf("%s\n", strerror(errno));
    return EXIT_FAILURE;
  }

  check1 = clock_gettime(CLOCK_REALTIME, &start); /* Obtenemos el tiempo inicial */

  for(i=0; i<N_HIJOS; i++){
    if((pid = fork()) < 0){
      printf("Error haciendo fork en la iteración número %d", i);
      free(est);
      exit(EXIT_FAILURE);
    }
    if(!pid) break;
  }
  if(!pid){
    primos = calcularPrimos(atoi(argv[1]));
    if(!primos){
      printf("Error reservando memoria para el array.\n");
      free(est);
      exit(EXIT_FAILURE);
    }
    /* AQUÍ HARÍAMOS ALGO CON EL ARRAY DE PRIMOS CALCULADO
       SI EL ENUNCIADO ESPECIFICARA ALGO */
    free(primos);

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

  printf("El tiempo necesitado para crear %d procesos y calcular los\n", N_HIJOS);
  printf("%d primos primos en cada uno de ellos ha sido de:\n", atoi(argv[1]));
  printf("%0.1f nanosegundos = %0.4f segundos\n", total_time, (total_time/TENTOTHENINE));

  free(est);

  exit(EXIT_SUCCESS);
}



int esPrimo(int n){
  int k;

  for(k=2; k<=sqrt(n); k++){
    if(!(n % k)) return 0;
  }
  return 1;
}



int* calcularPrimos(int n_primos){
  int *primos=NULL;
  int contador=0, i;

  primos = (int *) malloc(n_primos * sizeof(int));
  if(!primos){
    printf("Error de memoria.\n");
    return NULL;
  }

  primos[0] = 2; /* El 2 no es necesario de calcular */
  contador++;

  i = 3;
  while(contador < n_primos){
    if(esPrimo(i)){
      primos[contador] = i;
      contador++;
    }
  }
  return primos;
}
