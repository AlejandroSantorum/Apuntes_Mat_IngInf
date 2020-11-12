/**
* @brief Ejercicio8_2
* Ejecución de varios programas desde el ultimo
* pasado como argumento de entrada hasta el primero
* @file ejercicio8_2.c
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
  int pid, i, j, flag=0;
  char **arg=NULL;
  char path[PATH_LEN];

  /* Control de errores argumentos de entrada */
  if(argc < 3){
    printf("Error. Parámetros de entrada insuficientes.\n");
    printf("Introduzca nombres de los programas ejecutables y despues\n");
    printf("la indicación de la funcion exec que desea utilizar(-l, -lp, -v, -vp).\n");
    exit(EXIT_FAILURE);
  }

  if(strcmp(argv[argc-1], "-l") && strcmp(argv[argc-1], "-lp") && strcmp(argv[argc-1], "-v") && strcmp(argv[argc-1], "-vp")){
    printf("Error. Indicación de la funcion exec a utilizar desconocida.\n");
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
      arg = (char **) malloc((argc) * sizeof(char *));
      if(!arg){ /* Error reservando memoria */
        printf("%s\n", strerror(errno));
        exit(EXIT_FAILURE);
      }

      for(i=0; i<(argc-2); i++){
        arg[i] = strcpy(((char *) malloc(strlen(argv[i])*sizeof(char))) , argv[i]);
        if(!arg[i]){ /* Error reservando memoria */
          for(j=0; j<i; j++){ /* Liberando todo lo reservado */
            free(arg[j]);
          }
          free(arg);
          printf("%s\n", strerror(errno));
          exit(EXIT_FAILURE);
        }
      }
      arg[argc-2] = strcpy(((char *) malloc(strlen(argv[argc-1])*sizeof(char))) , argv[argc-1]);
      arg[argc-1] = NULL;

      execvp(argv[0], arg);
      perror("Fallo en exec llamando de nuevo al programa padre.\n");
      exit(EXIT_FAILURE);
    }
  }
  /* --------------------------------------------------------------------------- */
  if(flag) wait(NULL);

  /* A continuacion, ejecutamos el programa pasado como parametro de entrada */
  if(strcmp(argv[argc-1], "-l")){
    if(!(memset(path, '\0', PATH_LEN))){
      printf("%s\n", strerror(errno)); /* Error de memoria */
      exit(EXIT_FAILURE);
    }
    strcpy(path, "/bin/");
    if(path==NULL){ /* Error reservando memoria */
      printf("%s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
    strcat(path, argv[argc-2]);
    if(path==NULL){ /* Error reservando memoria */
      printf("%s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
    execl(path, argv[argc-2], NULL);
  } else if(strcmp(argv[argc-1], "-lp")){
    	execlp(argv[argc-2], argv[argc-2], NULL);
  } else if(strcmp(argv[argc-1], "-v")){
    	arg = (char **) malloc(2 * sizeof(char *));
    	if(!arg){ /* Error reservando memoria */
      	printf("%s\n", strerror(errno));
      	exit(EXIT_FAILURE);
    }
    arg[0] = strcpy(((char *) malloc(strlen(argv[argc-2])*sizeof(char))) , argv[argc-2]);
    if(!arg[0]){ /* Error reservando memoria */
      printf("%s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
    arg[1] = NULL;

    if(!(memset(path, '\0', PATH_LEN))){
      printf("%s\n", strerror(errno)); /* Error de memoria */
      exit(EXIT_FAILURE);
    }
    strcpy(path, "/bin/");
    if(path==NULL){ /* Eror reservando memoria */
      printf("%s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
    strcat(path, argv[argc-2]);
    if(path==NULL){ /* Eror reservando memoria */
      printf("%s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }

    execv(path, arg);
  } else if(strcmp(argv[argc-1], "-vp")){
    	arg = (char **) malloc(2 * sizeof(char *));
    	if(!arg){ /* Error reservando memoria */
      	printf("%s\n", strerror(errno));
      	exit(EXIT_FAILURE);
    	}
    	arg[0] = strcpy(((char *) malloc(strlen(argv[argc-2])*sizeof(char))) , argv[argc-2]);
    	if(!arg[0]){ /* Error reservando memoria */
      	printf("%s\n", strerror(errno));
      	exit(EXIT_FAILURE);
    		}
    	arg[1] = NULL;

    	execvp(argv[argc-2], arg);
	} else{
    	printf("Error inverosímil, esta comprobación ya había sido superada anteriormente.\n");
    	exit(EXIT_FAILURE);
  }

  printf("No se ha ejecutado el programa %s\n", argv[argc-2]);

  exit(EXIT_SUCCESS);
}
