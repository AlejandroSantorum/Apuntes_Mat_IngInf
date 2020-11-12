#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define NUM_PROC 6

int main (void){
  int pid;
  int i;
  int praiz;

  praiz = getpid();

  for (i=0; i <= NUM_PROC; i++){
    if (i % 2 == 0) {
      if ((pid=fork()) <0 ){
        printf("Error al emplear fork\n");
        exit(EXIT_FAILURE);
      }
      else if(getppid()==1 && getpid()!=praiz){
        printf("Proceso huerfano %d\n", getpid());
      }
      else if(pid == 0){
        printf ("PADRE %d\n", getppid());
        printf("HIJO  %d\n", getpid());
      }
    }
  }
  exit(EXIT_SUCCESS);
}
