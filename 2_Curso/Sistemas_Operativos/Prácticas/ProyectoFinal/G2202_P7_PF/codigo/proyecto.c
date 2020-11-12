/**
* @brief Proyecto Final
*
* Proyecto final de la asignatura de Sistemas Operativos 2018
* @file proyecto.c
* @author Alejandro Santorum & David Cabornero (G2202-Pareja7)
* @version 1.0
* @date 04-05-2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <signal.h>
#include <limits.h>
#include <ctype.h>
#include <pthread.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <syslog.h>
#include "semaforos.h"


#define N_ARGS 6 /*!< Numero de argumentos de entrada */
#define MIN_PROC 3 /*!< Numero de procesos */

#define MAX_HORSES 10 /*!< Numero maximo de caballos */
#define MIN_HORSES 2 /*!< Numero minimo de caballos */
#define MAX_RACE 200 /*!< Longitud maxima de la carrera */
#define MIN_RACE 20 /*!< Longitud minima de la carrera */
#define MAX_BETTOR 100 /*!< Numero maximo de apostadores */
#define MIN_BETTOR 10 /*!< Numero minimo de apostadores */
#define MAX_WINDOWS 30 /*!< Numero maximo de ventanillas */
#define MIN_WINDOWS 1 /*!< Numero minimo de ventanillas */
#define MAX_MONEY 2000 /*!< Cantidad maxima apostable en una unica apuesta */
#define MIN_MONEY 10 /*!< Cantidad minima apostable en una unica apuesta */

#define PROC_MANAGER 0 /*!< Indice del array de PIDS del proceso manejador de apuestas */
#define PROC_BETTOR 1 /*!< Indice del array de PIDS del proceso apostador */
#define PROC_DISPLAYER 2 /*!< Indice del array de PIDS del proceso monitor */

#define SEM_SIZE 3 /*!< Tamanio del array de semaforos */
#define MARKET_SEM 0  /*!< Indice del array de semaforos del semaforo que controla el acceso a la zona de memoria compartida de las cotizaciones */
#define RACECONTROL_SEM 1 /*!< Indice del array de semaforos del semaforo que controla el acceso a la zona de memoria compartida del control de carrera */
#define FILE_SEM 2 /*!< Indice del array de semaforos del semaforo que controla el acceso a ficheros de texto */

#define FIRST 1 /*!< Primera posicion de la carrera */
#define NORMAL 100 /*!< Tirada de tipo normal: ni remontadora ni ganadora */
#define LAST -100 /*!< Ultima posicion de la carrera */

#define PATH "/bin/bash" /*!< Directorio de obtenicion de keys */
#define BETFILE "apuestas.txt" /*!< Fichero de guardado de datos de las apuestas */
#define BETTORFILE "resultados_apostadores.txt" /*!< Fichero de guardado de datos de los resultadores de las apuestas */
#define ERROR -1 /*!< Constante de error */
#define SECONDS 30 /*!< Tiempo (s) de duracion de las apuestas */
#define NAME_SIZE 20 /*!< Tamanio maximo de los nombres de los apostadores */
#define BUFFER_SIZE 128 /*!< Tamanio maximo del buffer de lectura */
#define N_BEST_BETTOR 10 /*!< Numero de mejores apostadores mostrados por pantalla */

/**
* @brief Estructura de colas de mensajes
*
* Esta estructura contiene la informacion necesaria para comunicarse por colas de mensajes
*/
struct msgbuf{
    long mtype; /*!< tipo del mensaje */
    struct{
        struct{
            char name[NAME_SIZE]; /*!< nombre apostador */
            int bettor_id; /*!< ID apostador */
            int horse_id; /*!< ID caballo */
            float bet; /*!< cantidad apostada */
        }betting; /*!< Informacion de apuestas */
        struct{
            int position; /*!< posicion */
            int last_throw; /*!< ultima tirada */
        }race;
    }info; /*!< Informacion de control de carrera */
};

/**
* @brief Estructura de memoria compartida de cotizaciones
*
* Esta estructura contiene la informacion de las cotizaciones en la etapa de apuestas
*/
typedef struct{
    float horse_bet[MAX_HORSES]; /*!< Apuestas totoles a cada caballo */
    float horse_rate[MAX_HORSES]; /*!< Cotizacion de cada caballo */
    float total; /*!< Cantidad total apostada */
}market_rates_struct;

/**
* @brief Estructura de memoria compartida de control de carrera
*
* Esta estructura contiene la informacion del control de carrera de los caballos
*/
typedef struct{
    int position[MAX_HORSES]; /*!< Posicion de cada caballo */
    int last_throw[MAX_HORSES]; /*!< Ultima tirada de cada caballo */
    int current_box[MAX_HORSES]; /*!< Casilla actual de cada caballo */
    int horses_done; /*!< Numero de caballos que ya han tirado en el turno actual */
}race_control_struct;


/**
* @brief inicializa syslog
* @return void.
*/
void init_syslog();

/**
* @brief comprueba si una cadena de caracteres es un numero
*
* @param input - cadena de caracteres
* @return 1 en caso de que sea un numero. 0 en caso contrario
*/
int is_valid_integer(char *input);

/**
* @brief devuelve un numero entero aleatorio en el intervalo (limites incluidos)
*
* @param inf - limite inferior intervalo
* @param sup - limite superior intervalo
* @return entero aleatorio en el intervalo. Corta ejecucion en caso de error.
*/
int aleat_num(int inf, int sup);

/**
* @brief devuelve un numero decimal aleatorio en el intervalo (limites incluidos)
*
* @param inf - limite inferior intervalo
* @param sup - limite superior intervalo
* @return entero aleatorio en el intervalo.
*/
float float_rand( float min, float max );

/**
* @brief nuevo manejador de la señal SIGUSR1 para el proceso apostador.
* Su funcionalidad es simplemente obligar al proceso a no ignorar la señal.
* Ademas, pone la variable global de control del apostador a 1
*
* @param sig - la señal que utilizará este manejador cuando sea llamada
* @return void.
*/
void handler_SIGUSR1_bettor(int sig);

/**
* @brief nuevo manejador de la señal SIGUSR2.
* Su funcionalidad es simplemente obligar al proceso a no ignorar la señal.
*
* @param sig - la señal que utilizará este manejador cuando sea llamada
* @return void.
*/
void handler_SIGUSR2(int sig);

/**
* @brief funcion que implementa la funcionalidad del proceso monitor
*
* @param bettor_process_pid - id del proceso apostador
* @param betting_manager_process_pid - id del proceso manejador de apuestas
* @param len_race - longitud de la carrera
* @param n_bettor - numero de apostadores
* @return void.
*/
void displayer_process(int bettor_process_pid, int betting_manager_process_pid, int len_race, int n_bettor);

/**
* @brief funcion que implementa la funcionalidad del proceso manejador de apuestas
*
* @param n_horses - numero de caballos
* @param n_bettor - numero de apostadores
* @param n_windows - numero de vetanillas
* @return void.
*/
void betting_manager_process(int n_horses, int n_bettor, int n_windows);

/**
* @brief funcion que implementa la funcionalidad del proceso apostador
*
* @param n_horses - numero de caballos
* @param n_bettor - numero de apostadores
* @param money - cantidad maxima apostadble por apuesta
* @return void.
*/
void bettor_process(int n_horses, int n_bettor, int money);

/**
* @brief funcion que implementa la funcionalidad del proceso caballo
*
* @return void.
*/
void horse();

/**
* @brief funcion que implementa la funcionalidad de las ventanillas
* 
* @param arg - puntero a estructura de informacion
* @return void*.
*/
void* window_function(void* arg);

/**
* @brief funcion que asigna a cada caballo su posicion en el ranking actual
* 
* @param current - array de enteros que se corresponden con la casilla actual de cada caballo
* @param position - array de enteros en el que se devuelven las posiciones de los caballos actuales
* @param len - longitud de los arrays
* @return void.
*/
void classification(int *current, int *position, int len);

/**
* @brief funcion auxiliar de la funcion classification que se encarga de comprobar si todos los caballos han sido clasificados
* 
* @param current - array de enteros que se corresponden con la casilla de cada caballo, o -1 si ya ha sido clasificado
* @param len - longitud del array
* @return 1 si ya han sido todos clasificados o 0 en caso contrario.
*/
int checked(int *array, int len);

/**
* @brief funcion auxiliar que se encarga de comprobar si la carrera ha finalizado
* 
* @param current - array de enteros que se corresponden con la casilla de cada caballo, o -1 si ya ha sido clasificado
* @param len - longitud del array
* @param racelen - longitud total de la carrera
* @return 1 si ya han sido todos clasificados o 0 en caso contrario.
*/
int finished(int *array, int len, int racelen);

/**
* @brief funcion que calcula los resultados de las apuestas y los escribe en un fichero
* 
* @param winners - array de IDs de los caballos ganadores de la carrera
* @param n_winners - numero de ganadores (tamaño del array winners)
* @param n_bettor - numero de apostadores
* @return void
*/
void calculate_bet_results(int *winners, int n_winners, int n_bettor);

/**
* @brief funcion que calcula los mejores apostadores y los muestra por pantalla
* 
* @param n_bettor - numero de apostadores
* @return void
*/
void print_best_bettors(int n_bettor);


int semid, msgid, memid_market, memid_race; /** Variables invariantes a lo largo del programa y de interes comun */
int n_horses, n_proc; /** Paramentros de entrada necesitados en handlers */
int flag_bettor=0, flag_window=0; /** Flags variables para hilos, handlers y proceso apostador */
int *pids=NULL; /** IDS de todos los procesos para poder acabar su ejecución en el caso de que se utilice CTRL+C */
market_rates_struct *market_rates=NULL; /** Cotizaciones de los caballos */
race_control_struct *race_control=NULL; /** Estructura de control de carrera */

int main(int argc, char **argv){
    int len_race, n_bettor, n_windows, money;
    int i, j;
    int semkey, msgkey, memkey_market, memkey_race;
    unsigned short ini_sem[SEM_SIZE];
    void handler_SIGUSR2();
    void handler_SIGINT();
    
    /* Comprobacion inicial de errores */
    if(argc != N_ARGS){
        printf("Argumentos que se deben especificar:\n");
        printf("-Numero de caballos de la carrera(min=%d, max=%d)\n", MIN_HORSES, MAX_HORSES);
        printf("-Longitud de la carrera(min=%d, max=%d)\n", MIN_RACE, MAX_RACE);
        printf("-Numero de apostadores(min=%d, max=%d)\n", MIN_BETTOR, MAX_BETTOR);
        printf("-Numero de ventanillas(min=%d, max=%d)\n", MIN_WINDOWS, MAX_WINDOWS);
        printf("-Dinero de cada apostante(min=%d, max=%d)\n", MIN_MONEY, MAX_MONEY);
        exit(EXIT_FAILURE);
    }
    
    for(i = 1; i < N_ARGS; i++){
        if(!is_valid_integer(argv[i])){
            printf("Error en el parametro %d: entero no valido o 0\n",i);
            exit(EXIT_FAILURE);
        }
    }
    
    n_horses = atoi(argv[1]);
    len_race = atoi(argv[2]);
    n_bettor = atoi(argv[3]);
    n_windows = atoi(argv[4]);
    money = atoi(argv[5]);
    
    if(n_horses > MAX_HORSES || n_horses < MIN_HORSES){
        printf("Error. El numero de caballos debe estar entre %d y %d\n", MIN_HORSES, MAX_HORSES);
        exit(EXIT_FAILURE);
    }
    
    if(len_race < MIN_RACE || len_race > MAX_RACE){
        printf("Error. La longitud de la carrera debe ser como minimo %d, y como maximo %d\n", MIN_RACE, MAX_RACE);
        exit(EXIT_FAILURE);
    }
    
    if(n_bettor < MIN_BETTOR || n_bettor > MAX_BETTOR){
        printf("Error. El numero de apostadores debe ser como minimo %d, y como maximo %d\n", MIN_BETTOR, MAX_BETTOR);
        exit(EXIT_FAILURE);
    }
    
    if(n_windows < MIN_WINDOWS || n_windows > MAX_WINDOWS){
        printf("Error. El numero de ventanillas debe ser como minimo %d, y como maximo %d\n", MIN_WINDOWS, MAX_WINDOWS);
        exit(EXIT_FAILURE);
    }
    
    if(money < MIN_MONEY || money > MAX_MONEY){
        printf("Error. La cantidad de dinero de un apostador debe ser como minimo %d, y como maximo %d\n", MIN_MONEY, MAX_MONEY);
        exit(EXIT_FAILURE);
    }
    /* Fin de la comprobacion inicial de errores */
    
    n_proc = n_horses+MIN_PROC;
    init_syslog();
    
    if(signal(SIGUSR2, handler_SIGUSR2)==SIG_ERR){
        perror("Error estableciendo el nuevo manejador de SIGUSR2 en el proceso principal");
        exit(EXIT_FAILURE);
    }
    
    /* Array de pids de todos los procesos a crear */
    pids = (int*) malloc(n_proc * sizeof(int));
    if(!pids){
        perror("Error al reservar memoria para el array de pids");
        exit(EXIT_FAILURE);
    }
    
    /* CREACION COLA DE MENSAJES */
    msgkey = ftok(PATH, aleat_num(1000, 3000));
    if(msgkey == ERROR){
        free(pids);
        perror("Error obteniendo la key para la cola de mensajes");
        exit(EXIT_FAILURE);
    }
    msgid = msgget(msgkey, IPC_CREAT|IPC_EXCL|0660);
    if(msgid==ERROR && errno==EEXIST){
        msgid = msgget(msgkey, IPC_CREAT|0660);
    }else if(msgid == ERROR){
        free(pids);
        perror("Error creando la cola de mensajes");
        exit(EXIT_FAILURE);
    }
    /* FIN CREACION COLA MENSAJES */
    
    
    /* CREACION DE SEMAFOROS */
    semkey = ftok(PATH, aleat_num(3001, 6000));
    if(semkey == ERROR){
        msgctl(msgid, IPC_RMID, NULL); /* Sin comprobacion de error porque precisamente estamos terminando el programa */
        free(pids);
        perror("Error obteniendo la key para los semaforos");
        exit(EXIT_FAILURE);
    }
    if(Crear_Semaforo(semkey, SEM_SIZE, &semid) == ERROR){
        msgctl(msgid, IPC_RMID, NULL); /* Sin comprobacion de error porque precisamente estamos terminando el programa */
        free(pids);
        perror("Error creando el conjunto de semaforos");
        exit(EXIT_FAILURE);
    }
    for(j=0; j<SEM_SIZE; j++){
        ini_sem[j] = 1;
    }
    if(Inicializar_Semaforo(semid, ini_sem) == ERROR){/*Ponemos los semáforos a 1*/
        msgctl(msgid, IPC_RMID, NULL); /* Sin comprobacion de error porque precisamente estamos terminando el programa */
        free(pids);
        Borrar_Semaforo(semid);
        perror("Error inicializando a 1 el conjunto de semaforos");
        exit(EXIT_FAILURE);
    }
    /* FIN CREACION DE SEMAFOROS */ 
    
    
    /* CREACION MEMORIA COMPARTIDA */
    memkey_market = ftok(PATH, aleat_num(6001,9000));
    if(memkey_market == ERROR){
        msgctl(msgid, IPC_RMID, NULL); /* Sin comprobacion de error porque precisamente estamos terminando el programa */
        Borrar_Semaforo(semid);
        free(pids);
        perror("Error obteniendo la key para la zona compartida de las cotizaciones");
        exit(EXIT_FAILURE);
    }
    memid_market = shmget(memkey_market, sizeof(market_rates_struct), IPC_CREAT|0660);
    if(memid_market == ERROR){
        msgctl(msgid, IPC_RMID, NULL); /* Sin comprobacion de error porque precisamente estamos terminando el programa */
        Borrar_Semaforo(semid);
        free(pids);
        perror("Error al crear la memoria compartida para las cotizaciones.");
        exit(EXIT_FAILURE);
    }
    market_rates = (market_rates_struct *) shmat(memid_market, (char *)0, 0);
    if(market_rates == ((void*)ERROR)){
        msgctl(msgid, IPC_RMID, NULL); /* Sin comprobacion de error porque precisamente estamos terminando el programa */
        shmctl(memid_market, IPC_RMID, NULL);
        Borrar_Semaforo(semid);
        free(pids);
        perror("Error adjuntando la zona de memoria para las cotizaciones");
        exit(EXIT_FAILURE);
    }
    market_rates->total = 0.0;
    
    memkey_race = ftok(PATH, aleat_num(9001, 12000));
    if(memkey_race == ERROR){
        msgctl(msgid, IPC_RMID, NULL); /* Sin comprobacion de error porque precisamente estamos terminando el programa */
        shmdt(market_rates);
        shmctl(memid_market, IPC_RMID, NULL);
        Borrar_Semaforo(semid);
        free(pids);
        perror("Error obteniendo la key para la zona compartida de los beneficios de los apostadores");
        exit(EXIT_FAILURE);
    }
    memid_race = shmget(memkey_race, sizeof(race_control_struct), IPC_CREAT|0660);
    if(memid_race == ERROR){
        msgctl(msgid, IPC_RMID, NULL); /* Sin comprobacion de error porque precisamente estamos terminando el programa */
        shmdt(market_rates);
        shmctl(memid_market, IPC_RMID, NULL);
        Borrar_Semaforo(semid);
        free(pids);
        perror("Error creando la memoria compartida para los beneficios de los apostadores");
        exit(EXIT_FAILURE);
    }
    race_control = (race_control_struct *) shmat(memid_race, (char*)0, 0);
    if(race_control == ((void*)ERROR)){
        msgctl(msgid, IPC_RMID, NULL); /* Sin comprobacion de error porque precisamente estamos terminando el programa */
        shmdt(market_rates);
        shmctl(memid_market, IPC_RMID, NULL);
        shmctl(memid_race, IPC_RMID, NULL);
        Borrar_Semaforo(semid);
        free(pids);
        perror("Error creando la memoria compartida para los beneficios de los apostadores");
        exit(EXIT_FAILURE);
    }
    /* FIN CREACION MEMORIA COMPARTIDA */
    
    
    for(i=0; i<n_proc; i++){
        if((pids[i] = fork())==ERROR){
            msgctl(msgid, IPC_RMID, NULL); /* Sin comprobacion de error porque precisamente estamos terminando el programa */
            shmdt(market_rates);
            shmctl(memid_market, IPC_RMID, NULL);
            shmdt(race_control);
            shmctl(memid_race, IPC_RMID, NULL);
            Borrar_Semaforo(semid);
            free(pids);
            perror("Error al realizar fork");
            exit(EXIT_FAILURE);
        }
        if(!pids[i]){
            break;
        }
    }
    
    if(i==PROC_DISPLAYER){
        displayer_process(pids[PROC_BETTOR], pids[PROC_MANAGER], len_race, n_bettor);
    }else if(i==PROC_MANAGER){
        betting_manager_process(n_horses, n_bettor, n_windows);
    }else if(i==PROC_BETTOR){
        bettor_process(n_horses, n_bettor, money);
    }else if(i>PROC_DISPLAYER && i<n_proc){
        horse(i-PROC_DISPLAYER);
    }else{/* Proceso padre*/
        if(signal(SIGINT, handler_SIGINT)==SIG_ERR){
            perror("Error estableciendo el nuevo manejador de SIGINT en el proceso principal");
            exit(EXIT_FAILURE);
        }
        pause(); /* Espera a que el periodo de apuestas finalice */
    }
    
    if(msgctl(msgid, IPC_RMID, NULL) == ERROR){
        perror("Advertencia: no se ha podido eliminar la cola de mensajes de las cotizaciones");
    }
    if(shmdt(market_rates) == ERROR){
        perror("Advertencia: no se ha podido desadjuntar la zona de memoria compartida para las cotizaciones");
    }
    if(shmctl(memid_market, IPC_RMID, NULL) == ERROR){
        perror("Advertencia: no se ha podido eliminar la zona de memoria compartida de las cotizaciones");
    }
        
    for(j=0; j<n_horses; j++){
        race_control->position[j] = 0;
        race_control->last_throw[j] = 0;
        race_control->current_box[j] = 0;
        race_control->horses_done = 0;
    }
    
    while(1){
        /* Comprobamos si la carrera ha terminado */
        if(finished(race_control->current_box, n_horses, len_race)){
            break;
        }
        
        /* Avisamos al proceso monitor que muestre el estado actual de la carrera */
        kill(pids[PROC_DISPLAYER], SIGUSR2);
        pause();
        
        for(j=PROC_DISPLAYER+1; j<n_proc; j++){
            kill(pids[j], SIGUSR2);
        }
        
        pause();
        
        if(Down_Semaforo(semid, RACECONTROL_SEM, 0) == ERROR){
            perror("Error bajando el semaforo de control de carrera en el proceso principal");
            Borrar_Semaforo(semid);
            exit(EXIT_FAILURE);
        }
        
        race_control->horses_done = 0;
        classification(race_control->current_box, race_control->position, n_horses);
        
        if(Up_Semaforo(semid, RACECONTROL_SEM, 0) == ERROR){
            perror("Error levantando el semaforo de control de carrera en el proceso principal");
            Borrar_Semaforo(semid);
            exit(EXIT_FAILURE);
        }
    }
    
    /* Avisamos al proceso monitor de que muestre toda la informacion de final de carrera */
    kill(pids[PROC_DISPLAYER], SIGUSR2);
    
    for(j=PROC_DISPLAYER+1; j<n_proc; j++){
        kill(pids[j], SIGINT); /* Finalizamos los caballos */
    }
    
    while(wait(NULL)>0);
    
    closelog();
    shmdt(race_control);
    shmctl(memid_race, IPC_RMID, NULL);
    Borrar_Semaforo(semid);
    free(pids);
    exit(EXIT_SUCCESS);
}


void displayer_process(int bettor_process_pid, int betting_manager_process_pid, int len_race, int n_bettor){
    void handler_SIGUSR2();
    int j, k;
    int *winners=NULL;
    
    srand(time(NULL) + getpid());
    
    printf("Abriendo ventanillas e inicilizando apuestas...\n");
    syslog(LOG_NOTICE, "Abriendo ventanillas e inicilizando apuestas...");
    sleep(2);
    for(j=SECONDS; j>0; j--){
        sleep(1);
        if(Down_Semaforo(semid, MARKET_SEM, 0) == ERROR){
            perror("Error bajando el semaforo de las cotizaciones en el monitor");
            Borrar_Semaforo(semid);
            exit(EXIT_FAILURE);
        }
        printf("\t===> SEGUNDOS RESTANTES PARA LA CARRERA = %d <===\n", j);
        printf("COTIZACIONES ACTUALES DE LOS CABALLOS:\n");
        for(k=0; k<n_horses; k++){
            printf("Cotizacion caballo ID %d = %f\n", k+1, market_rates->horse_rate[k]);
            syslog(LOG_NOTICE, "Cotizacion caballo ID %d = %f\n", k+1, market_rates->horse_rate[k]);
        }
        if(Up_Semaforo(semid, MARKET_SEM, 0) == ERROR){
            perror("Error levantando el semaforo de las cotizaciones en el monitor");
            Borrar_Semaforo(semid);
            exit(EXIT_FAILURE);
        }
    }
    
    kill(bettor_process_pid, SIGINT);
    kill(betting_manager_process_pid, SIGUSR2);
    sleep(1); /* Ayuda a la sincronizacion */
    printf("\n\t ======================================\n");
    printf("APUESTAS FINALIZADAS. La carrera comenzara en breves instantes");
    printf("\n\t ======================================\n");
    syslog(LOG_NOTICE, "APUESTAS FINALIZADAS. La carrera comenzara en breves instantes");
    
    kill(getppid(), SIGUSR2); /* Avisa al proceso principal de que las apuestas han finalizado */
        
    while(1){
        pause(); /* Espera a la señal del proceso principal */
        
        if(Down_Semaforo(semid, RACECONTROL_SEM, 0) == ERROR){
            perror("Error bajando el semaforo de control de carrera en el monitor");
            Borrar_Semaforo(semid);
            exit(EXIT_FAILURE);
        }
        if(finished(race_control->current_box, n_horses, len_race)){
            if(Up_Semaforo(semid, RACECONTROL_SEM, 0) == ERROR){
                perror("Error subiendo el semaforo de control de carrera en el monitor en el break");
                Borrar_Semaforo(semid);
                exit(EXIT_FAILURE);
            }
            break;
        }
        
        printf("\tEstado actual de la carrera:\n");
        for(j=0; j<n_horses; j++){
            if(race_control->position[j]!=LAST){
                printf("Caballo nº %d en la %dª posicion (casilla nº %d)\n", j+1, race_control->position[j], race_control->current_box[j]);
                syslog(LOG_NOTICE, "Caballo nº %d en la %dª posicion (casilla nº %d)\n", j+1, race_control->position[j], race_control->current_box[j]);
            }else{
                printf("Caballo nº %d en la ultima posicion (casilla nº %d)\n", j+1, race_control->current_box[j]);
                syslog(LOG_NOTICE, "Caballo nº %d en la ultima posicion (casilla nº %d)\n", j+1, race_control->current_box[j]);
            }
        }
        
        if(Up_Semaforo(semid, RACECONTROL_SEM, 0) == ERROR){
            perror("Error subiendo el semaforo de control de carrera en el monitor");
            Borrar_Semaforo(semid);
            exit(EXIT_FAILURE);
        }
        usleep(1500000);
        kill(getppid(), SIGUSR2);
    }
    
    printf("\n\t ======================================\n");
    printf("¡CARRERA FINALIZADA!: espere unos instantes mientras calculamos los resultados...");
    printf("\n\t ======================================\n");
    syslog(LOG_NOTICE, "¡CARRERA FINALIZADA!: espere unos instantes mientras calculamos los resultados...");
    
    sleep(2); /* Csmbiar por 15? */
    
    winners = (int*) malloc(n_horses * sizeof(int));
    if(!winners){
        perror("Error al reservar memoria para la lista de ganadores");
        exit(EXIT_SUCCESS);
    }
    
    for(j=0, k=0; j<n_horses; j++){
        if(race_control->position[j] == FIRST){
            printf("El caballo %d ha GANADO LA CARRERA (casilla final = %d)\n", j+1, race_control->current_box[j]);
            syslog(LOG_NOTICE, "El caballo %d ha GANADO LA CARRERA (casilla final = %d)\n", j+1, race_control->current_box[j]);
            winners[k] = j+1;
            k++;
        }else if(race_control->position[j] == LAST){
            printf("El caballo %d ha terminado ultimo (casilla final = %d)\n", j+1, race_control->current_box[j]);
            syslog(LOG_NOTICE, "El caballo %d ha terminado ultimo (casilla final = %d)\n", j+1, race_control->current_box[j]);
        }else{
            printf("El caballo %d ha terminado en %dª posicion (casilla final = %d)\n", j+1, race_control->position[j], race_control->current_box[j]);
            syslog(LOG_NOTICE, "El caballo %d ha terminado en %dª posicion (casilla final = %d)\n", j+1, race_control->position[j], race_control->current_box[j]);
        }
    }
    
    calculate_bet_results(winners, k, n_bettor);
    print_best_bettors(n_bettor);
    
    free(winners);
    exit(EXIT_SUCCESS);
}


void betting_manager_process(int n_horses, int n_bettor, int n_windows){
    pthread_t *thr=NULL;
    pthread_attr_t attr;
    int *window_id=NULL;
    int j;
    FILE *f=NULL;
    
    srand(time(NULL) + getpid());
    
    /* Inicializamos las apuestas */
    for(j=0; j<n_horses; j++){
        market_rates->horse_bet[j] = 1.0;
        market_rates->total += 1.0;
        market_rates->horse_rate[j] = market_rates->total/market_rates->horse_bet[j];
    }
    /* --------------------- */
    
    f = (FILE *) fopen(BETFILE, "w");
    if(!f){
        perror("Error creando un nuevo fichero de apuestas");
        exit(EXIT_FAILURE);
    }
    fprintf(f, "Apostador_ID   N_Ventanilla   Caballo_ID   Cotizacion   Cantidad\n");
    
    fclose(f);
    
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    
    window_id = (int *) malloc(n_windows*sizeof(int));
    if(!window_id){
        perror("Error reservando memoria para el array de ids de las ventanillas");
        exit(EXIT_FAILURE);
    }
    
    thr = (pthread_t*) malloc(n_windows * sizeof(pthread_t));
    if(!thr){
        perror("Error reservando los hilos en el gestor de apuestas");
        free(window_id);
        exit(EXIT_FAILURE);
    }
    for(j=0; j<n_windows; j++){
        window_id[j] = j;
        if(pthread_create(&thr[j], &attr, window_function, (void *) &window_id[j])!= 0){
            free(thr);
            free(window_id);
            perror("Error en la creación de los hilos ventanilla");
            exit(EXIT_FAILURE);
        }
    }
    
    pause(); /* Esperando a que comience la carrera para terminar con los apuestas */
    flag_window = 1; /* Carrera iniciada, apuestas finalizadas, ventanillas cerradas */
    for(j=0; j<n_windows; j++){
        pthread_join(thr[j], NULL);
    }
    free(window_id);
    free(thr);
    
    exit(EXIT_SUCCESS);
}


void bettor_process(int n_horses, int n_bettor, int money){
    struct msgbuf msg_arg={0};
    void handler_SIGUSR1_bettor();
    int rand_horse, rand_bettor;
    float rand_bet;
    char aux[NAME_SIZE];
    
    srand(time(NULL) + getpid()); /* Semilla de generacion de numeros aleatorios distinta al resto de procesos */
    
    if(signal(SIGUSR1, handler_SIGUSR1_bettor)==SIG_ERR){
        perror("Error estableciendo el nuevo manejador de SIGUSR1 en el proceso apostador");
        exit(EXIT_FAILURE);
    }
    
    msg_arg.mtype = 1;
    while(!flag_bettor){
        usleep(200000);
        rand_horse = aleat_num(1, n_horses);
        rand_bettor = aleat_num(1, n_bettor);
        do{
            rand_bet = float_rand(0, money);
        }while(rand_bet == 0.0);
        strcpy(msg_arg.info.betting.name, "Apostador-");
        sprintf(aux, "%d", rand_bettor);
        strcat(msg_arg.info.betting.name, aux);
        msg_arg.info.betting.bettor_id = rand_bettor;
        msg_arg.info.betting.horse_id = rand_horse;
        msg_arg.info.betting.bet = rand_bet;
        if(msgsnd(msgid, (struct msgbuf *)&msg_arg, sizeof(msg_arg.info), 0) == ERROR){
            if(errno!=EIDRM && errno!=EINTR){
                /* msgsnd puede devolver error si el proceso recibe una señal
                 * del sistema o si la cola de mensajes es eliminada, lo cual
                 * no es un error que deba ser reportado y subsanado */
                perror("Error enviando mensaje desde el proceso apostador\n");
                exit(EXIT_FAILURE);
            }
            
        }
        memset(msg_arg.info.betting.name, 0, sizeof(msg_arg.info.betting.name));
    }
    exit(EXIT_SUCCESS);
}

void horse(int id){
    int the_throw=-1, last1, last2;
    
    srand(time(NULL) + getpid());
    
    pause(); /* Esperamos al inicio de la carrera */
    
    while(1){
        if(Down_Semaforo(semid, RACECONTROL_SEM, 0) == ERROR){
            perror("Error bajando el semaforo de control de carrera en un caballo");
            Borrar_Semaforo(semid);
            exit(EXIT_FAILURE);
        }
        
        if(race_control->position[id-1] == LAST){
            last1 = aleat_num(1, 6);
            last2 = aleat_num(1, 6);
            the_throw = last1+last2;
        }else if(race_control->position[id-1] == FIRST){
            the_throw = aleat_num(1, 7);
        }else{
            the_throw = aleat_num(1, 6);
        }
        
        race_control->current_box[id-1] += the_throw;
        race_control->last_throw[id-1] = the_throw;
        race_control->horses_done++;
        if(race_control->horses_done == n_horses){
            kill(getppid(), SIGUSR2);
        }
        usleep(150000);
        if(Up_Semaforo(semid, RACECONTROL_SEM, 0) == ERROR){
            perror("Error levantando el semaforo de control de carrera en un caballo");
            Borrar_Semaforo(semid);
            exit(EXIT_FAILURE);
        }
        pause();
    }
    exit(EXIT_SUCCESS);
}

void handler_SIGUSR1_bettor(int sig){
    flag_bettor=1; /* Proceso acabado */
    return;
}

void handler_SIGUSR2(int sig){
    return;
}

void handler_SIGINT(int sig){
    int k;
    for(k=0; k<n_proc; k++){
        kill(pids[k], SIGINT);
    }
    msgctl(msgid, IPC_RMID, NULL);
    shmdt(market_rates);
    shmctl(memid_market, IPC_RMID, NULL);
    shmdt(race_control);
    shmctl(memid_race, IPC_RMID, NULL);
    Borrar_Semaforo(semid);
    free(pids);
    exit(EXIT_SUCCESS);
}

void* window_function(void* arg){
    int window_id = *((int*)arg);
    struct msgbuf rcv={0};
    int j;
    float auxiliar_rate;
    FILE *f=NULL;
    
    srand(time(NULL) + getpid());
    
    while(!flag_window){
        usleep(300000);
        if(msgrcv(msgid, (struct msgbuf *)&rcv, sizeof(rcv.info), 1, 0) == ERROR){
            if(errno == EIDRM || errno == EINTR){ /* Las apuestas han acabado */
                exit(EXIT_SUCCESS);
            }else{ /* Error */
                perror("Error recibiendo un mensaje en una ventanilla de apuestas");
                exit(EXIT_FAILURE);
            }
        }
        
        /* Comprobamos el caballo y hacemos las actualizaciones necesarias */
        if(rcv.info.betting.horse_id > 0 && rcv.info.betting.horse_id <= n_horses){
            /* Bajando semaforo de proteccion de memoria compartida
             *  para las cotizaciones de los caballos */
            if(Down_Semaforo(semid, MARKET_SEM, 0) == ERROR){ 
                printf("Error bajando el semaforo de las cotizaciones en una ventanilla.\n");
                Borrar_Semaforo(semid);
                exit(EXIT_FAILURE);
            }
            
            auxiliar_rate = market_rates->horse_rate[rcv.info.betting.horse_id-1];
            /* Actualizamos cotizaciones de cada caballo */
            market_rates->horse_bet[rcv.info.betting.horse_id-1] += rcv.info.betting.bet;
            market_rates->total += rcv.info.betting.bet;
            for(j=0; j<n_horses; j++){
                market_rates->horse_rate[j] = market_rates->total / market_rates->horse_bet[j];
            }
            
            if(Up_Semaforo(semid, MARKET_SEM, 0) == ERROR){ 
                perror("Error subiendo el semaforo de las cotizaciones en una ventanilla.");
                Borrar_Semaforo(semid);
                exit(EXIT_FAILURE);
            }
            
            
            /* Bajando semaforo de proteccion de memoria compartida
             *  para las cotizaciones de los caballos */
            if(Down_Semaforo(semid, FILE_SEM, 0) == ERROR){ 
                perror("Error bajando el semaforo del fichero de registro de apuestas.");
                Borrar_Semaforo(semid);
                exit(EXIT_FAILURE);
            }
            
            f = (FILE*) fopen(BETFILE, "a");
            if(!f){
                perror("Error abriendo el fichero de registro de apuestas en una ventanilla");
                Up_Semaforo(semid, FILE_SEM, 0);
                exit(EXIT_FAILURE);
            }
            fprintf(f, "%d %d %d %f %f\n", rcv.info.betting.bettor_id, window_id+1, rcv.info.betting.horse_id, auxiliar_rate, rcv.info.betting.bet);
            fclose(f);
            
            if(Up_Semaforo(semid, FILE_SEM, 0) == ERROR){ 
                perror("Error subiendo el semaforo de las cotizaciones en una ventanilla.");
                Borrar_Semaforo(semid);
                exit(EXIT_FAILURE);
            }
        }
    }
    return NULL;
}


void classification(int *current, int *position, int len){
    int *aux=NULL;
    int i,j, flag=0;
    int tmp;
    
    for(i=1; i<len; i++){
        if(current[i] != current[i-1]){
            flag = 1;
            break;
        } 
    }
    if(!flag){
        for(j=0; j<len; j++){
            position[j] = FIRST;
        }
        return;
    }
    
    aux = (int*) malloc(len*sizeof(int));
    if(!aux){
        perror("Error al reservar el array auxiliar a la hora de actualizar la clasificacion");
        exit(EXIT_FAILURE);
    }
    
    for(i=0; i<len; i++){
        aux[i] = current[i];
    }
    
    i=FIRST;
    while(!checked(aux, len)){
        tmp = aux[0];
        for(j=1; j<len; j++){
            if(aux[j] > tmp) {
                tmp = aux[j];
            }
        }
        for(j=0; j<len; j++){
            if(current[j] == tmp){
                position[j] = i;
                aux[j] = -1;
            }
        }
        i++;
    }
    tmp = position[0];
    for(j=1; j<len; j++){
        if(position[j]>tmp){
            tmp = position[j];
        } 
    }
    
    for(j=0; j<len; j++){
        if(position[j] == tmp){
            position[j] = LAST;
        }
    }
    free(aux);
}

int checked(int *array, int len){
    int i;
    for(i=0; i<len; i++){
        if(array[i]!=-1) return 0;
    }
    return 1;
}

int finished(int *array, int len, int racelen){
    int i;
    for(i=0; i<len; i++){
        if(array[i] >= racelen) return 1;
    }
    return 0;
}


void calculate_bet_results(int *winners, int n_winners, int n_bettor){
    FILE *fbets=NULL, *fbettors=NULL;
    int i, current_bettor;
    float total_bet, total_won, profit;
    char buffer[BUFFER_SIZE], name[NAME_SIZE], aux[NAME_SIZE];
    int bettor_id, window_id, horse_id;
    float price, amount_bet;
    
    
    fbettors = (FILE *) fopen(BETTORFILE, "w");
    if(!fbettors){
        perror("Error abriendo el fichero de resultados de los apostadores");
        fclose(fbets);
        exit(EXIT_FAILURE);
    }
    fprintf(fbettors, "Nombre_Apostador  Cantidad_Total_Apostada  Ganancias_Totales  Beneficios_Netos\n");
    syslog(LOG_NOTICE, "Nombre_Apostador  Cantidad_Total_Apostada  Ganancias_Totales  Beneficios_Netos");
    
    for(current_bettor=1; current_bettor<=n_bettor; current_bettor++){
        total_bet=0;
        total_won=0;
        
        fbets = (FILE *) fopen(BETFILE, "r");
        if(!fbets){
            perror("Error abriendo el fichero de apuestas para mostrar los mejores apostadores");
            exit(EXIT_FAILURE);
        }
    
        fgets(buffer, BUFFER_SIZE, fbets);
        while(!feof(fbets)){
            fgets(buffer, BUFFER_SIZE, fbets);
            sscanf(buffer, "%d %d %d %f %f\n", &bettor_id, &window_id, &horse_id, &price, &amount_bet);
            if(bettor_id == current_bettor){
                total_bet += amount_bet;
                for(i=0; i<n_winners; i++){
                    if(winners[i] == horse_id){
                        total_won += (amount_bet * price);
                    }
                }
            }
        }
        profit = total_won - total_bet;
        memset(name, 0, NAME_SIZE);
        strcpy(name, "Apostador-");
        sprintf(aux, "%d", current_bettor);
        strcat(name, aux);
        fprintf(fbettors, "%s %f %f %f\n", name, total_bet, total_won, profit);
        syslog(LOG_NOTICE, "%s %f %f %f\n", name, total_bet, total_won, profit);
        fclose(fbets);
    }
    
    fclose(fbettors);
}


void print_best_bettors(int n_bettor){
    FILE *fbettors=NULL;
    int *profits = NULL;
    char **names=NULL;
    char buffer[BUFFER_SIZE], name[NAME_SIZE], best_name[NAME_SIZE];
    int j, k;
    float best_profit, bet_amount, won_amount, profit;
    
    profits = (int*) malloc(n_bettor*sizeof(int));
    if(!profits){
        perror("Error reservando memoria para los mejores beneficios");
        exit(EXIT_FAILURE);
    }
    names = (char **) malloc(n_bettor*sizeof(char *));
    if(!names){
        perror("Error reservando memoria para los nombres de los mejores apostadores");
        free(profits);
        exit(EXIT_FAILURE);
    }
    for(j=0; j<n_bettor; j++){
        names[j] = (char *) malloc(NAME_SIZE * sizeof(char));
        if(!names[j]){
            perror("Error reservando memoria para el nombre");
            for(k=0; k<j; k++){
                free(names[k]);
            }
            free(names);
            free(profits);
            exit(EXIT_FAILURE);
        }
    }
    
    fbettors = (FILE *) fopen(BETTORFILE, "r");
    if(!fbettors){
        perror("Error abriendo el fichero de resultados de los apostadores para mostrar a los mejores");
        exit(EXIT_FAILURE);
    }
    fgets(buffer, BUFFER_SIZE, fbettors);
    j=0;
    while(j<n_bettor){
        fgets(buffer, BUFFER_SIZE, fbettors);
        sscanf(buffer, "%s %f %f %f", name, &bet_amount, &won_amount, &profit);
        profits[j] = profit;
        memset(names[j], 0, NAME_SIZE);
        strcpy(names[j], name);
        j++;
    }
    fclose(fbettors);
    
    printf("\n\t--> LISTA DE MEJORES APOSTADORES:\n");
    syslog(LOG_NOTICE, "--> LISTA DE MEJORES APOSTADORES");
    
    for(j=0; j<N_BEST_BETTOR; j++){
        strcpy(best_name, names[0]);
        best_profit = profits[0];
        for(k=1; k<n_bettor; k++){
            if(profits[k] > best_profit){
                best_profit = profits[k];
                strcpy(best_name, names[k]);
            }
        }
        printf("%d - %s con unos beneficios netos de %f\n", j+1, best_name, best_profit);
        syslog(LOG_NOTICE, "%d - %s con unos beneficios netos de %f\n", j+1, best_name, best_profit);
        for(k=0; k<n_bettor; k++){
            if(profits[k] == best_profit){
                profits[k] = INT_MIN;
            }
        }
    }
    
    for(k=0; k<n_bettor; k++){
        free(names[k]);
    }
    free(names);
    free(profits);
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
         return 0;
      }
    }
    if(!atoi(input)){
      return 0;
   }
   return 1;
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


float float_rand( float min, float max ){
    float scale = rand() / (float) RAND_MAX; /* [0, 1.0] */
    return min + scale * ( max - min );      /* [min, max] */
}

void init_syslog(){
    setlogmask (LOG_UPTO (LOG_NOTICE));
    openlog ("Proyecto_final_SOPER_logger", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
}
