/**
* @brief Ejercicio6b
* Toma de contacto con la funcion sigfillset()
* @file ejercicio6b.c
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


/**
* @brief nuevo manejador de la señal SIGTERM.
* Su funcionalidad es simplemente imprimir el PID y un mensaje.
*
* @param sig - la señal que utilizará este manejador cuando sea llamada
* @return void.
*/
void handler_SIGTERM(int sig);


int main(int argc, char *argv[]){
    int pid, counter;
    sigset_t set, oset;
    void handler_SIGTERM();

    if((pid = fork()) < 0){
        printf("Fork function Error: %s", strerror(errno)); /* Error */
        exit(EXIT_FAILURE);
    }
    if (!pid){ /* Zona acción proceso hijo */
        if(signal(SIGTERM, handler_SIGTERM)==SIG_ERR){ /* Armamos nuevo manejador de la señal SIGTERM */
            printf("Error estableciendo el nuevo manejador de SIGTERM.\n"); /* Error */
            exit(EXIT_FAILURE);
        }

        if(sigfillset(&set)){  /* Creamos un conjunto de señales con todas las señales */
            printf("Error en sigfillset(&set)"); /* Error */
            exit(EXIT_FAILURE);
        }
        if(sigdelset(&set, SIGTERM)){ /* Eliminamos del conjunto la señal que NO queremos ignorar: SIGTERM */
            printf("Error en sigdelset(&set)"); /* Error */
            exit(EXIT_FAILURE);
        }

        if(sigprocmask(SIG_BLOCK, &set, &oset)){ /* Ignoramos todas las señales de esta máscara: todas menos SIGTERM */
                printf("Error bloqueando el set de señales\n"); /* Error */
                exit(EXIT_FAILURE);
        }
        while(1){ /* Trabajo */
            for (counter = 0; counter < NUM; counter++){
                printf("%d\n", counter);
                sleep(1);
            }
            sleep(3);
        }

    }
    /* Zona acción proceso padre*/
    else{
        sleep(40); /* Esperamos 40 segundos */
        kill(pid, SIGTERM); /* Enviamos señal al hijo */
    }
    wait(NULL);
    exit(EXIT_SUCCESS);
}


void handler_SIGTERM(int sig){
    printf("Soy %d y he recibido la señal SIGTERM\n", getpid());
    exit(EXIT_SUCCESS);
}
