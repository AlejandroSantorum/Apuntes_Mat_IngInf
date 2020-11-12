/**
* @brief Ejercicio5
*
* Este ejercicio tiene un fin educativo e introductorio a los mensajes en C
* @file ejercicio5.c
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
#include <sys/msg.h>
#include "semaforos.h"


#define NUM_PROC 3 /*!< Numero de procesos */
#define PATH "/bin/bash" /*!< Directorio para obtener la key */
#define ERROR -1 /*!< Constante de error */
#define FILE_N_BYTES 8192
#define SIZE 2048
#define SEM_SIZE 1

struct msgbuf{
    long mtype; /* type of message */
    char mtext[SIZE]; /* message text */
};

/**
* @brief devuelve un numero entero aleatorio en el intervalo (limites incluidos)
*
* @param inf - limite inferior intervalo
* @param sup - limite superior intervalo
* @return entero aleatorio en el intervalo. Corta ejecucion en caso de error.
*/
int aleat_num(int inf, int sup);

/**
* @brief funcion que implementa la funcionalidad del proceso A
*
* @param msgid - id de la cola de mensajes 1
* @param filename - nombre del fichero donde lee el proceso A
* @param pid_b - PID del proceso B para enviarle una señal una vez A termine
* @return void.
*/
void process_a(int msgid, char *filename, int pid_b);


/**
* @brief funcion que implementa la funcionalidad del proceso B
*
* @param msgid1 - id de la cola de mensajes 1
* @param msgid2 - id de la cola de mensajes 2
* @param pid_c - PID del proceso C para enviarle una señal una vez B termine
* @return void.
*/
void process_b(int msgid1, int msgid2, int pid_c);


/**
* @brief funcion que implementa la funcionalidad del proceso C
*
* @param msgid - id de la cola de mensajes 2
* @param filename - nombre del fichero donde escribe el proceso C
* @return void.
*/
void process_c(int msgid, char *filename);


/**
* @brief nuevo manejador de la señal SIGUSR1.
* Su funcionalidad es simplemente obligar al proceso a no ignorar la señal.
* Ademas, pone la variable global de control a 1
*
* @param sig - la señal que utilizará este manejador cuando sea llamada
* @return void.
*/
void handler_SIGUSR1(int sig);


volatile int flag = 0;

int main(int argc, char *argv[]){
    int key_msg1, key_msg2, msgid2, msgid1, i, pid[NUM_PROC];
    void handler_SIGUSR1();

    if(argc != 3){ /* Error */
        printf("Error de entrada: parametros incorrectos.\n");
        printf("Por favor. Introduzca el nombre del programa, el nombre del fichero 1 y el nombre del fichero 2\n");
        exit(EXIT_FAILURE);
    }

    if(signal(SIGUSR1, handler_SIGUSR1)==SIG_ERR){
        perror("Error estableciendo el nuevo manejador de SIGUSR1"); /* Error */
        exit(EXIT_FAILURE);
    }

    /*Creación de la cola de mensajes 1*/
    if((key_msg1 = ftok(PATH,aleat_num(1000, 3000))) == ERROR){
        perror("Error al hacer ftok para la creacion de cola de mensajes (1)");
        exit(EXIT_FAILURE);
    }

    msgid1 = msgget(key_msg1, IPC_CREAT|IPC_EXCL|0660);
    if(msgid1==ERROR && errno==EEXIST) { /* La cola de mensajes ya existe */
        msgid1 = msgget(key_msg1, IPC_CREAT|0660);
    } else if(msgid1==ERROR){
       perror("Error al crear la cola de mensajes (1)");
       exit(EXIT_FAILURE);
    }

    /*Creación de la cola de mensajes 2*/
    if((key_msg2 = ftok(PATH, aleat_num(5000, 7000))) == ERROR){
        perror("Error al hacer ftok para la creacion de cola de mensajes (2)");
        exit(EXIT_FAILURE);
    }
    msgid2 = msgget(key_msg1, IPC_CREAT|IPC_EXCL|0660);
    if(msgid2==ERROR && errno==EEXIST) { /* La cola de mensajes ya existe */
        msgid2 = msgget(key_msg2, IPC_CREAT|0660);
    } else if(msgid2==ERROR){
       perror("Error al crear la cola de mensajes (2)");
       exit(EXIT_FAILURE);
    }

    /*Creación de hijos*/
    for(i=0; i<NUM_PROC; i++){
        if((pid[i] = fork()) < 0){
            printf("Error al crear los hijos.\n");
            exit(EXIT_FAILURE);
        }

        if(!pid[i]){
            break;
        }
    }
    /*Fin de la creacion de hijos*/

    /*Proceso C*/
    if(i == 0){
        process_c(msgid2, argv[2]);
    }

    /*Proceso B*/
    else if(i == 1){
        process_b(msgid1, msgid2, pid[0]);
    }

    /*Proceso A*/
    else if(i == 2){
        process_a(msgid1, argv[1], pid[1]);
    }

    while(wait(NULL)>0);

    /* Nos desprendemos de las colas de mensajes */
    if(msgctl(msgid1,IPC_RMID,NULL)==ERROR){
      perror("Error eliminando la cola de mensajes 1");
    }
    if(msgctl(msgid2,IPC_RMID,NULL)==ERROR){
      perror("Error eliminando la cola de mensajes 2");
    }

    exit(EXIT_SUCCESS);
}


void process_a(int msgid, char *filename, int pid_b){
    FILE *f=NULL;
    struct msgbuf msg_arg={0};

    if(msgid<0 || filename==NULL ||pid_b<0){ /* Comprobacion de errores */
        perror("Error en los argumentos de entrada en process_a function\n");
        exit(EXIT_FAILURE);
    }

    f = fopen(filename, "r");
    if(f==NULL){ /* Error */
        perror("Error abriendo el fichero en process_a function");
        exit(EXIT_FAILURE);
    }

    msg_arg.mtype = 1; /* EL proceso A mete tipo 1 y el proceso B coge tipo 1 */
    while(!feof(f)){ /* Leemos del fichero de 2KB en 2KB y enviamos la informacion con mensajes */
        fread(msg_arg.mtext, SIZE, 1, f);

        if(msgsnd(msgid, (struct msgbuf *)&msg_arg, SIZE, 0) == -1){
            perror("Error enviando mensaje desde A\n");
            exit(EXIT_FAILURE);
        }
        memset(msg_arg.mtext,0,sizeof(msg_arg));
    }
    fclose(f);
    if(kill(pid_b, SIGUSR1)){ /* Si kill != 0 entonces ERROR */
        printf("%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}


void process_b(int msgid1, int msgid2, int pid_c){
    struct msqid_ds buf = {{0}};
    struct msgbuf msg_rcv = {0};
    int num_msg, i;

    if(msgid1<0 || msgid2<0 || pid_c<0){ /* Comprobacion de errores */
        perror("Error en los argumentos de entrada en process_b function");
        exit(EXIT_FAILURE);
    }

    while(1){
        if(flag == 1){ /* flag==1 el proceso A ha acabado */
            if(msgctl(msgid1, IPC_STAT, &buf)==-1){
                perror("Error obteniendo la informacion de la cola en process_b function");
                exit(EXIT_FAILURE);
            }
            num_msg = buf.msg_qnum;
            if(num_msg==0){ /* Si el numero de mensajes en la cola 1, el proceso B ha acabado su mision */
                break;
            }
        }

        /* Leemos de la cola de mensajes */
        if(msgrcv(msgid1, (struct msgbuf *)&msg_rcv, SIZE, 1, 0) == -1){
            if(errno == EINTR){
              break;
            }
            perror("Error recibiendo mensaje en B\n");
            exit(EXIT_FAILURE);
        }

        for(i=0; i<SIZE; i++){ /* Realizamos cambios */
            if(msg_rcv.mtext[i] == 'z') msg_rcv.mtext[i] = 'a';
            else if(msg_rcv.mtext[i] < 'z' && msg_rcv.mtext[i] >= 'a') msg_rcv.mtext[i] = msg_rcv.mtext[i]+1;

            if(msg_rcv.mtext[i] == 'Z') msg_rcv.mtext[i] = 'A';
            else if(msg_rcv.mtext[i] < 'Z' && msg_rcv.mtext[i] >= 'A') msg_rcv.mtext[i] = msg_rcv.mtext[i]+1;
            /* Si es otro caracter, no sera variado */
        }

        msg_rcv.mtype = 2; /* De B a C mensajes de tipo 2 */

        /* Espera activa */
        while(msgsnd(msgid2, (struct msgbuf *)&msg_rcv, (SIZE), IPC_NOWAIT) == -1);
        memset(msg_rcv.mtext,0,sizeof(msg_rcv));

    }
    if(kill(pid_c, SIGUSR1)){ /* Si kill != 0 entonces ERROR */
        printf("%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}


void process_c(int msgid, char *filename){
    struct msqid_ds buf = {{0}};
    struct msgbuf msg_rcv={0};
    int num_msg, check;
    FILE *f=NULL;


    if(msgid<0 || filename==NULL){ /* Comprobacion de errores */
        perror("Error en los argumentos de entrada en process_c function\n");
        exit(EXIT_FAILURE);
    }

    f = (FILE *) fopen(filename, "w");
    if(f==NULL){ /* Error */
        perror("Error abriendo el fichero de escritura en el proceso C");
        exit(EXIT_FAILURE);
    }

    while(1){
        if(flag == 1){ /* flag==1 el proceso B ha acabado */
            if(msgctl(msgid, IPC_STAT, &buf)==-1){
                perror("Error obteniendo la informacion de la cola en process_c function");
                exit(EXIT_FAILURE);
            }
            num_msg = buf.msg_qnum;
            if(num_msg==0){ /* Si el numero de mensajes en la cola 1, el proceso C ha acabado su mision */
                break;
            }
        }

        /* Leemos mensaje */
        if((check = msgrcv(msgid, (struct msgbuf *)&msg_rcv, (SIZE), 2, 0)) == -1){
            if(errno == EINTR){
                break;
            }
            perror("Error recibiendo mensaje en C\n");
            exit(EXIT_FAILURE);
        }
        else if(check > 0){
          /* Escribimos lo recibido */
          fprintf(f,"%s",msg_rcv.mtext);
        }

    }
    fclose(f);
    exit(EXIT_SUCCESS);
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
    flag=1; /* Proceso acabado */
    return;
}
