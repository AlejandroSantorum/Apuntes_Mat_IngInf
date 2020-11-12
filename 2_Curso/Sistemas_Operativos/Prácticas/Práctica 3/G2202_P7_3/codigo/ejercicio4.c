/**
* @brief Ejercicio4
*
* Este ejercicio tiene un fin educativo con el problema de escritores-lectores
* @file ejercicio4.c
* @author Alejandro Santorum & David Cabornero (G2202-Pareja7)
* @version 1.0
* @date 16-04-2018
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
#include <sys/sem.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define N_THREADS 2 /*!< Numero de hilos */
#define READER 0 /*!< Identificador del hilo lector */
#define WRITER 1 /*!< Identificador del hilo escritor */


/**
* @brief devuelve un numero entero aleatorio en el intervalo (limites incluidos)
*
* @param inf - limite inferior intervalo
* @param sup - limite superior intervalo
* @return entero aleatorio en el intervalo. Corta ejecucion en caso de error.
*/
int aleat_num(int inf, int sup);

/**
* @brief funcion del hilo escritor: escribe en un fichero numeros aleatorios
*
* @param args - puntero a la estructura que sera pasada como parametro al hilo
* @return void* - NULL
*/
void* write_file(void *args);

/**
* @brief funcion del hilo lector: lee de un fichero numeros aleatorios y los muestra
*
* @param args - puntero a la estructura que sera pasada como parametro al hilo
* @return void* - NULL
*/
void* read_file(void *args);


int main(){
   pthread_t thr[N_THREADS];
   int fd;

   /* Creacion hilo escritor */
   if(pthread_create(&thr[WRITER], NULL, write_file, NULL) != 0){
      perror("Error en la creación del hilo escritor\n");
      exit(EXIT_FAILURE);
   }

   /* Espera por el hilo escritor */
   if(pthread_join(thr[WRITER], NULL) != 0){
      perror("Error en la espera por el hilo escritor\n");
      exit(EXIT_FAILURE);
   }

   /* Conseguimos el file descrriptor, que se lo pasamos al segundo hilo, lector. */
   fd = open("ejercicio4.txt", O_RDONLY, 0644);
   if(fd < 0){
      perror("Error abriendo el fichero con open()");
      exit(EXIT_FAILURE);
   }

   /* Creamos hilo lector */
   if(pthread_create(&thr[READER], NULL, read_file, &fd) != 0){
      perror("Error en la creación del hilo lector\n");
      exit(EXIT_FAILURE);
   }

   /* Esperamos por el hilo lector */
   if(pthread_join(thr[READER], NULL) != 0){
      perror("Error en la espera por el hilo lector\n");
      exit(EXIT_FAILURE);
   }

   close(fd);

   exit(EXIT_SUCCESS);
}

void* write_file(void *args){
   FILE *f=NULL;
   int i, n_nums;

   f = (FILE *) fopen("ejercicio4.txt", "w");
   if(f==NULL){
      perror("Error abriendo el fichero para escribir\n");
      exit(EXIT_FAILURE);
   }

   n_nums = aleat_num(1000, 2000);

   for(i=0; i<n_nums-1; i++){
      fprintf(f, "%d,", aleat_num(100, 1000));
   }
   /* el último sin coma */
   fprintf(f, "%d", aleat_num(100, 1000));

   fclose(f);

   return NULL;
}


void* read_file(void *args){
   int fildes = *(int*) args;
   struct stat s;
   int size, i;
   char *f;

   if(fstat(fildes, &s) == -1){
      perror("Error obteniendo el tamaño del fichero\n");
      exit(EXIT_FAILURE);
   }

   size = s.st_size;

   f = (char *) mmap(0, size, PROT_READ, MAP_PRIVATE, fildes, 0);
   if(f == MAP_FAILED){
      perror("Error en la funcion mmap()\n");
      exit(EXIT_SUCCESS);
   }


   for(i=0; i<size; i++){
      /* Mostramos por pantalla los numeros, cambiando las comas por espacios */
      if(f[i]==','){
         printf(" ");
      }else{
         printf("%c", f[i]);
      }
   }
   return NULL;
}



int aleat_num(int inf, int sup){
    int result = 0;

    if(inf == sup){
        return sup;
    }

    else if (inf > sup){
        printf("ERROR: Límite inferior mayor que el límite superior.\n");
        exit(EXIT_FAILURE);
    }

    result = (inf + ((int) ((((double)(sup-inf+1)) * rand())/(RAND_MAX + 1.0))));

    return result;
}
