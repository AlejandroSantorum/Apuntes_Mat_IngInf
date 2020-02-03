/***************************************************************************
 interface.h
 Definiciones y cabeceras para interface.c
 
 Autor: Jose Luis Garcia Dorado
 2018 EPS-UAM 
***************************************************************************/

#ifndef __INTERFACE_H
#define __INTERFACE_H

/***************************Funciones extraer configuracion interface/socket/enlace*************/
#include <stdio.h>
#include <stdlib.h>

#include <pcap.h>
#include <string.h>
#include <netinet/in.h>
#include <linux/udp.h>
#include <linux/tcp.h>
#include <signal.h>
#include <time.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <netinet/ether.h>
#include <netinet/if_ether.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <math.h>
#include "practica3.h"

uint8_t obtenerPuertoOrigen(uint16_t* puerto);
uint8_t obtenerMACdeInterface(char* interface, uint8_t* MAC);
uint8_t obtenerMascaraInterface(char* interface, uint8_t* retorno);
uint8_t obtenerIPInterface(char* interface, uint8_t* retorno);
uint8_t obtenerGateway(char* interface, uint8_t* retorno);
uint8_t solicitudARP(char* interface, uint8_t* IP, uint8_t* retorno);
uint8_t obtenerMTUInterface(char* interface, uint16_t* retorno);

#endif
