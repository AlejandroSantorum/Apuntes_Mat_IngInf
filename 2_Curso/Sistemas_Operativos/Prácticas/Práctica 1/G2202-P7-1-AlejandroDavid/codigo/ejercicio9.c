/**
* @brief Ejercicio9
* Ejercicio de comunicación bidireccional
* entre procesos utilizando tuberias (pipes)
* @file ejercicio9.c
* @author Alejandro Santorum & David Cabornero (G2202)
* @version 1.0
* @date 02-03-2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#define READ 0 /*!< Macro para lectura en tuberias */
#define WRITE 1 /*!< Macro para escritura en tuberias */
#define N_CHILDS 4 /*!< Numero de procesos hijo */
#define LEN 300 /*!< Longitud de las cadenas de caracteres*/

/**
* @brief separa de una cadena el primero Operando
*
* @param str cadena para ser separada
* @return entero que es el primer operando
*/
int split_first(char *str);

/**
* @brief separa de una cadena el segundo Operando
*
* @param str cadena para ser separada
* @return entero que es el segundo operando
*/
int split_second(char *str);

/**
* @brief calcula el factorial
*
* @param a entero para calcular su factorial
* @return entero factorial
*/
long long factorial(int a);

/**
* @brief calcula el valor absoluto
*
* @param a entero para calcular su valor absoluto
* @return entero valor absoluto
*/
int abs(int a);

int main(){
  int fd[2*N_CHILDS][2];
  int fpid, h, i;
  int ids[4];
  int O1, O2;
  long long O3;
  char str_write[LEN], str_read[LEN];

  fpid = getpid();

  for(h=0; h<2*N_CHILDS; h++){ /* Creacion de las tuberias de comunicacion */
    if(pipe(fd[h]) == -1){ /* Error de creacion de tuberias */
      printf("Error creando pipe número %d", h);
      exit(EXIT_FAILURE);
    }
  }

  for(h=0; h<N_CHILDS; h++){ /* Creacion de procesos */
    if(getpid() == fpid){
      if((ids[h] = fork()) < 0){
        printf("Error. Fork número %d", h);
        exit(EXIT_FAILURE);
      }
      if(getpid() != fpid){ /* Si no estamos en el proceso padre, no queremos hacer mas forks */
        break;
      }
    }
  }

  if(getpid() == fpid){
    fflush(stdin);
    /* Pedimos los operandos por pantalla al usuario */
    printf("Introduzca el primer operando: ");
    scanf("%d", &O1);
    fflush(stdin);
    printf("Introduzca el second operando: ");
    scanf("%d", &O2);

    sprintf(str_write, "%d,%d", O1, O2);

    for(i=0; i<N_CHILDS; i++){
      close(fd[i][READ]); /* Cerramos lectura */
      write(fd[i][WRITE], str_write, strlen(str_write)); /* Enviamos los operandos */
    }
  }
  /* ----------------------------------------------------------------------- */

  /* Cada hijo realiza su operacion y devuelve el resultado al proceso
    padre para ser mostrado por pantalla */
  if(h == 0){
    memset(str_read,0,LEN);
    memset(str_write,0,LEN);
    close(fd[h][WRITE]);
    read(fd[h][READ], str_read, LEN);

    O1 = split_first(str_read);
    O2 = split_second(str_read);

    O3 = pow(O1,O2);
    sprintf(str_write,"Datos enviados a través de la tubería por el proceso PID=%d. Operando 1: %d. Operando 2: %d. Potencia: %.2lli \n", getpid(), O1, O2, O3);

    close(fd[h+N_CHILDS][READ]); /* Cerramos lectura */
    /* Enviamos los operandos */
    write(fd[h+N_CHILDS][WRITE], str_write, strlen(str_write));
  }

  if(h == 1){
    memset(str_read,0,LEN);
    memset(str_write,0,LEN);
    close(fd[h][WRITE]);
    read(fd[h][READ], str_read, LEN);

    O1 = split_first(str_read);
    O2 = split_second(str_read);
    if(O1<0 || O2<0){
        sprintf(str_write,"Datos enviados a través de la tubería por el proceso PID=%d. Operando 1: %d. Operando 2: %d. No se puede hacer el factorial \n", getpid(), O1, O2);
    }else if(!O2){
        sprintf(str_write, "Datos enviados a través de la tubería por el proceso PID=%d. Operando 1: %d. Operando 2: %d. No se puede dividir entre cero\n", getpid(), O1, O2);
    }else{
        O3 = (long long)factorial(O1)/(long long)(O2);
        sprintf(str_write,"Datos enviados a través de la tubería por el proceso PID=%d. Operando 1: %d. Operando 2: %d. Factorial entre el numero: %.2lli \n", getpid(), O1, O2, O3);
    }
    close(fd[h+N_CHILDS][READ]); /* Cerramos lectura */
    write(fd[h+N_CHILDS][WRITE], str_write, strlen(str_write)); /* Enviamos los operandos */
  }

  if(h == 2){
    memset(str_read,0,LEN);
    memset(str_write,0,LEN);
    close(fd[h][WRITE]);
    read(fd[h][READ], str_read, LEN);

    O1 = split_first(str_read);
    O2 = split_second(str_read);

    if(O1<O2 || O1<0 || O2<0){
        sprintf(str_write,"Datos enviados a través de la tubería por el proceso PID=%d. Operando 1: %d. Operando 2: %d. No hay permutacion posible \n", getpid(), O1, O2);
    }else{
        O3 = ((long long)factorial(O1))/((long long)factorial(O2));
        sprintf(str_write,"Datos enviados a través de la tubería por el proceso PID=%d. Operando 1: %d. Operando 2: %d. Permutacion: %.2lli \n", getpid(), O1, O2, O3);
    }
    close(fd[h+N_CHILDS][READ]); /* Cerramos lectura */
    write(fd[h+N_CHILDS][WRITE], str_write, strlen(str_write)); /* Enviamos los operandos */
  }

  if(h == 3){
    memset(str_read,0,LEN);
    memset(str_write,0,LEN);
    close(fd[h][WRITE]);
    read(fd[h][READ], str_read, LEN);

    O1 = split_first(str_read);
    O2 = split_second(str_read);

    O3 = abs(O1)+abs(O2);

    sprintf(str_write,"Datos enviados a través de la tubería por el proceso PID=%d. Operando 1: %d. Operando 2: %d. Suma de valores absolutos: %.2lli \n", getpid(), O1, O2, O3);

    close(fd[h+4][READ]); /* Cerramos lectura */
    write(fd[h+4][WRITE], str_write, strlen(str_write)); /* Enviamos los operandos */
  }

  if(fpid == getpid()){
    for(h=0; h < N_CHILDS; h++){
      memset(str_read,0,LEN);
      close(fd[h+N_CHILDS][WRITE]);
      read(fd[h+N_CHILDS][READ], str_read, LEN);
      printf("%s",str_read);
    }
  }
  exit(EXIT_SUCCESS);
}


int split_first(char *str){
  char *copia, *aux;
  int final;

  aux = (char *)malloc(sizeof(char)*LEN);
  if(aux == NULL){
    printf("Error reservando memoria (split_first function)\n");
    exit(EXIT_FAILURE);
  }
  copia = strcpy((char *) malloc(sizeof(char)*sizeof(str+1)),str);
  aux = strchr(copia, ',');
  *aux = 0;
  final = atoi(copia);
  free(copia);
  return final;
}


int split_second(char *str){
  char *aux;
  int final;

  aux = (char *)malloc(sizeof(char)*LEN);
  if(aux == NULL){
    printf("Error reservando memoria (split_second function)\n");
    exit(EXIT_FAILURE);
  }
  aux = strchr(str, ',');
  aux++;
  final = atoi(aux);
  return final;
}


long long factorial(int a){
  if(a<0){
    printf("Error al calcular el factorial, el numero es negativo.\n");
    return -1;
  }

  if(a==0 || a==1){
    return 1;
  }

  return a*factorial(a-1);
}


int abs(int a){
  if(a<0){
    return -a;
  }
  return a;
}
