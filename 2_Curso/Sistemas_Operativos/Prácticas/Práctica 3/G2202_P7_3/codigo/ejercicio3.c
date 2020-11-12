/**
* @brief Ejercicio3
*
* Este ejercicio tiene un fin educativo con el problema del productor-consumidor
* @file ejercicio3.c
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

#define SEM_SIZE 3 /*!< Numero de semaforos utilizados */
#define PATH "/bin/bash" /*!< Directorio para obtener la key */
#define IS_INTEGER 1 /*!< Constante de exito en la funcion is_valid_integer*/
#define NOT_INTEGER 0 /*!< Constante de error en la funcion is_valid_integer*/
#define N_PROD 36 /*!< Numero de productor creados */


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
* @brief devuelve el siguiente caracter al recibido.
*
* @param old - el caracter viejo
* @return caracter siguiente al viejo.
*/
char next_char(char old);


int main(int argc, char *argv[]){
    int size_queue, check_sem, semid, keysem, i, pid, id_zone, key;
    unsigned short *sem_array;
    char *buff;
    char item;

    if(argc != 2){
        printf("Error al pasar los argumentos. Introduce la longitud maxima de la cola.\n");
        exit(EXIT_FAILURE);
    }

    if(!is_valid_integer(argv[1])) {
        exit(EXIT_FAILURE);
    }

    size_queue = atoi(argv[1]);

    if(size_queue < 0){
        printf("Error, la longitud maxima de la cola debe ser un entero positivo.\n");
        exit(EXIT_FAILURE);
    }

    /**Creando zona de memoria compartida (nuestro buffer)*/
    if((key = ftok(PATH, aleat_num(3000, 6000))) == ERROR){
        perror("Error realizando ftok - memoria compartida");
        exit(EXIT_FAILURE);
    }
    id_zone = shmget(key, sizeof(char)*size_queue, IPC_CREAT|SHM_R|SHM_W);
    if(id_zone == ERROR){
        printf("Error al crear la memoria compartida");
        exit(EXIT_FAILURE);
    }

    buff = (char *)shmat(id_zone, (char *)0, 0);
    /**Memoria compartida creada*/

    /**Creamos e inicializamos los tres semáforos:
     * 1. El número de entradas vacías (vacio)
     * 2. El número de entradas ocupadas (lleno)
     * 3. Mutex para la memoria compartida (mutex)*/
    if((keysem = ftok(PATH, aleat_num(999, 2999))) == ERROR){
         perror("Error realizando ftok - semaforo");
         exit(EXIT_FAILURE);
    }

    check_sem = Crear_Semaforo(keysem, SEM_SIZE, &semid);
    if(check_sem == ERROR){
        printf("Error en la creacion del conjunto de semaforos\n");
        shmdt(buff);
        shmctl(id_zone, IPC_RMID, (struct shmid_ds *)NULL);
        exit(EXIT_FAILURE);
    }

    sem_array = (unsigned short *) malloc((SEM_SIZE)*sizeof(unsigned short));
    if(!sem_array){
        printf("Error reservando memoria para el array de ids de semaforos involucrados\n");
        exit(EXIT_FAILURE);
    }
    sem_array[0] = size_queue; /* semaforo de numero de entradas vacias en el "almacen" del productor */
    sem_array[1] = 0; /* numero de entradas llenas en el "almacen" del productor */
    sem_array[2] = 1; /* mutex de la memoria compartida */


    if(Inicializar_Semaforo(semid, sem_array) == ERROR){/*Ponemos los semáforos a 1*/
        printf("Error inicializando a 1 todos los semaforos al principio\n");
        Borrar_Semaforo(semid);
        shmdt(buff);
        shmctl(id_zone, IPC_RMID, (struct shmid_ds *)NULL);
        free(sem_array);
        exit(EXIT_FAILURE);
    }
    free(sem_array);
    /**Fin de la creación e inicialización de los semáforos.*/

    /**El proceso padre será el productor, el proceso hijo el consumidor*/
    pid = fork();
    if(pid < 0){
        printf("Error al crear el proceso hijo.\n");
        Borrar_Semaforo(semid);
        shmdt(buff);
        shmctl(id_zone, IPC_RMID, (struct shmid_ds *)NULL);
        exit(EXIT_FAILURE);
    }

    /**Consumidor*/
    if(pid == 0){
        for(i = 0; i<N_PROD; i++){
            sleep(1);
            /*sleep(aleat_num(1,3));*/

            if(Down_Semaforo(semid, 1, SEM_UNDO) == ERROR){/*Bajando el semaforo de lleno*/
                printf("Error bajando el semaforo de lleno.\n");
                Borrar_Semaforo(semid);
                shmdt(buff);
                shmctl(id_zone, IPC_RMID, (struct shmid_ds *)NULL);
                exit(EXIT_FAILURE);
            }
            if(Down_Semaforo(semid, 2, SEM_UNDO) == ERROR){/*Bajando el semaforo de mutex*/
                printf("Error bajando el semaforo de mutex.\n");
                Borrar_Semaforo(semid);
                shmdt(buff);
                shmctl(id_zone, IPC_RMID, (struct shmid_ds *)NULL);
                exit(EXIT_FAILURE);
            }
            /**Entramos en memoria compartida*/
            item = buff[i%size_queue];
            /**Salimos de memoria compartida*/

            if(Up_Semaforo(semid, 2, SEM_UNDO) == ERROR){/*Subiendo el semaforo de mutex*/
                printf("Error subiendo el semaforo de mutex.\n");
                Borrar_Semaforo(semid);
                shmdt(buff);
                shmctl(id_zone, IPC_RMID, (struct shmid_ds *)NULL);
                exit(EXIT_FAILURE);
            }
            if(Up_Semaforo(semid, 0, SEM_UNDO) == ERROR){/*Subiendo el semaforo de vacio*/
                printf("Error subiendo el semaforo de vacio.\n");
                Borrar_Semaforo(semid);
                shmdt(buff);
                shmctl(id_zone, IPC_RMID, (struct shmid_ds *)NULL);
                exit(EXIT_FAILURE);
            }
            /**Imprimimos el item recogido*/
            printf("Producto recogido: %c\n",item);
        }

        exit(EXIT_SUCCESS);
    }

    /**Productor*/
    item = 'A';
    for(i=0; i<N_PROD; i++){
        /*sleep(aleat_num(1,3));*/

        if(Down_Semaforo(semid, 0, SEM_UNDO) == ERROR){/*Bajando el semaforo de vacio*/
            printf("Error bajando el semaforo de vacio.\n");
            Borrar_Semaforo(semid);
            shmdt(buff);
            shmctl(id_zone, IPC_RMID, (struct shmid_ds *)NULL);
            exit(EXIT_FAILURE);
        }
        if(Down_Semaforo(semid, 2, SEM_UNDO) == ERROR){/*Bajando el semaforo de mutex*/
            printf("Error bajando el semaforo de mutex.\n");
            Borrar_Semaforo(semid);
            shmdt(buff);
            shmctl(id_zone, IPC_RMID, (struct shmid_ds *)NULL);
            exit(EXIT_FAILURE);
        }

        /**Entramos en memoria compartida*/
        buff[i%size_queue] = item;
        /**Salimos de memoria compartida*/

        if(Up_Semaforo(semid, 2, SEM_UNDO) == ERROR){/*Subiendo el semaforo de mutex*/
            printf("Error subiendo el semaforo de mutex.\n");
            Borrar_Semaforo(semid);
            shmdt(buff);
            shmctl(id_zone, IPC_RMID, (struct shmid_ds *)NULL);
            exit(EXIT_FAILURE);
        }
        if(Up_Semaforo(semid, 1, SEM_UNDO) == ERROR){/*Subiendo el semaforo de lleno*/
            printf("Error subiendo el semaforo de lleno.\n");
            Borrar_Semaforo(semid);
            shmdt(buff);
            shmctl(id_zone, IPC_RMID, (struct shmid_ds *)NULL);
            exit(EXIT_FAILURE);
        }

        item = next_char(item);
    }
    wait(NULL);

    Borrar_Semaforo(semid);
    shmdt(buff);
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


char next_char(char old){
    char new;

    if((old< 'Z' && old>='A')||(old<'9' && old >='0')){
        new = old + 1;
    }
    else if(old == 'Z'){
        new = '0';
    }
    else if(old == '9'){
        new = 'A';
    }
    else{
        printf("Error en next_char.\n");
        exit(EXIT_FAILURE);
    }

    return new;
}
