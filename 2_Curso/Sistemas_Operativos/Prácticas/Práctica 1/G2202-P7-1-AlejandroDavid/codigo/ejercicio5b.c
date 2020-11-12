/**
* @brief Ejercicio5b
* Modificación del ejercicio4b para que un proceso
* tenga un conjunto de hijos que serán esperados por el padre.
* @file ejercicio5b.c
* @author Alejandro Santorum & David Cabornero (G2202)
* @version 1.0
* @date 02-03-2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define PROC_NUM 6 /*!< Número de procesos */

int main (void){
  int pid;
  int i;

  for (i=0; i <= PROC_NUM; i++){
    if (i % 2 != 0) {
      if ((pid=fork()) <0 ){ /* Fork + comprobación de errores */
        	printf("Error haciendo fork\n");
        	exit(EXIT_FAILURE);
      } else if(pid == 0){ /* Si es hijo, imprime PID y PPID */
        	printf ("PADRE %d \n",getppid());
        	printf("HIJO  %d \n",getpid());
        	break; /* Si pid = 0 es que es un hijo por lo que no hace más forks */
      }
    }
  }

  while(wait(NULL)>=0); /* Devolverá -1 cuando no tenga más hijos */
  exit(EXIT_SUCCESS);
}
