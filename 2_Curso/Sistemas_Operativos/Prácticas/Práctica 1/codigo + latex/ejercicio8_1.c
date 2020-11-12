/**
* @brief Ejercicio8_1
* Ejecución de varios programas desde el primero
* pasado como argumento de entrada hasta el ultimo
* @file ejercicio8_1.c
* @author Alejandro Santorum & David Cabornero (G2202)
* @version 1.0
* @date 02-03-2018
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#define PATH_LEN 100 /*!< Longitud cadenas de caracteres */

int main(int argc, char **argv){
  int pid, flag, i, j, k;
  char **argum=NULL;
  char path[PATH_LEN];

  /* Control de errores argumentos de entrada */
  if(argc < 3){
    printf("Error. Parametros de entrada insuficientes.\n");
    printf("Introduzca nombres de los programas ejecutables y despues\n");
    printf("la indicacion de la funcion exec que desea utilizar(-l, -lp, -v, -vp).\n");
    exit(EXIT_FAILURE);
  }

  if(strcmp(argv[argc-1], "-l") && strcmp(argv[argc-1], "-lp") && strcmp(argv[argc-1], "-v") && strcmp(argv[argc-1], "-vp")){
    printf("Error. Indicacion de la funcion exec a utilizar desconocida.\n");
    printf("Indicacion introducida: %s\n", argv[argc-1]);
    exit(EXIT_FAILURE);
  }
  /* ------------------------------------------------------------------------------------------ */

  if(argc > 3){ /* Hay dos o más programas aún por ejecutarse */
    if((pid=fork()) <0 ){
      printf("Error al emplear fork\n");
      exit(EXIT_FAILURE);
    }
    flag=1;

    if(!pid){ /* En el proceso hijo llamamos de nuevo al programa principal con argc-1 argumentos */
      argum = (char **) malloc(argc * sizeof(char *));
      if(argum==NULL){ /* Error reservando memoria */
        printf("%s\n", strerror(errno));
        exit(EXIT_FAILURE);
      }

      if((argum[0] = strcpy(((char *) malloc((strlen(argv[0])+1)*sizeof(char))), argv[0])) == NULL){ /*nombre programa*/
        free(argum);
        printf("Error de memoria.\n");
        exit(EXIT_FAILURE);
      }
      for(i=2, j=1; i<argc; i++, j++){
        if((argum[j] = strcpy(((char *) malloc((strlen(argv[i])+1)*sizeof(char))), argv[i])) == NULL){
          /* Error reservando memoria */
          for(k=0;- k<j; k++){ /* Liberando todo lo reservado */
            free(argum[k]);
          }
          free(argum);
          printf("Error de memoria.\n");
          exit(EXIT_FAILURE);
        }
      }
      argum[argc-1] = NULL;

      execvp(argv[0], argum);
      perror("Fallo en exec llamando de nuevo al programa padre.\n");
      exit(EXIT_FAILURE);
    }
  }
  /* --------------------------------------------------------------------------- */
  if(flag) wait(NULL);

  /* A continuacion, ejecutamos el programa pasado como parametro de entrada */
  if(!strcmp(argv[argc-1], "-l")){
      sprintf(path, "/bin/bash");
      execl(path, "bash", "-c", argv[1], NULL);
  }else if(!strcmp(argv[argc-1], "-lp")){
      execlp(argv[1], argv[1], NULL);
  }else if(!strcmp(argv[argc-1], "-v")){
      sprintf(path, "/bin/bash");

      argum = (char **) malloc(4 * sizeof(char *));
      if(argum==NULL){ /* Error reservando memoria */
        printf("Error de memoria.\n");
        exit(EXIT_FAILURE);
      }
      argum[0] = strcpy(((char *) malloc((strlen("bash")+1)*sizeof(char))) , "bash");
      if(argum[0]==NULL){ /* Error reservando memoria */
        free(argum);
        printf("Error de memoria.\n");
        exit(EXIT_FAILURE);
      }
      argum[1] = strcpy(((char *) malloc((strlen("-c")+1)*sizeof(char))) , "-c");
      if(argum[1]==NULL){ /* Error reservando memoria */
        free(argum[0]);
        free(argum);
        printf("Error de memoria.\n");
        exit(EXIT_FAILURE);
      }
      argum[2] = strcpy(((char *) malloc(strlen(argv[1])*sizeof(char))) , argv[1]);
      if(argum[2]==NULL){ /* Error reservando memoria */
        free(argum[0]);
        free(argum[1]);
        free(argum);
        printf("Error de memoria.\n");
        exit(EXIT_FAILURE);
      }
      argum[3] = NULL;

      execv(path, argum);
  }else if(!strcmp(argv[argc-1], "-vp")){
      argum = (char **) malloc(2 * sizeof(char *));
      if(argum==NULL){ /* Error reservando memoria */
        printf("Error de memoria.\n");
        exit(EXIT_FAILURE);
      }
      argum[0] = strcpy(((char *) malloc(strlen(argv[1])*sizeof(char))) , argv[1]);
      if(argum[0]==NULL){ /* Error reservando memoria */
        free(argum);
        printf("Error de memoria.\n");
        exit(EXIT_FAILURE);
      }
      argum[1] = NULL;

      execvp(argv[1], argum);
  }else{
      printf("Error inverosimil, esta comprobacion ya había sido superada anteriormente.\n");
      exit(EXIT_FAILURE);
  }

  printf("\nNo se ha ejecutado el programa %s utilizando %s\n\n", argv[1], argv[argc-1]);

  exit(EXIT_SUCCESS);
}
