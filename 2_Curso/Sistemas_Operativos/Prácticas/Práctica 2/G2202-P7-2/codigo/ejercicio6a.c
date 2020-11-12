/**
* @brief Ejercicio6a
* Toma de contacto con la funcion alarm()
* @file ejercicio6a.c
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
#include <ctype.h>

#define NUM 5 /*!< Número de impresiones */

int main(int argc, char *argv[]){
    int pid, counter;
    sigset_t set, oset;
    
    if((pid = fork()) < 0){
        printf("Fork function Error: %s", strerror(errno)); /* Error */
        exit(EXIT_FAILURE);
    } 
    if (!pid){ /* Zona acción proceso hijo */
        if(alarm(40)){ /* Establecemos alarma */
            printf("Error: ya estía una alarma previamente establecida.\n"); /* Error */
            exit(EXIT_FAILURE);
        } 
        
        while(1){
            if(sigemptyset(&set)){ /* Creamos conjunto de señales vacío */
                printf("Error en sigemptyset(&set)"); /* Error */
                exit(EXIT_FAILURE);
            }
            if(sigemptyset(&oset)){ /* Creamos conjunto de señales vacío */
                printf("Error en sigemptyset(&oset)"); /* Error */
                exit(EXIT_FAILURE);
            }
            
            if(sigaddset(&set, SIGUSR1)){ /* Añadimos la señal SIGUSR1 al conjunto */
                printf("Error incluyendo la señal SIGUSR1\n"); /* Error */
                exit(EXIT_FAILURE);
            }
            if(sigaddset(&set, SIGUSR2)){ /* Añadimos la señal SIGUSR2 al conjunto */
                printf("Error incluyendo la señal SIGUSR2\n"); /* Error */
                exit(EXIT_FAILURE);
            }
            if(sigaddset(&set, SIGALRM)){ /* Añadimos la señal SIGALRM al conjunto */
                printf("Error incluyendo la señal SIGALRM\n"); /* Error */
                exit(EXIT_FAILURE);
            }
            
            if(sigprocmask(SIG_BLOCK, &set, &oset)){ /* Activamos la nueva máscara */
                printf("Error bloqueando el set de señales\n"); /* Error */
                exit(EXIT_FAILURE);
            }
            
            
            for (counter = 0; counter < NUM; counter++){ /* Trabajo */
                printf("%d\n", counter);
                sleep(1);
            }
            
            
            if(sigdelset(&set, SIGUSR2)){ /* Eliminamos la señal SIGUSR2 al conjunto */
                printf("Error al desbloquear la señal SIGUSR1\n"); /* Error */
                exit(EXIT_FAILURE);
            }
            
            if(sigprocmask(SIG_UNBLOCK, &set, &oset)){ /* Eliminamos la señal SIGALRM al conjunto */
                printf("Error bloqueando el set de señales\n"); /* Error */
                exit(EXIT_FAILURE);
            }
            
            sleep(3);
        }
    }
    wait(NULL);
    return EXIT_SUCCESS;
}

