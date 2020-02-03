/***************************************************************************
 practica3.c
 Inicio, funciones auxiliares y modulos de transmision implmentados y a implementar de la practica 4.
Compila con warning pues falta usar variables y modificar funciones

 Compila: make
 Autor: Jose Luis Garcia Dorado, Jorge E. Lopez de Vergara Mendez
 2018 EPS-UAM v1
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "interface.h"
#include "practica3.h"

/***************************Variables globales utiles*************************************************/
pcap_t* descr, *descr2; //Descriptores de la interface de red
pcap_dumper_t * pdumper;//y salida a pcap
uint64_t cont=0;	//Contador numero de mensajes enviados
char interface[10];	//Interface donde transmitir por ejemplo "eth0"
uint16_t ID=0;		//Identificador IP
char flag_mostrar = 0;

uint8_t _rangos_coincidentes(uint8_t* rango_origen, uint8_t* rango_destino, uint8_t longitud);

void handleSignal(int nsignal){
	printf("Control C pulsado (%"PRIu64")\n", cont);
	pcap_close(descr);
	exit(OK);
}

int main(int argc, char **argv){

	char errbuf[PCAP_ERRBUF_SIZE];
	char fichero_pcap_destino[CADENAS];
	uint8_t IP_destino_red[IP_ALEN];
	uint16_t MTU;
	uint16_t datalink;
	uint16_t puerto_destino;
	char data[IP_DATAGRAM_MAX];
	uint16_t pila_protocolos[CADENAS];
	int n_char=0;

	int long_index=0;
	char opt;
	char flag_iface = 0, flag_ip = 0, flag_port = 0, flag_file = 0, flag_dontfrag = 0;

	static struct option options[] = {
		{"if",required_argument,0,'1'},
		{"ip",required_argument,0,'2'},
		{"pd",required_argument,0,'3'},
		{"f",required_argument,0,'4'},
		{"d",no_argument,0,'5'},
		{"m",no_argument,0,'6'},
		{"h",no_argument,0,'7'},
		{0,0,0,0}
	};

		//Dos opciones: leer de stdin o de fichero, adicionalmente para pruebas si no se introduce argumento se considera que el mensaje es "Payload "
	while ((opt = getopt_long_only(argc, argv,"1:2:3:4:5:6:7", options, &long_index )) != -1) {
		switch (opt) {
			case '1' :
				flag_iface = 1;
				//Por comodidad definimos interface como una variable global
				sprintf(interface,"%s",optarg);
				break;
				
			case '2' :
				flag_ip = 1;
				//Leemos la IP a donde transmitir y la almacenamos en orden de red
				if (sscanf(optarg,"%"SCNu8".%"SCNu8".%"SCNu8".%"SCNu8"",
				                   &(IP_destino_red[0]),&(IP_destino_red[1]),&(IP_destino_red[2]),&(IP_destino_red[3])) != IP_ALEN){
					printf("Error: Fallo en la lectura IP destino %s\n", optarg);
					exit(ERROR);
				}
				break;

			case '3' :
				flag_port = 1;
				//Leemos el puerto a donde transmitir y la almacenamos en orden de hardware
				puerto_destino=atoi(optarg);
				break;

			case '4' :
				if(strcmp(optarg,"stdin")==0) {
					if (fgets(data, sizeof(data), stdin)==NULL) {
						printf("Error leyendo desde stdin: %s %s %d.\n",errbuf,__FILE__,__LINE__);
						return ERROR;
					}
					n_char = strlen(data);
					if(n_char % 2){ //Deben ser pares!
                        data[n_char-1] = 0; /* El \n final es prescindible */
                        n_char--;
                    }
					sprintf(fichero_pcap_destino,"%s%s","stdin",".pcap");
				} else {
					sprintf(fichero_pcap_destino,"%s%s",optarg,".pcap");
                    char c;
                    FILE *f=NULL;
                    f = (FILE *) fopen(optarg, "rb");
                    if(!f){
                        printf("Error abriendo el fichero de datos: %s %s %d.\n", errbuf, __FILE__, __LINE__);
                        return ERROR;
                    }
                    while(!feof(f)){
                        c = fgetc(f);
                        data[n_char] = c;
                        n_char++;
                    }
                    if(n_char % 2){ //Deben ser pares!
                        data[n_char-1] = 0; /* El EOF final es prescindible si después hay un \0 */
                        n_char--;
                    }
				}
				flag_file = 1;
				break;

			case '5' :
				flag_dontfrag =1; // El usuario solicita que los paquetes se envien con el bit DF=1.
				break;

			case '6' :
				flag_mostrar =1; // El usuario solicita que se muestren en hexadecimal las tramas enviadas.
				break;

			case '7' : printf("Ayuda. Ejecucion: %s -if interface -ip direccion_IP -pd puerto [-f /ruta/fichero_a_transmitir o stdin] [-d] [-m]: %d\n",argv[0],argc); exit(ERROR);
				break;

			case '?' :
			default: printf("Error. Ejecucion: %s -if interface -ip direccion_IP -pd puerto [-f /ruta/fichero_a_transmitir o stdin] [-d] [-m]: %d\n",argv[0],argc); exit(ERROR);
				break;
        }
    }

	if ((flag_iface == 0) || (flag_ip == 0) || (flag_port == 0)){
		printf("Error. Ejecucion: %s -if interface -ip direccion_IP -pd puerto [-f /ruta/fichero_a_transmitir o stdin] [-d] [-m]: %d\n",argv[0],argc);
		exit(ERROR);
	} else {
		printf("Interface:\n\t%s\n",interface);
		printf("IP:\n\t%"PRIu8".%"PRIu8".%"PRIu8".%"PRIu8"\n",IP_destino_red[0],IP_destino_red[1],IP_destino_red[2],IP_destino_red[3]);
		printf("Puerto destino:\n\t%"PRIu16"\n",puerto_destino);
		if (flag_dontfrag) printf("Se solicita enviar paquete con bit DF=1\n");
		if (flag_mostrar) printf("Se solicita mostrar las tramas enviadas en hexadecimal\n");
	}

	if (flag_file == 0) {
		sprintf(data,"%s","Payload "); //Deben ser pares!
		sprintf(fichero_pcap_destino,"%s%s","debugging",".pcap");
		n_char = strlen(data);
	}

	if(signal(SIGINT,handleSignal)==SIG_ERR){
		printf("Error: Fallo al capturar la senal SIGINT.\n");
		return ERROR;
	}
	//Inicializamos las tablas de protocolos
	if(inicializarPilaEnviar()==ERROR){
      	printf("Error leyendo desde stdin: %s %s %d.\n",errbuf,__FILE__,__LINE__);
		return ERROR;
	}
	//Leemos el tamano maximo de transmision del nivel de enlace
	if(obtenerMTUInterface(interface, &MTU)==ERROR)
		return ERROR;
	//Descriptor de la interface de red donde inyectar trafico
	if ((descr = pcap_open_live(interface,MTU+ETH_HLEN,0, 0, errbuf)) == NULL){
		printf("Error: pcap_open_live(): %s %s %d.\n",errbuf,__FILE__,__LINE__);
		return ERROR;
	}

	datalink=(uint16_t)pcap_datalink(descr); //DLT_EN10MB==Ethernet

	//Descriptor del fichero de salida pcap para debugging
	descr2=pcap_open_dead(datalink,MTU+ETH_HLEN);
	pdumper=pcap_dump_open(descr2,fichero_pcap_destino);

	//Formamos y enviamos el trafico, debe enviarse un unico segmento por llamada a enviar() aunque luego se traduzca en mas de un datagrama
	//Primero, un paquete ICMP; en concreto, un ping
	pila_protocolos[0]=ICMP_PROTO; pila_protocolos[1]=IP_PROTO; pila_protocolos[2]=ETH_PROTO;
	Parametros parametros_icmp; parametros_icmp.tipo=PING_TIPO; parametros_icmp.codigo=PING_CODE; parametros_icmp.bit_DF=flag_dontfrag; memcpy(parametros_icmp.IP_destino,IP_destino_red,IP_ALEN);
	if(enviar((uint8_t*)ICMP_DATA,strlen(ICMP_DATA),pila_protocolos,&parametros_icmp)==ERROR ){
		printf("Error: enviar(): %s %s %d.\n",errbuf,__FILE__,__LINE__);
		return ERROR;
	}
	else	cont++;
	printf("Enviado mensaje %"PRIu64", ICMP almacenado en %s\n\n", cont,fichero_pcap_destino);
	
	//Luego, un paquete UDP
	//Definimos la pila de protocolos que queremos seguir
	pila_protocolos[0]=UDP_PROTO; pila_protocolos[1]=IP_PROTO; pila_protocolos[2]=ETH_PROTO;
	//Rellenamos los parametros necesario para enviar el paquete a su destinatario y proceso
	Parametros parametros_udp; memcpy(parametros_udp.IP_destino,IP_destino_red,IP_ALEN); parametros_udp.bit_DF=flag_dontfrag; parametros_udp.puerto_destino=puerto_destino;
	//Enviamos
	if(enviar((uint8_t*)data,n_char,pila_protocolos,&parametros_udp)==ERROR ){
		printf("Error: enviar(): %s %s %d.\n",errbuf,__FILE__,__LINE__);
		return ERROR;
	}
	else	cont++;

	printf("Enviado mensaje %"PRIu64", almacenado en %s\n\n\n", cont,fichero_pcap_destino);

	//Cerramos descriptores
	pcap_close(descr);
	pcap_dump_close(pdumper);
	pcap_close(descr2);
	return OK;
}


/****************************************************************************************
 * Nombre: enviar                                                                       *
 * Descripcion: Esta funcion envia un mensaje                                           *
 * Argumentos:                                                                          *
 *  -mensaje: mensaje a enviar                                                          *
 *  -pila_protocolos: conjunto de protocolos a seguir                                   *
 *  -longitud: bytes que componen mensaje                                               *
 *  -parametros: parametros necesario para el envio (struct parametros)                 *
 * Retorno: OK/ERROR                                                                    *
 ****************************************************************************************/

uint8_t enviar(uint8_t* mensaje, uint32_t longitud,uint16_t* pila_protocolos,void *parametros){
	uint16_t protocolo=pila_protocolos[0];
	printf("Enviar(%"PRIu16") %s %d.\n",protocolo,__FILE__,__LINE__);
	if(protocolos_registrados[protocolo]==NULL){
		printf("Protocolo %"PRIu16" desconocido\n",protocolo);
		return ERROR;
	}
	else {
		return protocolos_registrados[protocolo](mensaje,longitud,pila_protocolos,parametros);
	}
	return ERROR;
}


/***************************TODO Pila de protocolos a implementar************************************/


/****************************************************************************************
 * Nombre: moduloICMP                                                                   *
 * Descripcion: Esta funcion implementa el modulo de envio ICMP                         *
 * Argumentos:                                                                          *
 *  -mensaje: mensaje a anadir a la cabecera ICMP                                       *
 *  -longitud: bytes que componen el mensaje                                            *
 *  -pila_protocolos: conjunto de protocolos a seguir                                   *
 *  -parametros: parametros necesario para el envio este protocolo                      *
 * Retorno: OK/ERROR                                                                    *
 ****************************************************************************************/

uint8_t moduloICMP(uint8_t* mensaje, uint32_t longitud, uint16_t* pila_protocolos, void *parametros){
	uint8_t segmento[ICMP_DATAGRAM_MAX]={0};
	uint8_t aux8, aux8p[2];
	uint16_t aux16;
	uint32_t pos=0, CHKSpos;
	uint8_t protocolo_inferior=pila_protocolos[1];
	printf("modulo ICMP(%"PRIu16") %s %d.\n",protocolo_inferior,__FILE__,__LINE__);

	/* Type */
	aux8=PING_TIPO; /* Tambien podriamos sacarlo de la estructura de parametros */
	memcpy(segmento+pos, &aux8, sizeof(uint8_t));
	pos+=sizeof(uint8_t);
	/* Code */
	aux8=PING_CODE; /* Tambien podriamos sacarlo de la estructura de parametros */
	memcpy(segmento+pos, &aux8, sizeof(uint8_t));
	pos+=sizeof(uint8_t);
	/* Checksum */
	aux16=0;
	memcpy(segmento+pos, &aux16, sizeof(uint8_t));
	CHKSpos = pos;
	pos+=sizeof(uint16_t);
	/* Identifier */
    aux16=htons((uint16_t) getpid());
    memcpy(segmento+pos, &aux16, sizeof(uint16_t));
    pos+=sizeof(uint16_t);
	/* Sec number */
    aux16=htons((uint16_t) 1);
    memcpy(segmento+pos, &aux16, sizeof(uint16_t));
    pos+=sizeof(uint16_t);
    /* Copiando el mensaje en el campo datos de la cabecera ICMP */
    memcpy(segmento+pos, mensaje, longitud*sizeof(uint8_t));
    /* calculando e introduciendo el checksum */
    if(calcularChecksum(segmento, pos+longitud, aux8p) == ERROR){
        printf("Error calculando el checksum en el modulo ICMP\n");
        return ERROR;
    }
    memcpy(segmento+CHKSpos, aux8p, sizeof(uint16_t));

	return protocolos_registrados[protocolo_inferior](segmento,longitud+pos,pila_protocolos,parametros);
}


/****************************************************************************************
 * Nombre: moduloUDP                                                                    *
 * Descripcion: Esta funcion implementa el modulo de envio UDP                          *
 * Argumentos:                                                                          *
 *  -mensaje: mensaje a enviar                                                          *
 *  -longitud: bytes que componen mensaje                                               *
 *  -pila_protocolos: conjunto de protocolos a seguir                                   *
 *  -parametros: parametros necesario para el envio este protocolo                      *
 * Retorno: OK/ERROR                                                                    *
 ****************************************************************************************/

uint8_t moduloUDP(uint8_t* mensaje, uint32_t longitud, uint16_t* pila_protocolos, void *parametros){
	uint8_t segmento[UDP_SEG_MAX]={0};
	uint16_t puerto_origen = 0, udp_checksum=0;
	uint16_t aux16;
	uint32_t pos=0;
	uint8_t protocolo_inferior=pila_protocolos[1];
	printf("modulo UDP(%"PRIu16") %s %d.\n",protocolo_inferior,__FILE__,__LINE__);
	
	/* Control de tamanio */
	if (longitud>UDP_SEG_MAX){
		printf("Error: mensaje demasiado grande para UDP (%d).\n",UDP_SEG_MAX);
		return ERROR;
	}
	/* UDP Parameters */
	Parametros udpdatos=*((Parametros*)parametros);
	uint16_t puerto_destino=udpdatos.puerto_destino;
	/* Source port */
    if(obtenerPuertoOrigen(&puerto_origen) == ERROR){
        printf("Error obteniendo el Puerto origen en el moduloUDP\n");
        return ERROR;
    }
	aux16=htons(puerto_origen);
	memcpy(segmento+pos,&aux16,sizeof(uint16_t));
	pos+=sizeof(uint16_t);
	/* Dest port */
    aux16=htons(puerto_destino);
    memcpy(segmento+pos, &aux16, sizeof(uint16_t));
    pos+=sizeof(uint16_t);
	/* Length */
    aux16=htons((uint16_t) UDP_HLEN+longitud);
    memcpy(segmento+pos, &aux16, sizeof(uint16_t));
    pos+=sizeof(uint16_t);
	/* Checksum */
    aux16=htons((uint16_t) udp_checksum);
    memcpy(segmento+pos, &aux16, sizeof(uint16_t));
    pos+=sizeof(uint16_t);
	/* Data */
    memcpy(segmento+pos, mensaje, longitud*sizeof(uint8_t));
    
	return protocolos_registrados[protocolo_inferior](segmento,longitud+pos,pila_protocolos,parametros);
}


/****************************************************************************************
 * Nombre: moduloIP                                                                     *
 * Descripcion: Esta funcion implementa el modulo de envio IP                           *
 * Argumentos:                                                                          *
 *  -segmento: segmento a enviar                                                        *
 *  -longitud: bytes que componen el segmento                                           *
 *  -pila_protocolos: conjunto de protocolos a seguir                                   *
 *  -parametros: parametros necesario para el envio este protocolo                      *
 * Retorno: OK/ERROR                                                                    *
 ****************************************************************************************/

uint8_t moduloIP(uint8_t* segmento, uint32_t longitud, uint16_t* pila_protocolos, void *parametros){
	uint8_t datagrama[IP_DATAGRAM_MAX]={0};
	uint16_t aux16, mtu;
	uint8_t aux8, aux8p[2];
	uint8_t IP_origen[IP_ALEN];
	uint8_t protocolo_superior=pila_protocolos[0];
	uint8_t protocolo_inferior=pila_protocolos[2];
	pila_protocolos++;
	uint8_t mascara[IP_ALEN],IP_rango_origen[IP_ALEN],IP_rango_destino[IP_ALEN], IP_router[IP_ALEN];

	printf("modulo IP(%"PRIu16") %s %d.\n",protocolo_inferior,__FILE__,__LINE__);
	/* IP Parameters */
	Parametros ipdatos=*((Parametros*)parametros);
	uint8_t* IP_destino=ipdatos.IP_destino;
	
	if(obtenerMTUInterface(interface, &mtu) == ERROR){
        printf("Error obteniendo MTU en el modulo IP\n");
        return ERROR;
    }
    if(longitud > (mtu-IP_HLEN_MIN) && ipdatos.bit_DF==1){
		/* Fragmentation is not allowed (DF = 1) */
        printf("Error: mensaje demasiado grande para no poder ser fragmentado en el modulo IP (%s %d).\n", __FILE__, __LINE__);
        return ERROR;
    }
	/* Obtenemos direccion IP origen */
	if(obtenerIPInterface(interface, IP_origen) == ERROR){
		printf("Error obteniendo IP origen en el moduloIP\n");
		return ERROR;
    }
    /* Obtenemos direccion ETH origen y destino y las introducimos en la estructura de parametros */
    if(obtenerMascaraInterface(interface, mascara) == ERROR){
        printf("Error obteniendo la mascara en el modulo IP\n");
        return ERROR;
    }
    if(aplicarMascara(IP_origen, mascara, IP_ALEN, IP_rango_origen) == ERROR){
        printf("Error aplicando la mascara en la IP origen en el modulo IP\n");
        return ERROR;
    }
    if(aplicarMascara(IP_destino, mascara, IP_ALEN, IP_rango_destino) == ERROR){
        printf("Error aplicando la mascara en la IP destino en el modulo IP\n");
        return ERROR;
    }
		
    if(_rangos_coincidentes(IP_rango_origen, IP_rango_destino, IP_ALEN)){
        if(solicitudARP(interface, IP_destino, ipdatos.ETH_destino) == ERROR){
            printf("Error en la solicitud ARP en la misma subred en el modulo IP\n");
            return ERROR;
        }
    }else{
        if(obtenerGateway(interface, IP_router) == ERROR){
            printf("Error obteniendo el Getaway en el modulo IP\n");
            return ERROR;
        }
        if(solicitudARP(interface, IP_router, ipdatos.ETH_destino) == ERROR){
            printf("Error en la solicitud ARP al router en el modulo IP\n");
            return ERROR;
        }
    }
    /* Creacion de cabeceras IP para cada uno de los posibles fragmentos */
    int data_frag_index = 0;
    int length;
    uint16_t aux;
    ID++;
    while(longitud != data_frag_index){
		aux16=0;
        int more_frag = 1;
        uint32_t pos = 0;
        /* Version & IHL */
        aux8 = IP_VERSION << 4;
        aux8 += (0x0f & IHL_MIN);
        memcpy(datagrama+pos, &aux8, sizeof(uint8_t));
        pos += sizeof(uint8_t);
        /* Service type */
        aux8 = 0;
        memcpy(datagrama+pos, &aux8, sizeof(uint8_t));
        pos += sizeof(uint8_t);
        /* Total length */
        if(longitud - data_frag_index > IP_MAXDATA){
            aux16 = htons((uint16_t)IP_MAXDATA+IP_HLEN_MIN);
            memcpy(datagrama+pos, &aux16, sizeof(uint16_t));
            pos += sizeof(uint16_t);
        }
        else{
            aux16 = htons((uint16_t)((longitud-data_frag_index)+IP_HLEN_MIN));
            memcpy(datagrama+pos, &aux16, sizeof(uint16_t));
            pos += sizeof(uint16_t);
            more_frag = 0;
        }
        /* Identifier */
        aux16 = htons((uint16_t) ID);
        memcpy(datagrama+pos, &aux16, sizeof(uint16_t));
        pos += sizeof(uint16_t);
        /* Flags & Fragment offset */
        aux16 = (uint16_t)(2*ipdatos.bit_DF + more_frag);
        aux16 = aux16 << IP_FLAGS_DISPLACE;
        aux = (uint16_t) data_frag_index/8;
        aux16 += (0x1fff & aux);
        aux16 = htons(aux16);
        memcpy(datagrama+pos, &aux16, sizeof(uint16_t));
        pos += sizeof(uint16_t);
        /* Time to Live */
        aux8 = IP_LIFETIME;
        memcpy(datagrama+pos, &aux8, sizeof(uint8_t));
        pos += sizeof(uint8_t);
        /* Protocol */
        aux8 = protocolo_superior;
        memcpy(datagrama+pos, &aux8, sizeof(uint8_t));
        pos += sizeof(uint8_t);
        /* Checksum */
        aux16 = 0;
        memcpy(datagrama+pos, &aux16, sizeof(uint16_t));
        pos += sizeof(uint16_t);
        /* IP Source Address */
        memcpy(datagrama+pos, IP_origen, IP_ALEN*sizeof(uint8_t));
        pos += sizeof(uint32_t);
        /* IP Dest Adderess */
        memcpy(datagrama+pos, IP_destino, IP_ALEN*sizeof(uint8_t));
        pos += sizeof(uint32_t);
        /* Checksum II */
        if(calcularChecksum(datagrama, pos, aux8p) == ERROR){
            printf("Error calculando el checksum en el modulo ICMP\n");
            return ERROR;
        }
        memcpy(datagrama+IP_CHECKSUM_POS, aux8p, sizeof(uint16_t));
        /* Data */
        if(longitud - data_frag_index > IP_MAXDATA){
            memcpy(datagrama+pos, segmento+data_frag_index, IP_MAXDATA);
            data_frag_index += IP_MAXDATA;
            length = pos+IP_MAXDATA;
        }
        else{
            length = longitud-data_frag_index;
            memcpy(datagrama+pos, segmento+data_frag_index, length);
            data_frag_index = longitud;
            length += pos;
        }
        if(protocolos_registrados[protocolo_inferior](datagrama,length,pila_protocolos,(void*)(&ipdatos)) == ERROR){
            return ERROR;
        }
    }
    return OK;
}


/****************************************************************************************
 * Nombre: moduloETH                                                                    *
 * Descripcion: Esta funcion implementa el modulo de envio Ethernet                     *
 * Argumentos:                                                                          *
 *  -datagrama: datagrama a enviar                                                      *
 *  -longitud: bytes que componen el datagrama                                          *
 *  -pila_protocolos: conjunto de protocolos a seguir                                   *
 *  -parametros: Parametros necesario para el envio este protocolo                      *
 * Retorno: OK/ERROR                                                                    *
 ****************************************************************************************/

uint8_t moduloETH(uint8_t* datagrama, uint32_t longitud, uint16_t* pila_protocolos,void *parametros){
    uint8_t trama[ETH_FRAME_MAX]={0};
    uint16_t mtu=0, aux16;
    uint32_t pos=0;
    uint8_t ETH_origen[ETH_ALEN];

    printf("modulo ETH(fisica) %s %d.\n",__FILE__,__LINE__);

    Parametros ethdatos = *((Parametros*)parametros);

    /* Control de tamanio */
    if(obtenerMTUInterface(interface, &mtu) == ERROR){
        printf("Error obteniendo MTU en el modulo ETH\n");
        return ERROR;
    }
    if(longitud > mtu){
        printf("Error, la longitud del paquete supera el tamaño MTU (modulo ETH)\n");
        return ERROR;
    }

    /* Dest ETH Addr */
    memcpy(trama+pos, ethdatos.ETH_destino, ETH_ALEN*sizeof(uint8_t));
    pos += ETH_ALEN*sizeof(uint8_t);
	/* Source ETH Addr */
    if(obtenerMACdeInterface(interface, ETH_origen) == ERROR){
        printf("Error obteniendo la MAC origen en el modulo ETH\n");
        return ERROR;
    }
    memcpy(trama+pos, ETH_origen, ETH_ALEN*sizeof(uint8_t));
    pos += ETH_ALEN*sizeof(uint8_t);
	/* Ethernet type */
    aux16 = htons((uint16_t) ETHTYPE_IPv4);
    memcpy(trama+pos, &aux16, sizeof(uint16_t));
    pos += sizeof(uint16_t);
	/* Data */
    memcpy(trama+pos, datagrama, longitud);
    pos += longitud;
	/* Injection into physical level */
    if(pcap_inject(descr, trama, pos) == -1){
        printf("Error inyectando en la red con pcap_inject() en el modulo ETH\n");
        return ERROR;
    }
    /* Show trace */
    if(flag_mostrar){
		mostrarHex(trama, pos);
	}
	/* Dump to debug later */
    if(pdumper){
        struct timeval tvs;
        struct pcap_pkthdr pkt[1];

        gettimeofday(&tvs, NULL);

        pkt->ts.tv_sec = tvs.tv_sec;
        pkt->ts.tv_usec = tvs.tv_usec;
        pkt->len = pos;
        pkt->caplen = pos;

        pcap_dump((uint8_t *)pdumper, pkt, trama);
    }else{
        printf("Error al guardar el volcado en el dumper en el modulo ETH\n");
        return ERROR;
    }

	return OK;
}


uint8_t _rangos_coincidentes(uint8_t* rango_origen, uint8_t* rango_destino, uint8_t longitud){
    int i;
    for(i=0; i<longitud; i++){
        if(rango_origen[i] != rango_destino[i]){
            return 0;
        }
    }
    return 1;
}

/***************************Funciones auxiliares a implementar***********************************/

/****************************************************************************************
 * Nombre: aplicarMascara                                                               *
 * Descripcion: Esta funcion aplica una mascara a una vector                            *
 * Argumentos:                                                                          *
 *  -IP: IP a la que aplicar la mascara en orden de red                                 *
 *  -mascara: mascara a aplicar en orden de red                                         *
 *  -longitud: bytes que componen la direccion (IPv4 == 4)                              *
 *  -resultado: Resultados de aplicar mascara en IP en orden red                        *
 * Retorno: OK/ERROR                                                                    *
 ****************************************************************************************/
uint8_t aplicarMascara(uint8_t* IP, uint8_t* mascara, uint8_t longitud, uint8_t* resultado){
	int i;
	if(IP==NULL || mascara==NULL || resultado==NULL || longitud < 0){
		printf("Error: aplicarMascara(): entradas nulas.\n");
		return ERROR;
	}

	for(i=0; i<longitud; i++){
		resultado[i] = IP[i] & mascara[i];
	}
	return OK;
}


/***************************Funciones auxiliares implementadas**************************************/

/****************************************************************************************
 * Nombre: mostrarHex                                                                   *
 * Descripcion: Esta funcion imprime por pantalla en hexadecimal un vector              *
 * Argumentos:                                                                          *
 *  -datos: bytes que conforman un mensaje                                              *
 *  -longitud: Bytes que componen el mensaje                                            *
 * Retorno: OK/ERROR                                                                    *
 ****************************************************************************************/
uint8_t mostrarHex(uint8_t * datos, uint32_t longitud){
	uint32_t i;
	printf("Datos:\n");
	for (i=0;i<longitud;i++){
		printf("%02"PRIx8" ", datos[i]);
	}
	printf("\n");
	return OK;
}


/****************************************************************************************
 * Nombre: calcularChecksum                                                             *
 * Descripcion: Esta funcion devuelve el ckecksum tal como lo calcula IP/ICMP           *
 * Argumentos:                                                                          *
 *   -datos: datos sobre los que calcular el checksum                                   *
 *   -longitud: numero de bytes de los datos sobre los que calcular el checksum         *
 *   -checksum: checksum de los datos (2 bytes) en orden de red!                        *
 * Retorno: OK/ERROR                                                                    *
 ****************************************************************************************/
uint8_t calcularChecksum(uint8_t *datos, uint16_t longitud, uint8_t *checksum) {
    uint16_t word16;
    uint32_t sum=0;
    int i;
    // make 16 bit words out of every two adjacent 8 bit words in the packet
    // and add them up
    for (i=0; i<longitud; i=i+2){
        word16 = (datos[i]<<8) + datos[i+1];
        sum += (uint32_t)word16;
    }
    // take only 16 bits out of the 32 bit sum and add up the carries
    while (sum>>16) {
        sum = (sum & 0xFFFF)+(sum >> 16);
    }
    // one's complement the result
    sum = ~sum;
    checksum[0] = sum >> 8;
    checksum[1] = sum & 0xFF;
    return OK;
}


/***************************Funciones inicializacion implementadas*********************************/

/****************************************************************************************
 * Nombre: inicializarPilaEnviar                                                        *
 * Descripcion: inicializar la pila de red para enviar registrando los distintos modulos*
 * Retorno: OK/ERROR                                                                    *
 ****************************************************************************************/
uint8_t inicializarPilaEnviar() {
	bzero(protocolos_registrados,MAX_PROTOCOL*sizeof(pf_notificacion));
	if(registrarProtocolo(ETH_PROTO, moduloETH, protocolos_registrados)==ERROR){
		printf("No se ha podido registrar el protocolo Ethernet\n");
		return ERROR;
	}
	if(registrarProtocolo(IP_PROTO, moduloIP, protocolos_registrados)==ERROR){
		printf("No se ha podido registrar el protocolo IP\n");
		return ERROR;
	}
	if(registrarProtocolo(ICMP_PROTO, moduloICMP, protocolos_registrados)==ERROR){
		printf("No se ha podido registrar el protocolo ICMP\n");
		return ERROR;
	}
	if(registrarProtocolo(UDP_PROTO, moduloUDP, protocolos_registrados)==ERROR){
		printf("No se ha podido registrar el protocolo UDP\n");
		return ERROR;
	}

	return OK;
}


/****************************************************************************************
 * Nombre: registrarProtocolo                                                           *
 * Descripcion: Registra un protocolo en la tabla de protocolos                         *
 * Argumentos:                                                                          *
 *  -protocolo: Referencia del protocolo (ver RFC 1700)                                 *
 *  -handleModule: Funcion a llamar con los datos a enviar                              *
 *  -protocolos_registrados: vector de funciones registradas                            *
 * Retorno: OK/ERROR                                                                    *
 ****************************************************************************************/
uint8_t registrarProtocolo(uint16_t protocolo, pf_notificacion handleModule, pf_notificacion* protocolos_registrados){
	if(protocolos_registrados==NULL ||  handleModule==NULL){
		printf("Error: registrarProtocolo(): entradas nulas.\n");
		return ERROR;
	}
	else
		protocolos_registrados[protocolo]=handleModule;
	return OK;
}
