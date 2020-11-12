#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#define LEER 0
#define ESCRIBIR 1
#define N_HIJOS 4
#define LEN 200

int separar_primero(char *str);

int separar_segundo(char *str);

int factorial(int a);

int abs(int a);

int main(){
  int fd[2*N_HIJOS][2];
  int fpid, h, i;
  int ids[4];
  int O1, O2;
  float O3;
  char str_write[LEN], str_read[LEN];

  fpid = getpid();

  for(h=0; h<2*N_HIJOS; h++){
    if(pipe(fd[h]) == -1){
      printf("Error creando pipe número %d", h);
      exit(EXIT_FAILURE);
    }
  }

  for(h=0; h<N_HIJOS; h++){
    if(getpid() == fpid){
      if((ids[h] = fork()) < 0){
        printf("Error. Fork número %d", h);
        exit(EXIT_FAILURE);
      }
      if(getpid() != fpid){
        break;
      }
    }
  }

  if(getpid() == fpid){
    fflush(stdin);
    printf("Introduzca el primer operando: ");
    scanf("%d", &O1);
    fflush(stdin);
    printf("Introduzca el segundo operando: ");
    scanf("%d", &O2);

    sprintf(str_write, "%d,%d", O1, O2);

    for(i=0; i<N_HIJOS; i++){
      close(fd[i][LEER]); /* Cerramos lectura */
      write(fd[i][ESCRIBIR], str_write, strlen(str_write)); /* Enviamos los operandos */
    }
  }

  if(h == 0){
    memset(str_read,0,LEN);
    memset(str_write,0,LEN);
    close(fd[h][ESCRIBIR]);
    read(fd[h][LEER], str_read, LEN);

    O1 = separar_primero(str_read);
    O2 = separar_segundo(str_read);

    O3 = pow(O1,O2);

    sprintf(str_write, "Datos enviados a través de la tubería por el proceso PID=%d. Operando 1: %d. Operando 2: %d. Potencia: %.2f \n", getpid(), O1, O2, O3);

    close(fd[h+4][LEER]); /* Cerramos lectura */
    write(fd[h+4][ESCRIBIR], str_write, strlen(str_write)); /* Enviamos los operandos */
  }

  if(h == 1){
    memset(str_read,0,LEN);
    memset(str_write,0,LEN);
    close(fd[h][ESCRIBIR]);
    read(fd[h][LEER], str_read, LEN);

    O1 = separar_primero(str_read);
    O2 = separar_segundo(str_read);
    if(O1<0 || O2<0){
      sprintf(str_write,"Datos enviados a través de la tubería por el proceso PID=%d. Operando 1: %d. Operando 2: %d. No se puede hacer el factorial \n", getpid(), O1, O2);
    }
    else{
      O3 = (float)factorial(O1)/(float)(O2);

      sprintf(str_write,"Datos enviados a través de la tubería por el proceso PID=%d. Operando 1: %d. Operando 2: %d. Factorial entre el numero: %.2f \n", getpid(), O1, O2, O3);
    }

    close(fd[h+4][LEER]); /* Cerramos lectura */
    write(fd[h+4][ESCRIBIR], str_write, strlen(str_write)); /* Enviamos los operandos */
  }

  if(h == 2){
    memset(str_read,0,LEN);
    memset(str_write,0,LEN);
    close(fd[h][ESCRIBIR]);
    read(fd[h][LEER], str_read, LEN);

    O1 = separar_primero(str_read);
    O2 = separar_segundo(str_read);

    if(O1<O2 || O1<0 || O2<0){
      sprintf(str_write,"Datos enviados a través de la tubería por el proceso PID=%d. Operando 1: %d. Operando 2: %d. No hay permutacion posible \n", getpid(), O1, O2);
    }
    else{
      O3 = (float)factorial(O1)/(float)factorial(O2);

      sprintf(str_write,"Datos enviados a través de la tubería por el proceso PID=%d. Operando 1: %d. Operando 2: %d. Permutacion: %.2f \n", getpid(), O1, O2, O3);
    }

    close(fd[h+4][LEER]); /* Cerramos lectura */
    write(fd[h+4][ESCRIBIR], str_write, strlen(str_write)); /* Enviamos los operandos */
  }

  if(h == 3){
    memset(str_read,0,LEN);
    memset(str_write,0,LEN);
    close(fd[h][ESCRIBIR]);
    read(fd[h][LEER], str_read, LEN);

    O1 = separar_primero(str_read);
    O2 = separar_segundo(str_read);

    O3 = abs(O1)+abs(O2);

    sprintf(str_write,"Datos enviados a través de la tubería por el proceso PID=%d. Operando 1: %d. Operando 2: %d. Suma de valores absolutos: %.2f \n", getpid(), O1, O2, O3);

    close(fd[h+4][LEER]); /* Cerramos lectura */
    write(fd[h+4][ESCRIBIR], str_write, strlen(str_write)); /* Enviamos los operandos */
  }

  if(fpid == getpid()){
    for(h=0; h < N_HIJOS; h++){
      memset(str_read,0,LEN);
      close(fd[h+4][ESCRIBIR]);
      read(fd[h+4][LEER], str_read, LEN);
      printf("%s",str_read);
    }
  }
  exit(EXIT_SUCCESS);
}


int separar_primero(char *str){
  char *copia, *aux;
  int final;

  aux = (char *)malloc(sizeof(char)*LEN);
  if(aux == NULL){
    printf("Error reservando memoria\n");
    exit(EXIT_FAILURE);
  }
  copia = strcpy((char *) malloc(sizeof(char)*sizeof(str+1)),str);
  aux = strchr(copia, ',');
  *aux = 0;
  final = atoi(copia);
  free(copia);
  return final;
}


int separar_segundo(char *str){
  char *aux;
  int final;

  aux = (char *)malloc(sizeof(char)*LEN);
  if(aux == NULL){
    printf("Error reservando memoria\n");
    exit(EXIT_FAILURE);
  }
  aux = strchr(str, ',');
  aux++;
  final = atoi(aux);
  return final;
}


int factorial(int a){
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
