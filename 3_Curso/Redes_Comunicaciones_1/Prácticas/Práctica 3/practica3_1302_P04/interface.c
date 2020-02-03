/***************************************************************************
 interface.c
 Funciones necesarias en la practica 3 para extraer la configuracion de interface/socket/enlace
 
 Autor: Jose Luis Garcia Dorado
 2018 EPS-UAM 
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "interface.h"

int sock=-1 ;		//socket auxiliar

/****************************************************************************************
 * Nombre: solicitudARP                                                                 *
 * Descripcion: Devuelve en retorno la direccion Ethernet dada una direccion IP         *
 * Argumentos:                                                                          *
 *  -interface: nombre de la interface (p.ej: "eth0")                                   *
 *  -IP: Direccion IP en orden de red                                                   *
 *  -retorno: Direccion Ethernet asignada a la interface en orden de red                *
 * Retorno: OK/ERROR                                                                    *
 ****************************************************************************************/
uint8_t solicitudARP(char* interface, uint8_t* IP, uint8_t* retorno){
	char comando[255]; char linea[255]; char ETH_destino_aux[100]; char IP_char[16];
	FILE *f;
	sprintf(IP_char,"%"SCNu8".%"SCNu8".%"SCNu8".%"SCNu8"",IP[0],IP[1],IP[2],IP[3]);
	if(IP==NULL || interface==NULL)
		return ERROR;
	sprintf(comando,"arping %s -I %s -c 6",IP_char,interface);
	f = popen(comando, "r");
	if(f == NULL){
		printf("Error ejecutando el comando: %s\n",comando);
		return ERROR;
	}
	fgets(linea,255,f);
	if(linea==NULL)
		return ERROR;
	fgets(linea,255,f);
	if(linea==NULL)
		return ERROR;
	fgets(linea,255,f);
	if(linea==NULL)
		return ERROR;
	pclose(f);
	if(sscanf(linea,"%*s %*s %*s %*s [%s %*s\n",ETH_destino_aux)<1){
		printf("Error ejecutando el comando: %s\n",comando);
		return ERROR;
	}
	ETH_destino_aux[strlen((char*)ETH_destino_aux)-1]=0;
	if(sscanf(ETH_destino_aux,"%"SCNx8":%"SCNx8":%"SCNx8":%"SCNx8":%"SCNx8":%"SCNx8"" ,retorno,retorno+1,retorno+2,retorno+3,retorno+4,retorno+5)<ETH_ALEN){
		printf("La dirección IP a traducir es inalcanzable (Puede ser problemas de configuración de la subred o que no responda): %s\n",comando);
		return ERROR;
	}
	printf("Retorno solicitudARP(%s):\n",IP_char);
	printf("\t%02"PRIx8":%02"PRIx8":%02"PRIx8":%02"PRIx8":%02"PRIx8":%02"PRIx8"\n",
		retorno[0],retorno[1],retorno[2],retorno[3],retorno[4],retorno[5]);
	return OK;
}


/****************************************************************************************
 * Nombre: obtenerMACdeInterface                                                        *
 * Descripcion: Devuelve en retorno la direccion Ethernet de una interface              *
 * Argumentos:                                                                          *
 *  -interface: nombre de la interface (p.ej: "eth0")                                   *
 *  -retorno: Direccion Ethernet en orden de red                                        *
 * Retorno: OK/ERROR                                                                    *
 ****************************************************************************************/
uint8_t obtenerMACdeInterface(char* interface, uint8_t* retorno){
	 int fd;
	 struct ifreq ifr;
	 fd = socket(AF_INET, SOCK_DGRAM, 0);
	 if(fd<0) {
		printf("socket_ERROR\n");
		return ERROR;
	}
	ifr.ifr_addr.sa_family = AF_INET;
	strncpy(ifr.ifr_name, interface, IFNAMSIZ-1);
	if (ioctl(fd, SIOCGIFHWADDR, &ifr)<0){
		printf("IOCTL_ERROR\n");
		return ERROR;
	}
	close(fd);
	memcpy(retorno,ifr.ifr_hwaddr.sa_data,sizeof(uint8_t)*6);
	printf("Retorno obtenerMACdeInterface():\n");
	printf("\t%02"PRIx8":%02"PRIx8":%02"PRIx8":%02"PRIx8":%02"PRIx8":%02"PRIx8"\n",
		retorno[0],retorno[1],retorno[2],retorno[3],retorno[4],retorno[5]);
	return OK;
}


/****************************************************************************************
 * Nombre: obtenerMascaraInterface                                                      *
 * Descripcion: Devuelve en retorno la mascara de red de una interface                  *
 * Argumentos:                                                                          *
 *  -interface: nombre de la interface (p.ej: "eth0")                                   *
 *  -retorno: Mascara de red en orden de red                                            *
 * Retorno: OK/ERROR                                                                    *
 ****************************************************************************************/
uint8_t obtenerMascaraInterface(char* interface, uint8_t* retorno){
	 int fd;
	 struct ifreq ifr;
	 fd = socket(AF_INET, SOCK_DGRAM, 0);
	 if(fd<0) {
		printf("socket_ERROR\n");
		return ERROR;
	}
	ifr.ifr_addr.sa_family = AF_INET;
	strncpy(ifr.ifr_name, interface, IFNAMSIZ-1);
	if (ioctl(fd, SIOCGIFNETMASK, &ifr)<0){
		printf("IOCTL_ERROR\n");
		return ERROR;
	}
	close(fd);
	memcpy(retorno,&(*(struct sockaddr_in *)&ifr.ifr_netmask).sin_addr,sizeof(uint8_t)*IP_ALEN);
	printf("Retorno obtenerMascaraInterface():\n");
	printf("\t%"PRIu8".%"PRIu8".%"PRIu8".%"PRIu8"\n",retorno[0],retorno[1],retorno[2],retorno[3]);
	return OK;
}


/****************************************************************************************
 * Nombre: obtenerMTUInterface                                                          *
 * Descripcion: Devuelve en retorno la MTU del nivel anterio al fisco (enlace)          *
 * Argumentos:                                                                          *
 *  -interface: nombre de la interface (p.ej: "eth0")                                   *
 *  -retorno: MTU en orden de hardware                                                  *
 * Retorno: OK/ERROR                                                                    *
 ****************************************************************************************/
uint8_t obtenerMTUInterface(char* interface, uint16_t* retorno){
	int fd;
	struct ifreq ifr;
	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(fd<0) {
		printf("socket_ERROR\n");
		return ERROR;
	}
	ifr.ifr_addr.sa_family = AF_INET;
	strncpy(ifr.ifr_name, interface, IFNAMSIZ-1);
	if (ioctl(fd, SIOCGIFMTU, &ifr)<0){
		printf("IOCTL_ERROR\n");
		return ERROR;
	}
	close(fd);
	*retorno=ifr.ifr_mtu;
	printf("Retorno obtenerMTUInterface():\n");
	printf("\tMTU=%"PRIu16"\n",*retorno);
	return OK;
}


/****************************************************************************************
 * Nombre: obtenerIPInterface                                                           *
 * Descripcion: Esta funcion devuelve en retorno la IP asignada a una interface         *
 * Argumentos:                                                                          *
 *  -interface: nombre de la interface (p.ej: "eth0")                                   *
 *  -retorno: IP asignada a la interface en orden de red                                *
 * Retorno: OK/ERROR                                                                    *
 ****************************************************************************************/
uint8_t obtenerIPInterface(char * interface, uint8_t* retorno){
	int fd;
	struct ifreq ifr;
	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(fd<0) {
		printf("socket_ERROR\n");
		return ERROR;
	}
	ifr.ifr_addr.sa_family = AF_INET;
	strncpy(ifr.ifr_name, interface, IFNAMSIZ-1);
	if (ioctl(fd, SIOCGIFADDR, &ifr)<0){
		printf("IOCTL_ERROR\n");
		return ERROR;
	}
	close(fd);
	memcpy(retorno,&(*(struct sockaddr_in *)&ifr.ifr_addr).sin_addr,sizeof(uint8_t)*IP_ALEN);
	printf("Retorno obtenerIPInterface():\n");
	printf("\t%"PRIu8".%"PRIu8".%"PRIu8".%"PRIu8"\n",retorno[0],retorno[1],retorno[2],retorno[3]);
	return OK;
}


/****************************************************************************************
 * Nombre: obtenerGateway                                                               *
 * Descripcion: Esta funcion devuelve en retorno el gateway dada una interface          *
 * Argumentos:                                                                          *
 *  -interface: nombre de la interface (p.ej: "eth0")                                   *
 *  -retorno: direccion IP del gateway en orden de red                                  *
 * Retorno: OK/ERROR                                                                    *
 ****************************************************************************************/
uint8_t obtenerGateway(char * interface, uint8_t* retorno){
	char comando[255]; char linea[255];
	FILE *f;
	if(retorno==NULL || interface==NULL)
		return ERROR;
	sprintf(comando,"netstat -rn | grep '^\\(default\\|0\\.0\\.0\\.0\\)' | grep %s | awk '{print $2}'",interface);
//printf("Comando en ejecucion: %s\n",comando);
	f = popen(comando, "r");
	if(f == NULL){
		printf("Error ejecutando el comando: %s\n",comando);
		return ERROR;
	}
	fgets(linea,255,f);
	//sscanf(linea,"%s\n",retorno);
	if(sscanf(linea,"%"SCNu8".%"SCNu8".%"SCNu8".%"SCNu8"\n" ,retorno,retorno+1,retorno+2,retorno+3)<IP_ALEN){
		printf("La direccion IP a traducir es inalcanzable (puede ser problemas de configuracion de la subred o que el equipo no responda): %s\n",comando);
		return ERROR;
	}
	pclose(f);
	printf("Retorno obtenerGateway():\n");
	printf("\t%"PRIu8".%"PRIu8".%"PRIu8".%"PRIu8"\n",retorno[0],retorno[1],retorno[2],retorno[3]);
	return OK;
}


/****************************************************************************************
 * Nombre: obtenerPuertoOrigen                                                          *
 * Descripcion: Devuelve en retorno un puerto origen disponible                         *
 * Argumentos:                                                                          *
 *  -puerto: puerto disponible en orden hardware                                        *
 * Retorno: OK/ERROR                                                                    *
 ****************************************************************************************/
uint8_t obtenerPuertoOrigen(uint16_t* puerto){
	struct sockaddr_in  sock_addr;
   	int c;
    	fd_set rfds;   
	sock = socket( AF_INET, SOCK_DGRAM, 0 );
	if(sock == -1){
		perror("El socket no pudo ser creado !\n");
		return ERROR;
	}
	c=1;
	setsockopt( sock, SOL_SOCKET, SO_REUSEADDR, (char *)&c, sizeof(c) );
	FD_ZERO(&rfds);
	FD_SET(sock, &rfds);
	bzero((char *)&sock_addr,sizeof(sock_addr));
	sock_addr.sin_family=AF_INET;
	if(bind(sock, (struct sockaddr *)&sock_addr, sizeof(sock_addr) )==-1){
		perror("El socket no pudo ser enlazado a un puerto libre !\n");
		return ERROR;
	} 
	socklen_t addrlen=sizeof(sock_addr);
	if(getsockname(sock, (struct sockaddr *)&sock_addr, &addrlen)==0)
		*puerto=ntohs(sock_addr.sin_port);
	else{
		*puerto=0;
		return ERROR;
	}
	close(sock);
	sock=-1;
	printf("Retorno obtenerPuertoOrigen():\n");
	printf("\t%"PRIu16"\n",*puerto);
	return OK;
}
