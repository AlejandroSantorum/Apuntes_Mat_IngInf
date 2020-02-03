/***************************************************************************
File: practica1.c
Project: Assignment 1 Communication Networks I
Authors:
	- Alejandro Santorum Varela - alejandro.santorum@estudiante.uam.es
	- David Cabornero Pascual - david.cabornero@estudiante.uam.es
Date: 17-10-2018
***************************************************************************/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <pcap.h>
#include <string.h>
#include <netinet/in.h>
#include <linux/udp.h>
#include <linux/tcp.h>
#include <signal.h>
#include <time.h>
#include <ctype.h>
#include <stdint.h>
#include <inttypes.h>

#include "practica1.h"


#define ERROR 1
#define OK 0
#define ETH_FRAME_MAX 1514	//Ethernet trace maximum size
#define SIZE 256
#define N_MINS 30

/** Global variables */
/** They are useful if we know what they exactly do */
pcap_t *descr=NULL,*descr2=NULL;
pcap_dumper_t *pdumper=NULL;
int counter=0, n_args=-1;


int main(int argc, char **argv)
{
	int N_bytes, ret=0, sup_lim=0;
	char errbuf[PCAP_ERRBUF_SIZE];
	char file_name[SIZE];
	struct timeval time;

	if(argc!=2 && argc!=3){ /* Input parameter error */
		printf("\nERROR --> PARAMETROS DE ENTRADA NO VALIDOS:\n\n");
		printf("\t·Opcion 1-Captura de interfaz\n");
		printf("\t\t-arg1 -> N_bytes: numero de primeros bytes a capturar de cada paquete\n\n");
		printf("\t·Opcion 2-Analizar traza ya guardada\n");
		printf("\t\t-arg1 -> N_bytes: numero de primeros bytes a analizar de cada paquete\n");
		printf("\t\t-arg2 -> Nombre: nombre del archivo .pcap de la traza a analizar\n\n");
		exit(ERROR);
	}

	if(is_valid_integer(argv[1]) == ERROR){ /* Checking that the first input parameter is truly an integer */
		printf("ERROR --> Primer parametro de entrada (numero de primeros bytes a capturar/analizar)\nno se corresponde con un entero\n");
		exit(ERROR);
	}

	n_args = argc; /* Global variable, useful to check error cases */
	N_bytes = atoi(argv[1]); /* Number of bytes that are getting printed */


	if(signal(SIGINT,handle)==SIG_ERR){
		printf("Error: Fallo al capturar la senal SIGINT.\n");
		exit(ERROR);
	}

	if(argc == 2){ /* CASE 1: TRACE CAPTURE */
		if(N_bytes > ETH_FRAME_MAX){
			/* The number of bytes that the user wants to print is bigger than
		 	the number of bytes that we are saving */
			N_bytes = ETH_FRAME_MAX;
			sup_lim = 1; /* Auxiliary variable to warn the user that we are limiting the printed bytes */
		}

		/* Interface opening */
		if ((descr = pcap_open_live("eth0", ETH_FRAME_MAX,0,100, errbuf)) == NULL){
			printf("Error: pcap_open_live(): %s, %s %d.\n",errbuf,__FILE__,__LINE__);
			exit(ERROR);
		}

		/* Trace dump */
		descr2=pcap_open_dead(DLT_EN10MB,ETH_FRAME_MAX);
		if (!descr2){
			printf("Error al abrir el dump.\n");
			pcap_close(descr);
			exit(ERROR);
		}
		gettimeofday(&time,NULL);
		sprintf(file_name,"eth0.%lld.pcap",(long long)time.tv_sec);
		pdumper=pcap_dump_open(descr2,file_name);
		if(!pdumper){
			printf("Error al abrir el dumper: %s, %s %d.\n",pcap_geterr(descr2),__FILE__,__LINE__);
			pcap_close(descr);
			pcap_close(descr2);
			exit(ERROR);
		}
	}else if(argc == 3){ /*CASE 2: TRACE ANALYSIS ALREADY SAVED */
		if((descr = pcap_open_offline(argv[2], errbuf)) == NULL){
			printf("Error: pcap_open_offline(): %s, %s, %d.\n", errbuf, __FILE__, __LINE__);
			exit(ERROR);
		}
	}

	ret = pcap_loop (descr,-1,package_treat, (uint8_t*)&N_bytes);
	if(ret == -1){ 		//En caso de error
		printf("Error al capturar un paquete %s, %s %d.\n",pcap_geterr(descr),__FILE__,__LINE__);
		pcap_close(descr);
		if(pdumper){
			pcap_dump_close(pdumper);
		}
		if(descr2){
			pcap_close(descr2);
		}
		exit(ERROR);
	}
	else if(ret==-2 && counter<=0){ /* Pcap_breakloop error */
		printf("Llamada a %s %s %d.\n","pcap_breakloop()",__FILE__,__LINE__);
	}
	else if(ret == 0){
		printf("No mas paquetes o limite superado %s %d.\n",__FILE__,__LINE__);
	}

	printf("NUMERO DE PAQUETES CAPTURADOS/ANALIZADOS = %d\n", counter);

	if(sup_lim){
		printf("CUIDADO: El numero de bytes que se quieren mostrar es mayor que el numero maximo de bytes que se guardan\n");
	}

	if(pdumper){
		pcap_dump_close(pdumper);
	}
	if(descr2){
		pcap_close(descr2);
	}
	pcap_close(descr);

	return OK;
}


void handle(int nsignal){
	printf("Control C pulsado\n");
	if(descr)
		pcap_breakloop(descr);
}


void package_treat(uint8_t *user, const struct pcap_pkthdr* header, const uint8_t* package){
	struct pcap_pkthdr* header_mod;
	int* N_bytes = (int*) user;
	int j=0, min=0;

	header_mod = (struct pcap_pkthdr*) header;
	counter++;
	printf("\n(%d) - Nuevo paquete capturado a las %s",counter, ctime((const time_t*)&(header->ts.tv_sec)));
	header_mod->ts.tv_sec = header->ts.tv_sec + 60*N_MINS;
	header_mod->len = header->len;
	header_mod->caplen = header->caplen;
	printf("(%d) - Paquete guardado como capturado a las %s", counter, ctime((time_t*)&(header_mod->ts.tv_sec)));

	/* Checking if the package size is smaller than the number of bytes that the user wants to print */
	if(header_mod->len < (*N_bytes)){
		min = header_mod->len;
	}else{
		min = (*N_bytes);
	}

	for(j=0; j<min; j++){
		printf("%02"PRIx8" ", package[j]);
	}
	printf("\n");

	if(n_args == 2){
		if(pdumper){
			pcap_dump((uint8_t *)pdumper,header_mod,package);
		}else{
			printf("Error al guardar el volcado en el dumper\n");
		}
	}
}


int is_valid_integer(char *input){
	int len, i;
	if(!input){
		printf("Error. Input igual a NULL\n");
		exit(ERROR);
	}
	len = strlen(input);
	for(i=0; i<len; i++){
		if(!isdigit(input[i])){
			return ERROR;
		}
	}
	if(!atoi(input)){
		return ERROR;
	}
	return OK;
}
