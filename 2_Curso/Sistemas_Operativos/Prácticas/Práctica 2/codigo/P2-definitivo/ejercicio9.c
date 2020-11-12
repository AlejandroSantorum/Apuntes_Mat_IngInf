/**
* @brief Ejercicio9
*
* Este ejercicio comprueba la librería de semaforos mientras ayuda didacticamente
* @file semaforos.c
* @author Alejandro Santorum & David Cabornero (G2202-Pareja7)
* @version 1.0
* @date 06-04-2018
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
#include <time.h>
#include "semaforos.h"


#define MIN_KEY 100 /*!< Limite inferior para la eleccion de la key de semaforos */
#define MAX_KEY 99999 /*!< Limite superior para la eleccion de la key de semaforos */
#define SIZE 64 /*!< Tamaño maximo nombres de ficheros */
#define NUM_OPERATIONS 50 /*!< Número de clientes por caja */
#define MAX_PRICE 300 /*!< Precio maximo de compra (aleatoria) */
#define MAX_AMOUNT 1000 /*!< Cantidad maxima de dinero en caja antes de aviso de retirada */
#define REMOVE 900 /*!< Cantidad de dinero retirada despues del aviso de una caja */
#define BUFFER_SIZE 128 /*!< Tamaño del buffer de lectura de ficheros */

int flag = 0; /*!< Constante global auxiliar para envitar fallos de coordinacion */


/**
* @brief evalua si un argumento de entrada es verdaderamente un entero
*
* @param input - contiene la cadena de caracteres sospechosa de ser un entero
* @return 1 si es un entero, 0 en caso contrario.
*/
int is_valid_integer(char *input);

/**
* @brief devuelve el fichero de clientes asignado a una caja
*
* @param num - identificador de la caja o cajero
* @return cadena de caracteres del nombre del fichero de clientes, NULL en caso de error.
*/
char *nombre_transaccion(int num);

/**
* @brief devuelve el fichero caja de un cajero
*
* @param num - identificador del cajero
* @return cadena de caracteres del nombre del fichero de caja, NULL en caso de error.
*/
char *nombre_cajero(int num);

/**
* @brief devuelve un numero entero aleatorio en el intervalo (limites incluidos)
*
* @param inf - limite inferior intervalo
* @param sup - limite superior intervalo
* @return entero aleatorio en el intervalo. Corta ejecucion en caso de error.
*/
int aleat_num(int inf, int sup);

/**
* @brief comprueba que la suma total es la suma de las compras de los clientes
*
* @param num_cash - numero de cajeros
* @param total - suma calculada por el programa
* @return OK en caso de que la suma sea correcta. ERROR en caso de error.
*/
int final_check(int num_cash, int total);

int main(int argc, char **argv){
    int num_cash, key, check_sem1, semid, param_key, max_active_wait;
    unsigned short *sem_array;
    char buff[BUFFER_SIZE], status[BUFFER_SIZE];
    char *name, *fcash;
    FILE *in, *faux;
    int i, j, k, pid, price, amount, id, active_wait=0, total=0, n_fin = 0;
    int debug_father=0, debug_childs=0;
    sigset_t set, oset;
    void handler_SIGUSR1();


    if(argc != 2){ /* Error de parámetros de entrada */
        printf("ERROR Parametros de Entrada:\n");
        printf("Por favor, introduzca después del nombre el numero de cajeros\n");
        exit(EXIT_FAILURE);
    }
    if(!is_valid_integer(argv[1])) exit(EXIT_FAILURE); /* No se ha introducido un entero */

    srand(time(NULL)); /* Semilla numeros aleatorios */

    num_cash = atoi(argv[1]); /* Numero de cajeros */
    max_active_wait = 2*num_cash; /* La espera activa es directamente proporcional al numero de cajeros */

    /* --------------- CREACION + INICIALIZACION DE SEMAFOROS -------------*/

    param_key = aleat_num(MIN_KEY, MAX_KEY);
    key = ftok("/bin/bash", param_key); /* Obtenemos la clave para el/los semaforo/s. */
    /*Inicializacion de semaforos*/
    check_sem1 = Crear_Semaforo(key, num_cash+1, &semid);
    if(check_sem1 == ERROR){ /* Error */
        printf("Error en la creacion del conjunto de semaforos\n");
        exit(EXIT_FAILURE);
    }

    sem_array = (unsigned short *) malloc((num_cash+1)*sizeof(unsigned short));
    if(!sem_array){ /* Error */
        printf("Error reservando memoria para el array de ids de semaforos involucrados\n");
        if(Borrar_Semaforo(semid) == ERROR){
           printf("Advertencia: no se han podido eliminar los semaforos despues del error anterior\n");
        }
        exit(EXIT_FAILURE);
    }
    for(i=0; i<=num_cash; i++){
        sem_array[i] = 1;
    }
    /* Inicializamos todos los semaforos a 1 con ayuda del array anterior */
    if(Inicializar_Semaforo(semid, sem_array)==ERROR){ /* Error */
        printf("Error Inicializar_Semaforo poniendo todos los semaforos a 1 al principio del programa\n");
        printf("CONSEJO: Ejecutar de nuevo este programa 'ejercicio9' para resetear la KEY de los semaforos\n");
        printf("Este error puede darse debido a ejecutarse demasiadas veces un semaforo con la misma key\n");
        printf("Para tratar de evitar esto, este programa escoge la key aleatoriamente entre 100 y 99999 en tiempo de ejecucion\n");
        free(sem_array);
        if(Borrar_Semaforo(semid) == ERROR){
           printf("Advertencia: no se han podido eliminar los semaforos despues del error anterior\n");
        }
        exit(EXIT_FAILURE);
    }
    free(sem_array);


    /* --------------------------- PREPARACION DE LAS SEÑALES --------------------------------- */

    if(sigfillset(&set)){  /* Creamos un conjunto de señales con todas las señales */
        printf("Error en sigfillset(&set)"); /* Error */
        if(Borrar_Semaforo(semid) == ERROR){
           printf("Advertencia: no se han podido eliminar los semaforos despues del error anterior\n");
        }
        exit(EXIT_FAILURE);
    }
    if(sigdelset(&set, SIGUSR1)){ /* Eliminamos del conjunto la señal que NO queremos ignorar: SIGUSR1 */
        printf("Error en sigdelset(&set) intentando eliminar la señal SIGUSR1 del conjunto\n"); /* Error */
        if(Borrar_Semaforo(semid) == ERROR){
           printf("Advertencia: no se han podido eliminar los semaforos despues del error anterior\n");
        }
        exit(EXIT_FAILURE);
    }
    if(sigdelset(&set, SIGINT)){ /* Eliminamos del conjunto la señal que NO queremos ignorar: SIGINT */
        printf("Error en sigdelset(&set) intentando eliminar la señal SIGINT del conjunto\n"); /* Error */
        if(Borrar_Semaforo(semid) == ERROR){
           printf("Advertencia: no se han podido eliminar los semaforos despues del error anterior\n");
        }
        exit(EXIT_FAILURE);
    }
    if(sigprocmask(SIG_BLOCK, &set, &oset)){ /* Ignoramos todas las señales de esta máscara: todas menos SIGINT y SIGUSR1 */
         printf("Error bloqueando el set de señales\n"); /* Error */
         if(Borrar_Semaforo(semid) == ERROR){
            printf("Advertencia: no se han podido eliminar los semaforos despues del error anterior\n");
         }
         exit(EXIT_FAILURE);
    }

    /* Creacion de los ficheros con las 50 transacciones que van a hacer */
    for(i=1; i<=num_cash; i++){
        name = nombre_transaccion(i);
        in = (FILE *) fopen(name, "w");
        if(!in){ /* Error */
            printf("Fallo creando el fichero clientes %d.\n", i);
            free(name);
            if(Borrar_Semaforo(semid) == ERROR){
               printf("Advertencia: no se han podido eliminar los semaforos despues del error anterior\n");
            }
            exit(EXIT_FAILURE);
        }
        fprintf(in, "%d", aleat_num(0,MAX_PRICE)); /* Una iteracion fuera del bucle porque no nos interesa el \n */
        for(j=1; j<NUM_OPERATIONS; j++){
            fprintf(in, "\n%d", aleat_num(0,MAX_PRICE));
        }
        free(name);
        fclose(in);
    }

    /* Creacion del fichero en el que guardaremos la cola de procesos que pide que se le retiren 900 euros*/
    in = (FILE *) fopen("txtfiles/cola.txt", "w");
    if(!in){ /* Error */
        printf("Fallo en la creación del fichero 'cola.txt'.\n");
        if(Borrar_Semaforo(semid) == ERROR){
           printf("Advertencia: no se han podido eliminar los semaforos despues del error anterior\n");
        }
        exit(EXIT_FAILURE);
    }
    fclose(in);

    /* Asignamos un nuevo manejador a la señal SIGUSR1 */
    if(signal(SIGUSR1, handler_SIGUSR1)==SIG_ERR){ /* Error */
        printf("Error estableciendo el nuevo manejador de SIGUSR1.\n"); /* Error */
        if(Borrar_Semaforo(semid) == ERROR){
           printf("Advertencia: no se han podido eliminar los semaforos despues del error anterior\n");
        }
        exit(EXIT_FAILURE);
    }

    /* Creacion de los cajeros como procesos */
    for(i=1; i<=num_cash; i++){
        if((pid = fork())<0){ /* Error */
            printf("Error al crear los cajeros (fork).\n");
            if(Borrar_Semaforo(semid) == ERROR){
               printf("Advertencia: no se han podido eliminar los semaforos despues del error anterior\n");
            }
            exit(EXIT_FAILURE);
        }
        if(pid == 0){ /* Esto nos permite que cada proceso hijo tenga un id = i */
            break;
        }
    }

    /* ------------------ ZONA DE ACTUACION DE PR. HIJOS: Cajeros ----------------- */
    if(pid == 0){
        name = nombre_transaccion(i);
        fcash = nombre_cajero(i);
        /**Inicializamos nuestra caja a 0*/
        in = (FILE *) fopen(fcash, "w");
        if(!in){ /* Error */
            printf("Error intentando abrir el archivo para inicializar la caja %d.\n", i);
            free(name);
            free(fcash);
            if(Borrar_Semaforo(semid) == ERROR){
               printf("Advertencia: no se han podido eliminar los semaforos despues del error anterior\n");
            }
            exit(EXIT_FAILURE);
        }
        fprintf(in,"%d\n", 0);
        fclose(in);

        /* Este bucle percorre las "compras" de los clientes y actualiza las cajas */
        for(j=0; j<NUM_OPERATIONS; j++){
            /**Leemos la operacion que queremos hacer*/
            in = (FILE *) fopen(name, "r");
            if(!in){ /* Error */
                printf("Error intentando abrir el archivo de clientes de la caja %d\n", i);
                free(name);
                free(fcash);
                if(Borrar_Semaforo(semid) == ERROR){
                   printf("Advertencia: no se han podido eliminar los semaforos despues del error anterior\n");
                }
                exit(EXIT_FAILURE);
            }
            for(k=0; k<=j; k++){ /* Nos colocamos en la transaccion actual */
                fscanf(in, "%d", &price);
            }
            fclose(in);

            /* Vamos a escribir en el archivo de la caja, bajamos semaforo */
            while(Down_Semaforo(semid, i, SEM_UNDO) == ERROR){ /* Espera activa */
              active_wait++;
              if(active_wait == max_active_wait){ /* Control de errores: exceso de espera activa permitido */
                 /* Error */
                 printf("Error bajando el semaforo de la caja %d\n", i);
                 if(Borrar_Semaforo(semid) == ERROR){
                    printf("Advertencia: no se han podido eliminar los semaforos despues del error anterior\n");
                 }
                 free(name);
                 free(fcash);
                 exit(EXIT_FAILURE);
              }
           }
           active_wait=0; /* Reseteamos la espera activa */

            /**Leemos el dinero que tenemos en el cajero*/
            in = (FILE *) fopen(fcash, "r");
            if(!in){ /* Error */
                printf("Error intentando abrir el fichero del cajero de la caja %d.\n", i);
                if(Borrar_Semaforo(semid) == ERROR){
                   printf("Advertencia: no se han podido eliminar los semaforos despues del error anterior\n");
                }
                free(name);
                free(fcash);
                exit(EXIT_FAILURE);
            }
            fscanf(in, "%d\n", &amount);
            fclose(in);
            /**Guardamos la nueva cantidad de dinero*/
            amount += price;

            printf("Soy el cajero %d con PID=%d y estoy cobrando %d (total caja = %d)\n", i, getpid(), price, amount);
            fflush(NULL);

            in = fopen(fcash, "w");
            if(!in){ /* Error */
                printf("Error intentando abrir el fichero del cajero de la caja %d para actualizar su valor.\n", i);
                free(name);
                free(fcash);
                if(Borrar_Semaforo(semid) == ERROR){
                   printf("Advertencia: no se han podido eliminar los semaforos despues del error anterior\n");
                }
                exit(EXIT_FAILURE);
            }
            fprintf(in,"%d",amount);
            fclose(in);

            /* Acabamos de escribir en el archivo de la caja, subimos semaforo */
            while(Up_Semaforo(semid, i, SEM_UNDO) == ERROR){ /* Espera activa */
               active_wait++;
               if(active_wait == max_active_wait){ /* Control de errores: exceso de espera activa permitido */
                  /* Error */
                   printf("Error levantando el semaforo de cola.txt en la caja %d\n", i);
                   free(name);
                   free(fcash);
                   if(Borrar_Semaforo(semid) == ERROR){
                      printf("Advertencia: no se han podido eliminar los semaforos despues del error anterior\n");
                   }
                   exit(EXIT_FAILURE);
               }
            }
            active_wait=0; /* Reseteamos la espera activa */

            /**Si el cajero tiene mas dinero del permitido, avisamos al padre*/
            if(amount > MAX_AMOUNT){
                /* Utilizamos un fichero como si fuera una cola de señales,
                * debido a que signal no proporciona dicha cola */

                /* Vamos a escribir en el fichero de la cola, bajamos semaforo */
                while(Down_Semaforo(semid, 0, SEM_UNDO) == ERROR){ /* Espera activa */
                  active_wait++;
                  if(active_wait == max_active_wait){ /* Control de errores: exceso de espera activa permitido */
                     /* Error */
                    printf("Error bajando el semaforo de cola.txt en la caja %d\n", i);
                    free(name);
                    free(fcash);
                    if(Borrar_Semaforo(semid) == ERROR){
                       printf("Advertencia: no se han podido eliminar los semaforos despues del error anterior\n");
                    }
                    exit(EXIT_FAILURE);
                  }
               }
               active_wait=0; /* Reseteamos la espera activa */

                in = (FILE *) fopen("txtfiles/cola.txt","a");
                if(!in){ /* Error */
                    printf("Error intentando abrir el fichero de la cola la caja %d (llena).\n", i);
                    free(name);
                    free(fcash);
                    if(Borrar_Semaforo(semid) == ERROR){
                       printf("Advertencia: no se han podido eliminar los semaforos despues del error anterior\n");
                    }
                    exit(EXIT_FAILURE);
                }
                fprintf(in,"\n%d %s" ,i,"filled"); /* Necesidad de retirar 900 euros */
                fclose(in);

                if(kill(getppid(),SIGUSR1)){ /* Si kill != 0 entonces ERROR */
                    printf("Error funcion kill: %s\n", strerror(errno));
                    free(name);
                    free(fcash);
                    if(Borrar_Semaforo(semid) == ERROR){
                       printf("Advertencia: no se han podido eliminar los semaforos despues del error anterior\n");
                    }
                    exit(EXIT_FAILURE);
                }
                debug_childs++;

                /* Acabamos de escribir en el fichero de la cola, subimos semaforo */
                while(Up_Semaforo(semid, 0, SEM_UNDO) == ERROR){ /* Espera activa */
                  active_wait++;
                  if(active_wait == max_active_wait){ /* Control de errores: exceso de espera activa permitido */
                     /* Error */
                     printf("Error levantando el semaforo de cola.txt en la caja %d\n", i);
                     free(name);
                     free(fcash);
                     if(Borrar_Semaforo(semid) == ERROR){
                        printf("Advertencia: no se han podido eliminar los semaforos despues del error anterior\n");
                     }
                     exit(EXIT_FAILURE);
                  }
               }
               active_wait=0; /* Reseteamos la espera activa */
            }
            sleep(aleat_num(1,5)); /* Simulacion del tiempo de gestion de un cliente */
        }

        /* Cuando el proceso sale del bucle, es que ha acabado con todas las transacciones.
        * Tenemos que avisar al padre para que retire el dinero sobrante */

        /* Vamos a escribir en el fichero de la cola, bajamos semaforo */
        while(Down_Semaforo(semid, 0, SEM_UNDO) == ERROR){ /* Espera activa */
          active_wait++;
          if(active_wait == max_active_wait){ /* Control de errores: exceso de espera activa permitido */
             /* Error */
             printf("Error bajando el semaforo de cola.txt en la caja %d\n", i);
             free(name);
             free(fcash);
             if(Borrar_Semaforo(semid) == ERROR){
                printf("Advertencia: no se han podido eliminar los semaforos despues del error anterior\n");
             }
             exit(EXIT_FAILURE);
          }
        }
        active_wait=0; /* Reseteamos la espera activa */

        /*Indicamos que el cajero ha finalizado sus transacciones*/
        in = (FILE *) fopen("txtfiles/cola.txt","a");
        if(!in){
            printf("Error intentando abrir el fichero de la cola la caja %d (finalizada).\n", i);
            free(name);
            free(fcash);
            if(Borrar_Semaforo(semid) == ERROR){
               printf("Advertencia: no se han podido eliminar los semaforos despues del error anterior\n");
            }
            exit(EXIT_FAILURE);
        }
        fprintf(in,"\n%d %s" ,i,"fin");
        fclose(in);
        if(kill(getppid(),SIGUSR1)){ /* Si kill != 0 entonces ERROR */
            printf("%s\n", strerror(errno));
            free(name);
            free(fcash);
            if(Borrar_Semaforo(semid) == ERROR){
               printf("Advertencia: no se han podido eliminar los semaforos despues del error anterior\n");
            }
            exit(EXIT_FAILURE);
        }

        debug_childs++;
        /* Acabamos de escribir en el fichero de la cola, subimos semaforo */
        while(Up_Semaforo(semid, 0, SEM_UNDO) == ERROR){ /* Espera activa */
          active_wait++;
          if(active_wait == max_active_wait){ /* Control de errores: exceso de espera activa permitido */
             /* Error */
            printf("Error levantando el semaforo de cola.txt en la caja %d\n", i);
            free(name);
            free(fcash);
            if(Borrar_Semaforo(semid) == ERROR){
               printf("Advertencia: no se han podido eliminar los semaforos despues del error anterior\n");
            }
            exit(EXIT_FAILURE);
          }
       }
       active_wait=0; /* Reseteamos la espera activa */

        free(fcash);
        free(name);
        printf("Soy la caja %d con PID=%d y he finalizado con %d peticiones\n", i, getpid(), debug_childs);
        fflush(NULL);
        exit(EXIT_SUCCESS);
    }

    /* --------------- ZONA DE ACTUACION DEL PR. PADRE: Gerente Global -------------------*/
    if(pid != 0){
        while(n_fin < num_cash){ /* Mientras el numero de cajas finalizadas sea menor que el numero de cajas total ... */

            if(flag == 0){ /* Esta comprobacion esta explicada en la memoria ampliamente */
               sigsuspend(&set);
            }

            /* Al padre le llega una señal, tiene que leer en el fichero cola de quien */
            /* Bajamos semaforo para ello */
            while(Down_Semaforo(semid, 0, SEM_UNDO) == ERROR){ /* Espera activa */
              active_wait++;
              if(active_wait == max_active_wait){ /* Control de errores: exceso de espera activa permitido */
                 /* Error */
                  printf("Error bajando el semaforo de cola.txt en el proceso padre\n");
                  if(Borrar_Semaforo(semid) == ERROR){
                     printf("Advertencia: no se han podido eliminar los semaforos despues del error anterior\n");
                  }
                  exit(EXIT_FAILURE);
              }
            }
            active_wait=0; /* Reseteamos la espera activa */

            in = (FILE *)fopen("txtfiles/cola.txt","r");
            if(!in){ /* Error */
                printf("Error abriendo el fichero 'cola.txt'");
                if(Borrar_Semaforo(semid) == ERROR){
                   printf("Advertencia: no se han podido eliminar los semaforos despues del error anterior\n");
                }
                exit(EXIT_FAILURE);
            }
            /**Leemos la cola de cajeros que han solicitado que se retire su dinero*/
            fgets(buff, BUFFER_SIZE, in);
            sscanf(buff, "%d", &id);
            while(!feof(in)){
                fgets(buff, BUFFER_SIZE, in);
                sscanf(buff, "%d %s", &id, status);
                name = nombre_cajero(id);

                /* Modificamos el archivo del cajero cuando hayamos determinado cual es el que envio la señal */
                /* Bajamos semaforo para quitarle 900 euros, o lo sobrante */
                while(Down_Semaforo(semid, id, SEM_UNDO) == ERROR){ /* Espera activa */
                  active_wait++;
                  if(active_wait == max_active_wait){ /* Control de errores: exceso de espera activa permitido */
                     /* Error */
                      printf("Error bajando el semaforo de la caja %d en el proceso padre\n", id);
                      if(Borrar_Semaforo(semid) == ERROR){
                         printf("Advertencia: no se han podido eliminar los semaforos despues del error anterior\n");
                      }
                      fclose(in);
                      free(name);
                      exit(EXIT_FAILURE);
                  }
               }
               active_wait=0; /* Reseteamos la espera activa */

                faux = (FILE *) fopen(name,"r");
                if(!faux){ /* Error */
                    printf("Error abriendo para leer el fichero de caja en el proceso padre\n");
                    fclose(in);
                    free(name);
                    if(Borrar_Semaforo(semid) == ERROR){
                       printf("Advertencia: no se han podido eliminar los semaforos despues del error anterior\n");
                    }
                    exit(EXIT_FAILURE);
                }

                fscanf(faux, "%d", &price);
                fclose(faux);

                faux = (FILE *) fopen(name, "w");
                if(!faux){ /* Error */
                    printf("Error abriendo para escribir el fichero de caja en el proceso padre\n");
                    fclose(in);
                    free(name);
                    if(Borrar_Semaforo(semid) == ERROR){
                       printf("Advertencia: no se han podido eliminar los semaforos despues del error anterior\n");
                    }
                    exit(EXIT_FAILURE);
                }

                if(!strcmp(status, "filled") && price > MAX_AMOUNT){ /* El cajero tenia mas de 1000 euros */
                    amount = price - REMOVE;
                    fprintf(faux, "%d", amount);

                    total += REMOVE;
                }else if(!strcmp(status, "fin")){ /* El cajero termino y quiere que le retiren lo sobrante */
                    total += price;
                    fprintf(faux, "%d", 0);
                    n_fin ++;
                }
                free(name);
                fclose(faux);


                debug_father++;

                /* Una vez realizados los calculos pertinentes en el cajero,
                * levantamos su semaforo para dejarlo trabajar */
                while(Up_Semaforo(semid, id, SEM_UNDO) == ERROR){ /* Espera activa */
                  active_wait++;
                  if(active_wait == max_active_wait){ /* Control de errores: exceso de espera activa permitido */
                     /* Error */
                    printf("Error levantando el semaforo de la caja %d en el proceso padre\n", id);
                    if(Borrar_Semaforo(semid) == ERROR){
                       printf("Advertencia: no se han podido eliminar los semaforos despues del error anterior\n");
                    }
                    fclose(in);
                    exit(EXIT_FAILURE);
                  }
               }
               active_wait=0; /* Reseteamos la espera activa */
            }
            fclose(in);

            in = (FILE *)fopen("txtfiles/cola.txt","w");
            if(!in){ /* Error */
                printf("Error abriendo el fichero 'cola.txt'");
                if(Borrar_Semaforo(semid) == ERROR){
                   printf("Advertencia: no se han podido eliminar los semaforos despues del error anterior\n");
                }
                exit(EXIT_FAILURE);
            }
            fclose(in);

            flag = 0;
            /* EL padre termina de procesar la cola, por lo que restaura su disponibilidad */
            while(Up_Semaforo(semid, 0, SEM_UNDO) == ERROR){ /* Espera activa */
               active_wait++;
               if(active_wait == max_active_wait){ /* Control de errores: exceso de espera activa permitido */
                  /* Error */
                  printf("Error levantando el semaforo de cola.txt en el proceso padre\n");
                  if(Borrar_Semaforo(semid) == ERROR){
                     printf("Advertencia: no se han podido eliminar los semaforos despues del error anterior\n");
                  }
                  exit(EXIT_FAILURE);
               }
            }
            active_wait=0; /* Reseteamos la espera activa */
        }
    }
    if(Borrar_Semaforo(semid)==ERROR){
       /* Error */
        printf("Error eliminando conjunto de semaforos\n");
        exit(EXIT_FAILURE);
    }

    /* Hacemos una ultima comprobacion de errores:
    * la suma de todas las transacciones de los cajeros tiene que ser igual
    * a la suma realizada anteriormente */
    printf("\nComprobando la correspondencia de las ganancias...\n");
    fflush(NULL);
    if(final_check(num_cash, total) == OK){
      printf("Comprobado exitosamente: la suma coincide con el total\n");
    }else{
      printf("Advertencia: la suma NO coincide con el total\n");
    }

    printf("\n\t==> GANANCIAS =  %d euros <==\nSe han realizado un total de %d peticiones (comprobar que es la suma de las peticiones de los hijos)\n", total, debug_father);
    fflush(NULL);

    exit(EXIT_SUCCESS);
}


int is_valid_integer(char *input){
    int len, i;

    if(!input){
        printf("Error. Input igual a NULL\n");
        exit(EXIT_FAILURE);
    }

    len = strlen(input);

    for(i=0; i<len; i++){
        if(!isdigit(input[i])){
         printf("ERROR. El parámetro introducido no es un entero positivo.\n");
         return 0;
      }
    }
    if(!atoi(input)){
      printf("ERROR. No se admite cero como entero de entrada.\n");
      return 0;
   }
   return 1;
}


char *nombre_transaccion(int num){
    char *text=NULL, *text2=NULL;

    text = (char *) malloc(SIZE * sizeof(char));
    if(!text){
        printf("Error reservando memoria para text en la funcion 'nombre_transaccion'\n");
        return NULL;
    }

    text2 = (char *) malloc(SIZE * sizeof(char));
    if(!text2){
        printf("Error reservando memoria para text2 en la funcion 'nombre_transaccion'\n");
        return NULL;
    }

    strcpy(text, "txtfiles/clientesCaja");
    sprintf(text2,"%d",num);
    strcat(text2,".txt");
    strcat(text,text2);
    free(text2);
    return text;
}


char *nombre_cajero(int num){
    char *text=NULL, *text2=NULL;

    text = (char *) malloc(SIZE * sizeof(char));
    if(!text){
        printf("Error reservando memoria para text en la funcion 'nombre_cajero'\n");
        return NULL;
    }

    text2 = (char *) malloc(SIZE * sizeof(char));
    if(!text2){
        printf("Error reservando memoria para text2 en la funcion 'nombre_cajero'\n");
        return NULL;
    }

    strcpy(text, "txtfiles/cajero");
    sprintf(text2,"%d",num);
    strcat(text2,".txt");
    strcat(text,text2);
    free(text2);
    return text;
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


void handler_SIGUSR1(int sig){
   flag = 1;
   return;
}


int final_check(int num_cash, int total){
   FILE *in=NULL;
   int i, j;
   int n_aux, n_sum=0;
   char *name=NULL;

   for(i=1; i<=num_cash; i++){
      if((name = nombre_transaccion(i)) == NULL){
         printf("Error usando nombre_transaccion() en la funcion final_check\n");
         return ERROR;
      }

      in = (FILE *) fopen(name, "r");
      if(in==NULL){
         printf("Error abriendo las transacciones numero %d en final_check()\n", i);
         return ERROR;
      }

      while(!feof(in)){
         fscanf(in, "%d", &n_aux);
         n_sum += n_aux; /* Sumamos cada cantidad de todos los ficheros */
      }

      fclose(in);
      free(name);
   }

   printf("\tSuma ficheros transacciones = %d\n", n_sum);
   printf("\tSuma total de los cajeros = %d\n", total);

   if(total == n_sum) return OK;
   return ERROR;
}
