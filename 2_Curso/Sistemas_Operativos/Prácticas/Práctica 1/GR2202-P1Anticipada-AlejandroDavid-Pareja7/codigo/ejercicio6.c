#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#define LEN 80

typedef struct{
  char cad[LEN];
  int n;
}Estruct;


int main(){
  Estruct *est=NULL;
  int pid;

  est = (Estruct *) malloc(sizeof(Estruct));
  if(!est){
    printf("%s\n", strerror(errno));
    return EXIT_FAILURE;
  }

  if(strcpy(est->cad, "TEXTO GUARDADO ANTES DEL FORK\n")==NULL){ /* Guardamos esto para ver que se imprime */
    printf("%s\n", strerror(errno));                        /* en el caso en que solo hayamos modifcado */
    return EXIT_FAILURE;                                    /* la cadena en el proceso hijo */
  }

  pid = fork();

  if(!pid){
    printf("Introduzca un nombre de maximo %d caracteres: ", LEN-1);
    fgets(est->cad, LEN-1, stdin);  /* Esto se encarga de solo guardar los 79 primeros caracteres + \0
                                       en el caso que el usuario no haya seguido lo especificado */
  }

  wait(NULL);

  printf("%s", est->cad); /* Esta intrucción se realiza tanto en el hijo como en el padre */

  free(est); /* Liberamos memoria en ambos */

  return 0;
}
