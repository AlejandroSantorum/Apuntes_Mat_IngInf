/**
* @brief Ejercicio5a
* Modificación del ejercicio4b para que cada proceso
* tengo un único hijo que sea esperado por su padre.
* @file ejercicio5a.c
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
      }else if(pid == 0){ /* Si es hijo, imprime PID y PPID */
          printf ("PADRE %d \n",getppid());
          printf("HIJO  %d \n",getpid());
      }else{
          break; /* pid > 0 quiere decir que no está funcionando como hijo */
      }
    }
  }

  wait(NULL); /* Esperando por un hijo, en este programa, solo uno posible */
  exit(EXIT_SUCCESS);
}
