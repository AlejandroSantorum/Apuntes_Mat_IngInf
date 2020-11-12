/**
* @brief Ejercicio2
* Creación de 4 procesos hijos que duermen durante 30s
* mientras que el proceso padre espera 5s y después envía
* a cada proceso hijo la señal de finalización SIGTERM
* @file ejercicio2.c
* @author Alejandro Santorum & David Cabornero (G2202-Pareja7)
* @version 1.0
* @date 31-03-2018
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

#define N_CHILDS 4 /*!< Número de procesos hijos */

int main(){
    int pid, i = 0;
    
    for(i = 0; i<N_CHILDS; i++){ 
        if((pid = fork())<0){
            printf("Fork function Error: %s\n", strerror(errno)); /* Error */
            exit(EXIT_FAILURE);
        }
        
        /* Zona de actuación procesos hijos */
        if(!pid){
            printf("Soy el proceso hijo %d\n", getpid());
            fflush(stdout);
            sleep(30);
            printf("Soy el proceso hijo %d y ya me toca terminar\n",getpid());
            break;
            /* Gracias a este break, los procesos hijos nunca ejecutarán el código de abajo */
            /* De todas formas, este programa no deja ni que llegue al segundo printf
            *  debido a la señal de terminacion controlada kill(pid, SIGTERM) */
        }
        
        /* Zona de actuación proceso padre */
        sleep(5);
        if(kill(pid,SIGTERM)){ /* Si kill != 0 entonces ERROR */
            printf("Kill function Error: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }
    
    exit(EXIT_SUCCESS);
}