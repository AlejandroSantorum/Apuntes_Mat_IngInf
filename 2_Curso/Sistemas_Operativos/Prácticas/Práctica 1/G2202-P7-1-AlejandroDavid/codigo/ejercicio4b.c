/**
* @brief Ejercicio4b
* Modificación del código dado para que cada HIJO
* imprima su PID y el PID de su padre. Se diferencia con el
* ejercicio anterior por la presencia de wait().
* @file ejercicio4b.c
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
  int proot;

  proot = getpid();

  for (i=0; i <= PROC_NUM; i++){
    if (i % 2 == 0) {
      if ((pid=fork()) <0 ){ /* Fork + comprobación de errores */
        printf("Error al emplear fork\n");
        exit(EXIT_FAILURE);
      }

      if(getppid()==1 && getpid()!=proot){ /* Comprobación de proceso huérfano */
          printf("Proceso huerfano %d\n", getpid());
      } else if(pid == 0){ /* Si es hijo, imprime PID y PPID */
          printf ("PADRE %d\n", getppid());
          printf("HIJO  %d\n", getpid());
      }
    }
  }

  wait(NULL);
  exit(EXIT_SUCCESS);
}
