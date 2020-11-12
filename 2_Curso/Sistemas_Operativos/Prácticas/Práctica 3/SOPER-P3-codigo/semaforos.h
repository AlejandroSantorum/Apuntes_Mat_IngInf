/**
* @brief Utilidades de manejo de semaforos
*
* Este modulo contiene los prototipos de las funciones de manejo de
* semaforos.
* @file semaforos.h
* @author Alejandro Santorum & David Cabornero (G2202-Pareja7)
* @version 1.0
* @date 01-04-2018
*/

#ifndef SEMAFOROS_H
#define SEMAFOROS_H

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
#include <sys/shm.h>

#define ERROR -1 /*!< Constante con significado de operacion erronea */
#define OK 0    /*!< Constante con significado de operacion exitosa*/


/**
* @brief funcion inicializadora de semaforos.
* Su funcionalidad es inicializar los semaforos indicados.
*
* @param semid - identificador del semaforo
* @param array - valores iniciales
* @return OK si todo fue correcto, ERROR en caso de error.
*/
int Inicializar_Semaforo(int semid, unsigned short *array);


/**
* @brief funcion que borra semaforos.
* Su funcionalidad es borrar el semaforo indicado.
*
* @param semid - identificador del semaforo
* @return OK si todo fue correcto, ERROR en caso de error.
*/
int Borrar_Semaforo(int semid);


/**
* @brief funcion creadora de semaforos.
* Su funcionalidad es crear un semaforo con la clave y tamaño indicados.
*
* @param key - clave precompartida del semaforo
* @param size - tamanio del semaforo.
* @param semid - entero pasado por referencia para alojar el semid del semaforo creado
* @return int *semid - identificador del semaforo. Int ERROR en caso de error, 1 si el semaforo ya existia, 0 en caso de exito.
*/
int Crear_Semaforo(key_t key, int size, int *semid);


/**
* @brief funcion que decrementa un semaforo.
* Su funcionalidad es bajar o decrementar el semaforo indicado.
*
* @param id - identificador del semaforo
* @param num_sem - semaforo dentro del array
* @param undo - flag de modo persistente pese a finalizacion abrupta
* @return OK si todo fue correcto, ERROR en caso de error.
*/
int Down_Semaforo(int id, int num_sem, int undo);


/**
* @brief funcion que decrementa varios semaforos.
* Su funcionalidad es bajar o decrementar todos los semaforos indicados.
*
* @param id - identificador del semaforo
* @param size - tamanio del array de ids de los semaforos involucrados(active)
* @param undo - flag de modo persistente pese a finalizacion abrupta
* @param active: Semaforos involucrados.
* @return OK si todo fue correcto, ERROR en caso de error.
*/
int DownMultiple_Semaforo(int id, int size, int undo, int *active);


/**
* @brief funcion que incrementa un semaforo.
* Su funcionalidad es subir o incrementar el semaforo indicado.
*
* @param id - identificador del semaforo
* @param num_sem - semaforo dentro del array
* @param undo - flag de modo persistente pese a finalizacion abrupta
* @return OK si todo fue correcto, ERROR en caso de error.
*/
int Up_Semaforo(int id, int num_sem, int undo);


/**
* @brief funcion que incrementa varios semaforos.
* Su funcionalidad es subir o incrementar todos los semaforos indicados.
*
* @param id - identificador del semaforo
* @param size - tamanio del array de ids de los semaforos involucrados(active)
* @param undo - flag de modo persistente pese a finalizacion abrupta
* @param active: Semaforos involucrados.
* @return OK si todo fue correcto, ERROR en caso de error.
*/
int UpMultiple_Semaforo(int id, int size, int undo, int *active);

#endif /** SEMAFOROS_H */
