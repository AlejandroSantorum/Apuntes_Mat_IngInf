/***************************************************************************
File: practica2.c
Project: Assignment 2 Communication Networks I
Authors:
	- Alejandro Santorum Varela - alejandro.santorum@estudiante.uam.es
	- David Cabornero Pascual - david.cabornero@estudiante.uam.es
Date: 10-11-2018
***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pcap.h>
#include <string.h>
#include <netinet/in.h>
#include <linux/udp.h>
#include <linux/tcp.h>
#include <signal.h>
#include <time.h>
#include <getopt.h>
#include <inttypes.h>
#include "practica2.h"

#define NO_LIMIT -1 /* No package limit at pcap_loop function */
#define ETH_FRAME_MAX 1514 /* Ethernet trace maximum size */
#define READ_TIMEOUT 100 /* Read timeout in miliseconds for pcap_open_live function */
#define MAX_NUM_INPUT_PAR 11 /* Maximum number of input parameters */
#define MIN_NUM_INPUT_PAR 3 /* Minimum number of input parameters */
#define OK 0
#define ERROR 1
#define PACK_ERROR -1 /* pcap_loop function returns an error handling the packages */
#define BREAKLOOP -2 /* pcap_loop function finishes because of breakloop function */
#define IP_ALEN 4 /* IPv4 - IP address size */
#define NO_FILTER 0
#define ACTIVE_FILTER 1
#define FORWARD_1BYTE 1
#define DISPLACE_1BYTE 8
#define ETH_ALEN 6 /* Number of bytes of Ethernet Address */
#define ETHTYPE_IPv4 0x0800 /* Ethernet type for IPv4 */
#define IHL_LEN 4 /* IHL length in bits */
#define IHL 4 /* IHL indicates the header length in 32 bit word (32 bits = 4 bytes) */
#define SERVTYPE_LEN 8 /* Service type length in bits */
#define FRAG_OFFSET_CONST 8 /* The fragmentation offset is always a multiple of 8 (last 3 bits of 16 are 0)*/
#define TCP_DECIMAL_VALUE 6 /* TCP decimal value */
#define UDP_DECIMAL_VALUE 17 /* UDP decimal value */
#define SEQUENCE_NUM_LEN 4 /* TCP sequence number length in bytes */
#define ACKNOWLEDGEMENT_NUM_LEN 4 /* TCP acknowledgement number length in bytes */

/** Global variables */
/** They are useful if we know what they exactly do */
int flag_offline = 0, flag_live = 0;
int flag_ipsrc = NO_FILTER, flag_ipdst = NO_FILTER, flag_srcport = NO_FILTER, flag_dstport = NO_FILTER;
pcap_t *descr=NULL;
uint64_t counter = 0;
uint8_t ipsrc_filter[IP_ALEN] = {NO_FILTER};
uint8_t ipdst_filter[IP_ALEN] = {NO_FILTER};
uint16_t srcport_filter = NO_FILTER;
uint16_t dstport_filter = NO_FILTER;


int main(int argc, char **argv){
	char errbuf[PCAP_ERRBUF_SIZE];
	int ret;

	if(signal(SIGINT, signal_handler) == SIG_ERR) {
		printf("ERROR: Fallo al capturar la senal SIGINT.\n");
		exit(ERROR);
	}

	input_parameter_checking(argc, argv);

	if(flag_ipsrc == ACTIVE_FILTER){
		printf("Filtro IP_Origen: ");
		printf("%"PRIu8".%"PRIu8".%"PRIu8".%"PRIu8"\n", ipsrc_filter[0], ipsrc_filter[1], ipsrc_filter[2], ipsrc_filter[3]);
	}
	if(flag_ipdst == ACTIVE_FILTER){
		printf("Filtro IP_Destino: ");
		printf("%"PRIu8".%"PRIu8".%"PRIu8".%"PRIu8"\n", ipdst_filter[0], ipdst_filter[1], ipdst_filter[2], ipdst_filter[3]);
	}
	if(flag_srcport == ACTIVE_FILTER){
		printf("Filtro Puerto_Origen: ");
		printf("%"PRIu16"\n", srcport_filter);
	}
	if(flag_dstport == ACTIVE_FILTER){
		printf("Filtro Puerto_Destino: ");
		printf("%"PRIu16"\n", dstport_filter);
	}

	if(flag_live){
		/* Interface opening */
		if ((descr = pcap_open_live(argv[2], ETH_FRAME_MAX, 0, READ_TIMEOUT, errbuf)) == NULL){
			printf("Error: pcap_open_live(): %s, %s %d.\n",errbuf,__FILE__,__LINE__);
			exit(ERROR);
		}
	}
	else if(flag_offline){
		/* Trace analysis */
		if((descr = pcap_open_offline(argv[2], errbuf)) == NULL){
			printf("Error: pcap_open_offline(): %s, %s, %d.\n", errbuf, __FILE__, __LINE__);
			exit(ERROR);
		}
	}
	else{ /* This error has been already treated, but it helps to endure the code even more */
		printf("ERROR: Ni lectura de interfaz ni analisis de trama han sido seleccionadas\n");
		exit(ERROR);
	}


	ret = pcap_loop(descr, NO_LIMIT, package_treat, NULL);
	switch(ret){
		case OK:
			printf("\nTraza leida con exito\n");
			break;
		case PACK_ERROR:
			printf("\nERROR leyendo paquetes con la funcion pcap_loop()\n");
			break;
		case BREAKLOOP:
			printf("\npcap_breakloop llamado y ha terminado con la ejecucion de pcap_loop\n");
			break;
	}

	printf("NUMERO DE PAQUETES PROCESADOS: %"PRIu64"\n", counter);
	pcap_close(descr);

	return 0;
}


void input_parameter_checking(int argc, char **argv){
	int j;

	if(argc < MIN_NUM_INPUT_PAR){ /* Minimum parameter number not reached */
		invalid_input_message();
		printf("\t(*) -> Número de parámetros de entrada por debajo del mínimo\n");
		exit(ERROR);
	}
	if(argc > MAX_NUM_INPUT_PAR){ /* Maximum parameter number reached */
		invalid_input_message();
		printf("\t(*) -> Número de parámetros de entrada por encima del máximo permitido\n");
		exit(ERROR);
	}
	if(!(argc%2)){ /* Even number of parameters */
		invalid_input_message();
		printf("\t(*) -> El número de parámetros de entrada es par cuando esto no es posible\n");
		exit(ERROR);
	}
	for(j=1; j<argc; j+=2){ /* There is at least one wrong flag */
		if(strcmp(argv[j],"-i") && strcmp(argv[j],"-f") && strcmp(argv[j],"-ipo") && strcmp(argv[j],"-ipd") && strcmp(argv[j],"-po") && strcmp(argv[j],"-pd")){
			invalid_input_message();
			printf("\t(*) -> Compruebe que todos los indicadores (-i, -f, -ipo, -ipd, -po o -pd) son los especificados\n");
			exit(ERROR);
		}
	}

	if(!strcmp(argv[1], "-i")){
		/* Checking that there is no other interface or file to be opened */
		for(j=3; j<argc; j++){
			if(!strcmp(argv[j],"-f") || !strcmp(argv[j],"-i")){
				invalid_input_message();
				printf("\t(*) -> No se admite leer de interfaz y fichero en la misma ejecución (son excluyentes)\n");
				exit(ERROR);
			}
		}
		flag_live = 1; /* The user wants to read from interface */
	}
	else if(!strcmp(argv[1], "-f")){
		/* Checking that there is no other interface or file to be opened */
		for(j=3; j<argc; j++){
			if(!strcmp(argv[j],"-f") || !strcmp(argv[j],"-i")){
				invalid_input_message();
				printf("\t(*) -> No se admite leer de interfaz y fichero en la misma ejecución (son excluyentes)\n");
				exit(ERROR);
			}
		}
		flag_offline = 1; /* The user wants to read a pcap file */
	}
	else{
		invalid_input_message();
		printf("\t(*) -> El primer parámetro debe ser un fichero .pcap o la interfaz\n");
		exit(ERROR);
	}

	for(j=3; j<argc; j+=2){
		if(!strcmp(argv[j], "-ipo")){ /* Source IP Address */
			if(sscanf(argv[j+1], "%"SCNu8".%"SCNu8".%"SCNu8".%"SCNu8"",  &(ipsrc_filter[0]), &(ipsrc_filter[1]), &(ipsrc_filter[2]), &(ipsrc_filter[3])) != IP_ALEN){
				invalid_input_message();
				printf("(*) -> Compruebe que el filtro IP_Origen se ha introducido con el formato A.B.C.D con A,B,C,D en [0,255]\n");
				exit(ERROR);
			}
			if(flag_ipsrc == ACTIVE_FILTER){
				invalid_input_message();
				printf("(*) -> No se pueden introducir dos filtros IP_Origen\n");
				exit(ERROR);
			}	
			flag_ipsrc = ACTIVE_FILTER;
		}
		else if(!strcmp(argv[j], "-ipd")){ /* Destination IP Address */
			if(sscanf(argv[j+1], "%"SCNu8".%"SCNu8".%"SCNu8".%"SCNu8"",  &(ipdst_filter[0]), &(ipdst_filter[1]), &(ipdst_filter[2]), &(ipdst_filter[3])) != IP_ALEN){
				invalid_input_message();
				printf("(*) -> Compruebe que el filtro IP_Destino se ha introducido con el formato A.B.C.D con A,B,C,D en [0,255]\n");
				exit(ERROR);
			}
			if(flag_ipdst == ACTIVE_FILTER){
				invalid_input_message();
				printf("(*) -> No se pueden introducir dos filtros IP_Destino\n");
				exit(ERROR);
			}
			flag_ipdst = ACTIVE_FILTER;
		}
		else if(!strcmp(argv[j], "-po")){ /* Source port */
			if(!(sscanf(argv[j+1], "%"SCNu16"", &srcport_filter))){
				invalid_input_message();
				printf("(*) -> Compruebe que el filtro Puerto_Origen se ha introducido correctamente\n");
				exit(ERROR);
			}
			if(flag_srcport == ACTIVE_FILTER){
				invalid_input_message();
				printf("(*) -> No se pueden introducir dos filtros Puerto_Origen\n");
				exit(ERROR);
			}
			flag_srcport = ACTIVE_FILTER;
		}
		else if(!strcmp(argv[j], "-pd")){ /* Destination port */
			if(!(sscanf(argv[j+1], "%"SCNu16"", &dstport_filter))){
				invalid_input_message();
				printf("(*) -> Compruebe que el filtro Puerto_Destino se ha introducido correctamente\n");
				exit(ERROR);
			}
			if(flag_dstport == ACTIVE_FILTER){
				invalid_input_message();
				printf("(*) -> No se pueden introducir dos filtros Puerto_Destino\n");
				exit(ERROR);
			}
			flag_dstport = ACTIVE_FILTER;
		}
		else{
			invalid_input_message();
			printf("(*) -> Error inesperado: compruebe los parametros de entrada\n");
			exit(ERROR);
		}
	}
	return;
}


void package_treat(u_char *user, const struct pcap_pkthdr *header, const uint8_t *pack){
	int i;
	uint16_t aux;
	uint32_t auxl;
	uint8_t ipsrc[IP_ALEN];
	uint8_t ipdst[IP_ALEN];

	(void)user; /* Indicating to the compiler that the variable is not used */

	if(!pack){ /* NULL pointer */
		printf("ERROR: Pack NULL pointer in package_treat function\n");
		pcap_close(descr);
		exit(ERROR);
	}

	counter++;
	printf("\n---> NUEVO PAQUETE (nº %"PRIu64") capturado el %s", counter, ctime((const time_t *) &(header->ts.tv_sec)));

	/* --------------------------- LINK LEVEL ANALYSIS ------------------------------------------------------------------ */
	printf("\tANALISIS DE NIVEL DE ENLACE (NIVEL 2):\n");

	printf("Direccion Ethernet Destino = ");
	printf("%02x", pack[0]);
	for(i=1; i<ETH_ALEN; i++){
		printf("-%02x", pack[i]);
	}
	printf("\n");

	pack += ETH_ALEN;

	printf("Direccion Ethernet Origen = ");
	printf("%02x", pack[0]);
	for(i=1; i<ETH_ALEN; i++){
		printf("-%02x", pack[i]);
	}
	printf("\n");

	pack += ETH_ALEN;

	aux = ntohs(*(uint16_t*)pack);
	printf("Tipo Ethernet = %04x\n", aux);
	pack += 2*FORWARD_1BYTE;

	if(aux != ETHTYPE_IPv4){ /* Ethernet type is not IPv4 */
		printf("El siguiente protocolo no se corresponde con un protocolo IPv4.\nFinalizamos analisis de este paquete\n");
		return;
	}
	/* ------------------------------------------------------------------------------------------------------------------ */
	/* -------------------------- NETWORK LEVEL ANALYSIS ---------------------------------------------------------------- */
	printf("\tANALISIS DE NIVEL DE RED IP (NIVEL 3):\n");

	aux = ntohs(*(uint16_t*)pack);
	printf("Version = %"PRIu16"\n", (aux & 0xf000) >> (IHL_LEN+SERVTYPE_LEN)); /* first 4 bits mask + 8 bit displace */

	printf("Valor del campo Longitud Cabecera = %"PRIu16"\n", (aux & 0x0f00) >> SERVTYPE_LEN); /* 0x0f00 mask + 8 bit displace */
	printf("Longitud de Cabecera real (interpretando el valor del campo) = %"PRIu16"\n", ((aux & 0x0f00) >> SERVTYPE_LEN)*IHL);

	pack += 2*FORWARD_1BYTE;
	aux = ntohs(*(uint16_t*)pack);
	printf("Logitud Total = %"PRIu16"\n", aux);

	pack += (4*FORWARD_1BYTE); /* Identification is not printed */
	aux = ntohs(*(uint16_t*)pack);
	uint16_t frag_offset = 0;
	printf("Valor campo desplazamiento en decimal = %"PRIu16"\n", (frag_offset = (aux & 0x1fff)));
	printf("Desplazamiento real (interpretando el valor del campo) = %"PRIu16"\n", frag_offset*FRAG_OFFSET_CONST);

	pack += 2*FORWARD_1BYTE;
	aux = ntohs(*(uint16_t*)pack);
	printf("Tiempo de vida = %"PRIu16"\n", (aux & 0xff00) >> DISPLACE_1BYTE);
	uint8_t protocol = 0;
	printf("Protocolo = %"PRIu16"\n", (protocol = (aux & 0x00ff)));

	pack += (4*FORWARD_1BYTE); /* Checksum is not printed */
	auxl = ntohl(*(uint32_t*)pack);
	ipsrc[0] = (auxl & 0xff000000) >> 3*DISPLACE_1BYTE;
	ipsrc[1] = (auxl & 0x00ff0000) >> 2*DISPLACE_1BYTE;
	ipsrc[2] = (auxl & 0x0000ff00) >> DISPLACE_1BYTE;
	ipsrc[3] = auxl & 0x000000ff;
	printf("Direccion IP Origen = %"PRIu8".%"PRIu8".%"PRIu8".%"PRIu8"\n", ipsrc[0], ipsrc[1], ipsrc[2], ipsrc[3]);
	if(flag_ipsrc == ACTIVE_FILTER){
		if(ipsrc_filter[0]!=ipsrc[0] || ipsrc_filter[1]!=ipsrc[1] || ipsrc_filter[2]!=ipsrc[2] || ipsrc_filter[3]!=ipsrc[3]){
			printf("Esta direccion IP de origen no ha superado el filtrado deseado\n");
			printf("Filtro IP Origen introducido: %"PRIu16".%"PRIu16".%"PRIu16".%"PRIu16"\n", ipsrc_filter[0], ipsrc_filter[1], ipsrc_filter[2], ipsrc_filter[3]);
			printf("Finalizamos analisis de este paquete\n");
			return;
		}
	}

	pack += (4*FORWARD_1BYTE);
	auxl = ntohl(*(uint32_t*)pack);
	ipdst[0] = (auxl & 0xff000000) >> 3*DISPLACE_1BYTE;
	ipdst[1] = (auxl & 0x00ff0000) >> 2*DISPLACE_1BYTE;
	ipdst[2] = (auxl & 0x0000ff00) >> DISPLACE_1BYTE;
	ipdst[3] = auxl & 0x000000ff;
	printf("Direccion IP Destino = %"PRIu8".%"PRIu8".%"PRIu8".%"PRIu8"\n", ipdst[0], ipdst[1], ipdst[2], ipdst[3]);
	if(flag_ipdst == ACTIVE_FILTER){
		if(ipdst_filter[0]!=ipdst[0] || ipdst_filter[1]!=ipdst[1] || ipdst_filter[2]!=ipdst[2] || ipdst_filter[3]!=ipdst[3]){
			printf("Esta direccion IP de destino no ha superado el filtrado deseado\n");
			printf("Filtro IP Destino introducido: %"PRIu16".%"PRIu16".%"PRIu16".%"PRIu16"\n", ipdst_filter[0], ipdst_filter[1], ipdst_filter[2], ipdst_filter[3]);
			printf("Finalizamos analisis de este paquete\n");
			return;
		}
	}

	if(frag_offset != 0){
		printf("Desplazamiento distinto de cero, este paquete no contiene la cabecera de nivel 4\n");
		printf("Finalizamos analisis de este paquete\n");
		return;
	}

	if(protocol != UDP_DECIMAL_VALUE && protocol != TCP_DECIMAL_VALUE){
		printf("El siguiente protocolo no se corresponde con el protocolo UDP o TCP.\nFinalizamos con el analisis de este paquete\n");
		return;
	}
	/* ------------------------------------------------------------------------------------------------------------------ */
	/* ------------------------- TRANSPORT LEVEL ANALYSIS --------------------------------------------------------------- */
	if(protocol == TCP_DECIMAL_VALUE) printf("\tANALISIS DE NIVEL DE TRANSPORTE TCP (NIVEL 4):\n");
	else printf("\tANALISIS DE NIVEL DE TRANSPORTE UDP(NIVEL 4):\n"); /* Already checked that lvl 4 protocol is TCP or UDP */

	pack += (4*FORWARD_1BYTE);
	aux = ntohs(*(uint16_t*)pack);
	printf("Puerto Origen =  %"PRIu16"\n", aux);
	if(flag_srcport == ACTIVE_FILTER){
		if(srcport_filter != aux){
			printf("Este puerto origen no ha superado el filtro deseado\n");
			printf("Filtro puerto origen introducido: %"PRIu16"\n", srcport_filter);
			printf("Finalizamos analisis del este paquete\n");
			return;
		}
	}

	pack += 2*FORWARD_1BYTE;
	aux = ntohs(*(uint16_t*)pack);
	printf("Puerto Destino =  %"PRIu16"\n", aux);
	if(flag_dstport == ACTIVE_FILTER){
		if(dstport_filter != aux){
			printf("Este puerto destino no ha superado el filtro deseado\n");
			printf("Filtro puerto destino introducido: %"PRIu16"\n", dstport_filter);
			printf("Finalizamos analisis del este paquete\n");
			return;
		}
	}

	if(protocol == TCP_DECIMAL_VALUE){ /* TCP ANALYSIS */
		pack += (2*FORWARD_1BYTE + SEQUENCE_NUM_LEN + ACKNOWLEDGEMENT_NUM_LEN);
		aux = ntohs(*(uint16_t*)pack);
		printf("Bandera SYN = %d\n", (aux & 0x0002) >> 1);
		printf("Bandera FIN = %d\n", aux & 0x0001);
	}
	else if(protocol == UDP_DECIMAL_VALUE){ /* UDP ANALYSIS */
		pack += 2*FORWARD_1BYTE;
		aux = ntohs(*(uint16_t*)pack);
		printf("Campo Longitud = %"PRIu16"\n", aux);
	}

	return;
}


void invalid_input_message(){
	printf("ERROR: Parámetros de entrada no válidos\n");
	printf("\tParámetros obligatorios: <-f ficheroPcap/ -i interfaz> (excluyentes entre ellos)\n");
	printf("\tParámetros opcionales: [-ipo IP_Origen] [-ipd IP_Destino] [-po Puerto_Origen] [-pd Puerto_Destino]\n");
}


void signal_handler(int nsignal){
	(void) nsignal; /* Telling the compiler this variable is not used on purpose */
	printf("--> Control C pulsado <--\n");
	pcap_breakloop(descr);
}
