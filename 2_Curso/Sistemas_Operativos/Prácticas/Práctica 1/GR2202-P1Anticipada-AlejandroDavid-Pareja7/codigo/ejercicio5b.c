#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define NUM_PROC 6

int main (void){
  int pid;
  int i;

  for (i=0; i <= NUM_PROC; i++){
    if (i % 2 != 0) {
      if ((pid=fork()) <0 ){
        printf("Error haciendo fork\n");
        exit(EXIT_FAILURE);
      }
      else if(pid == 0){
        printf ("PADRE %d \n",getppid());
        printf("HIJO  %d \n",getpid());
        break; /* Si pid = 0 es que es un hijo por lo que no hace más forks */
      }
    }
  }

  while(wait(NULL)>=0); /* Devolverá -1 cuando no tenga hijos */
  exit(EXIT_SUCCESS);
}
