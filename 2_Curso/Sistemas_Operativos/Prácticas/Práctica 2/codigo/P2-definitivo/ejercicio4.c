/**
* @brief Ejercicio4
* Manejo de señales entre procesos hijos y padre
* @file ejercicio4.c
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

#define N_PRINT 10 /*!< Número de impresiones por pantalla de cada hijo */


/**
* @brief evalua si un argumento de entrada es verdaderamente un entero
*
* @param input - contiene la cadena de caracteres sospechosa de ser un entero
* @return 1 si es un entero, 0 en caso contrario.
*/
int is_valid_integer(char *input);


/**
* @brief nuevo manejador de la señal SIGUSR1.
* Su funcionalidad es simplemente no hacer nada.
*
* @param sig - la señal que utilizará este manejador cuando sea llamada
* @return void.
*/
void handler_SIGUSR1(int sig);


int main(int argc, char *argv[]){
    int pid=0, last_pid = -1, i, j, childs;
    int pfather;
    void handler_SIGUSR1();

    if(argc != 2){ /* Error de parámetros de entrada */
        printf("ERROR. Parámetros de entrada incorrectos.\n");
        printf("Por favor, introduzca el nombre del programa seguido\n");
        printf("del numero de procesos hijos que se quiere generar.\n");
        exit(EXIT_FAILURE);
    }

    if(!is_valid_integer(argv[1])) exit(EXIT_FAILURE); /* No se ha introducido un entero */

    childs = atoi(argv[1]);

    pfather = getpid(); /* Guardamos el PID del proc. padre para el futuro */

    /* Asignamos un nuevo manejador a la señal SIGUSR1 */
    if(signal(SIGUSR1, handler_SIGUSR1)==SIG_ERR){
        printf("Error estableciendo el nuevo manejador de SIGUSR1.\n"); /* Error */
        exit(EXIT_FAILURE);
    }

    for(i=0; i<childs; i++){
        if((pid = fork())<0){
            printf("Fork function Error: %s", strerror(errno));
            exit(EXIT_FAILURE);
        }

        /* Zona de acción de los procesos hijos */
        if(!pid){
            if(last_pid != -1){
                kill(last_pid, SIGTERM); /* Enviamos una señal de finalización al proceso hijo anterior */
            }

            for(j = 0; j < N_PRINT; j++){
                printf("Soy %d y estoy trabajando\n", getpid());
                fflush(stdout);
                sleep(1);
            }
            sleep(10);
            kill(pfather, SIGUSR1); /* Enviamos señal al proceso padre */
            while(1){
                /* Se sigue imprimiento mientras el proceso padre
                 * no recoja la señal mandada y responda a ella.*/
                printf("Soy %d y estoy trabajando despues de enviar la señal\n", getpid());
                fflush(stdout);
                sleep(1);
            }
        }
        /* Zona de acción del proceso padre */
        else{
            pause(); /* Espera a una señal */
            last_pid = pid;
        }
    }

    kill(last_pid,SIGTERM); /* Una vez finalizado el bucle, enviamos
                             * señal de finalización al ultimo proceso hijo */

    while(wait(NULL)<0); /* Esperamos en el hipotético caso que los hijos aún no
                          * hayan respondido a la señal de finalización enviada */

    return(EXIT_SUCCESS);
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
         return 0;
      }
    }
    if(!atoi(input)){
      printf("ERROR. No se admite cero como entero de entrada.\n");
      return 0;
   }
   return 1;
}


void handler_SIGUSR1(int sig){
    return;
}
