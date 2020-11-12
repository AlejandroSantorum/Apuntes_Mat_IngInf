/**
* @brief Ejercicio2
*
* Este ejercicio sirve de ejemplo de por que los semaforos son importantes
* @file ejercicio2.c
* @author Alejandro Santorum & David Cabornero (G2202-Pareja7)
* @version 1.0
* @date 16-04-2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <ctype.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "semaforos.h"

#define BUFFER_SIZE 80 /*!< Tamaño del buffer de lectura de ficheros */
#define PATH "/bin/bash" /*!< Directorio para obtener la key */
#define ERROR -1 /*!< Constante de error */
#define NOT_INTEGER 0 /*!< Constante de error en la funcion is_valid_integer*/
#define IS_INTEGER 1 /*!< Constante de exito en la funcion is_valid_integer*/

/**
* @brief Estructura programa
*
* Esta estructura contiene una cadena de caracteres y un entero.
*/
typedef struct{
    char nombre[BUFFER_SIZE]; /*!< cadena de caracteres */
    int id; /*!< numero entero */
}info;


/**
* @brief evalua si un argumento de entrada es verdaderamente un entero
*
* @param input - contiene la cadena de caracteres sospechosa de ser un entero
* @return 1 si es un entero, 0 en caso contrario.
*/
int is_valid_integer(char *input);


/**
* @brief devuelve un numero entero aleatorio en el intervalo (limites incluidos)
*
* @param inf - limite inferior intervalo
* @param sup - limite superior intervalo
* @return entero aleatorio en el intervalo. Corta ejecucion en caso de error.
*/
int aleat_num(int inf, int sup);


/**
* @brief nuevo manejador de la señal SIGUSR1.
* Su funcionalidad es simplemente obligar al proceso a no ignorar la señal.
*
* @param sig - la señal que utilizará este manejador cuando sea llamada
* @return void.
*/
void handler_SIGUSR1(int sig);


int main(int argc, char *argv[]){
    int childs, pid, key, id_zone, i;
    void handler_SIGUSR1();
    sigset_t set, oset;
    info *information;

    if(argc != 2){
        printf("Error al pasar los argumentos. Introduce el numero de procesos hijo.\n");
        exit(EXIT_FAILURE);
    }

    if(!is_valid_integer(argv[1])) {
        printf("Error, el numero de procesos hijo debe ser un entero.\n");
        exit(EXIT_FAILURE);
    }

    childs = atoi(argv[1]);

    if(childs < 0){
        printf("Error, el numero de procesos hijo debe ser un entero positivo.\n");
        exit(EXIT_FAILURE);
    }

    /*Hacemos que la estuctura esté en memoria compartida*/
    if((key = ftok(PATH, aleat_num(1000, 3000))) == ERROR){
      printf("Error obteniendo la key para utilizar shmget: %s", strerror(errno));
      exit(EXIT_FAILURE);
    }
    id_zone = shmget(key, sizeof(info), IPC_CREAT|SHM_R|SHM_W);
    if(id_zone == ERROR){
        perror("Error al crear la memoria compartida");
        exit(EXIT_FAILURE);
    }

    information = (info *)shmat(id_zone, (char *)0, 0);
    if(information == ((void*)ERROR)){
      printf("Error shmat: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }


    for(i=0; i<childs; i++){
        if((pid = fork())<0){
            printf("Error al crear los procesos hijo.\n");
            shmdt((void *)information);
            shmctl(id_zone, IPC_RMID, (struct shmid_ds *)NULL);
            exit(EXIT_FAILURE);
        }

        if(!pid){
            break;
        }
    }

    /*Código del proceso hijo*/
    if(!pid){
        sleep(aleat_num(1,5));

        printf("Alta del cliente del proceso %d: ", i+1);
        fgets(information->nombre, BUFFER_SIZE, stdin);
        information->id++;

        kill(getppid(), SIGUSR1);

        exit(EXIT_SUCCESS);
    }

    /*Código del proceso padre*/
    if(signal(SIGUSR1, handler_SIGUSR1)==SIG_ERR){ /* Armamos nuevo manejador de la señal SIGUSR1 */
        printf("Error estableciendo el nuevo manejador de SIGTERM.\n"); /* Error */
        shmdt((void *)information);
        shmctl(id_zone, IPC_RMID, (struct shmid_ds *)NULL);
        exit(EXIT_FAILURE);
    }

    if(sigfillset(&set)){  /* Creamos un conjunto de señales vacio */
            printf("Error en sigfillset(&set)\n"); /* Error */
            shmdt((void *)information);
            shmctl(id_zone, IPC_RMID, (struct shmid_ds *)NULL);
            exit(EXIT_FAILURE);
    }

    if(sigaddset(&set, SIGUSR1)){ /*Añadimos nuestra señal únicamente al padre*/
        printf("Error en sigaddset(&set)º"); /* Error */
        shmdt((void *)information);
        shmctl(id_zone, IPC_RMID, (struct shmid_ds *)NULL);
        exit(EXIT_FAILURE);
    }

    if(sigprocmask(SIG_BLOCK, &set, &oset)){
        printf("Error en sigprocmask\n"); /* Error */
        shmdt((void *)information);
        shmctl(id_zone, IPC_RMID, (struct shmid_ds *)NULL);
        exit(EXIT_FAILURE);
    }

    for(i=0; i<childs; i++){/**Bucle en el que el padre esperará a sus hijos*/
        sigsuspend(&oset);
        printf("Nombre: %s", information->nombre);
        printf("Identificador: %d\n", information->id);
    }
    while(wait(NULL)!=-1);

    shmdt((void *)information);
    shmctl(id_zone, IPC_RMID, (struct shmid_ds *)NULL);

    exit(EXIT_SUCCESS);
}




int is_valid_integer(char *input){
    int len, i;

    if(!input){
        printf("Error. Input igual a NULL\n");
        exit(EXIT_FAILURE);
    }

    len = strlen(input);

    for(i=0; i<len; i++){
        if(!isdigit(input[i])){
         printf("ERROR. El parámetro introducido no es un entero positivo.\n");
         return NOT_INTEGER;
      }
    }
    if(!atoi(input)){
      printf("ERROR. No se admite cero como entero de entrada.\n");
      return NOT_INTEGER;
   }
   return IS_INTEGER;
}

int aleat_num(int inf, int sup){
    int result = 0;

    if(inf == sup){
        return sup;
    }

    else if (inf > sup){
        printf("ERROR: Límite inferior mayor que el límite superior.\n");
        exit(EXIT_FAILURE);
    }

    result = (inf + ((int) ((((double)(sup-inf+1)) * rand())/(RAND_MAX + 1.0))));

    return result;
}

void handler_SIGUSR1(int sig){
    return;
}
