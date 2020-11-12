/**
* @brief Utilidades de manejo de semaforos
*
* Este modulo contiene la implementacion de las funciones de manejo de
* semaforos.
* @file semaforos.c
* @author Alejandro Santorum & David Cabornero (G2202-Pareja7)
* @version 1.0
* @date 01-04-2018
*/

#include "semaforos.h"


int Inicializar_Semaforo(int semid, unsigned short *array){
  union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
  }arg;
  arg.array = array;

  if(semctl(semid, 0, SETALL, arg)==-1){
    printf("Error inicializando el semaforo %d\n",semid);
    return ERROR;
  }

  return OK;
}



int Borrar_Semaforo(int semid){
  if(semctl(semid, 0, IPC_RMID, 0)==-1){
    printf("Error eliminando el semaforo %d\n", semid);
    return ERROR;
  }
  return OK;
}



int Crear_Semaforo(key_t key, int size, int *semid){
  int i;
  unsigned short *array=NULL;

  *semid = semget(key, size, IPC_CREAT|IPC_EXCL|0666);
  if((*semid == -1) && (errno == EEXIST)){
    //printf("El semaforo que se intenta crear ya existia\n");
    *semid = semget(key,size,SHM_R|SHM_W);
    return 1;
  }
  if(*semid == -1){
    printf("Error intentando crear semaforos con semget\n");
    return ERROR;
  }

  array = (unsigned short *) malloc(size * sizeof(unsigned short));
  if(array==NULL){
    printf("Error: reservando memoria para el unsigned short array en Crear_Semaforo\n");
    return ERROR;
  }

  for(i=0; i<size; i++){ /* Array con todo a cero */
    array[i] = 0;
  }

  if(Inicializar_Semaforo(*semid, array)==ERROR){ /* Inicializamos sem de tamaño size a cero */
    printf("Error inicializando los semaforos al crearlos\n");
    free(array);
    return ERROR;
  }
  free(array);
  return 0;
}



int Down_Semaforo(int id, int num_sem, int undo){
  struct sembuf sops;

  sops.sem_num = num_sem;
  sops.sem_op = -1;
  sops.sem_flg = undo;

  if(semop(id, &sops, 1)==-1){
    //printf("Error bajando el semaforo de id %d: %s\n", id, strerror(errno));
    return ERROR;
  }

  return OK;
}



int DownMultiple_Semaforo(int id, int size, int undo, int *active){
   struct sembuf sops[size];

   for(int i=0; i < size; i++){
     sops[i].sem_num = active[i];
     sops[i].sem_op = -1;
     sops[i].sem_flg = undo;
     sops[i].sem_flg |= SEM_UNDO;
   }

   if(semop(id, sops, size)==-1){
     printf("Error bajando el semaforo de id %d\n", id);
     return ERROR;
   }

   return OK;
}



int Up_Semaforo(int id, int num_sem, int undo){
  struct sembuf sops;

  sops.sem_num = num_sem;
  sops.sem_op = 1;
  sops.sem_flg = undo;

  if(semop(id, &sops, 1)==-1){
    //printf("Error subiendo el semaforo de id %d: %s\n", id, strerror(errno));
    return ERROR;
  }

  return OK;
}



int UpMultiple_Semaforo(int id, int size, int undo, int *active){
  struct sembuf sops[size];

  for(int i=0; i < size; i++){
    sops[i].sem_num = active[i];
    sops[i].sem_op = 1;
    sops[i].sem_flg = undo;
    sops[i].sem_flg |= SEM_UNDO;
  }

  if(semop(id, sops, size)==-1){
    printf("Error subiendo el semaforo de id %d\n", id);
    return ERROR;
  }

  return OK;
}
