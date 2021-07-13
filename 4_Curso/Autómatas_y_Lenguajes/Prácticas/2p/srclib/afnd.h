#ifndef AFND_H
#define AFND_H

#include <stdio.h>

#define INICIAL	0
#define FINAL	1
#define INICIAL_Y_FINAL	2
#define NORMAL 3

typedef struct _AFND AFND;


AFND * AFNDNuevo(char * nombre, int num_estados, int num_simbolos);
void AFNDElimina(AFND * p_afnd);
void AFNDImprime(FILE * fd, AFND* p_afnd);

int AFNDIndiceDeSimbolo(AFND * p_afnd, char * nombre);
int AFNDIndiceDeEstado(AFND * p_afnd, char * nombre);
char * AFNDNombreEstadoEn(AFND * p_afnd, int pos);
char * AFNDSimboloEn(AFND * p_afnd, int pos);

AFND * AFNDInsertaSimbolo(AFND * p_afnd, char * simbolo);
AFND * AFNDInsertaEstado(AFND * p_afnd, char * nombre, int tipo);
AFND * AFNDInsertaTransicion(AFND * p_afnd, char * nombre_estado_i, char * nombre_simbolo_entrada, char * nombre_estado_f );
AFND * AFNDInsertaLTransicion(AFND * p_afnd, char * nombre_estado_i, char * nombre_estado_f );

AFND * AFNDInsertaLetra(AFND * p_afnd, char * letra);
void  AFNDImprimeConjuntoEstadosActual(FILE * fd, AFND * p_afnd);
void AFNDImprimeCadenaActual(FILE *fd, AFND * p_afnd);
void AFNDTransita(AFND * p_afnd);
void AFNDProcesaEntrada(FILE * fd, AFND * p_afnd);


int AFNDIndiceEstadoInicial(AFND * p_afnd);
AFND * AFNDInicializaEstado (AFND * p_afnd);
AFND * AFNDInicializaCadenaActual (AFND * p_afnd);
AFND * AFNDCierraLTransicion (AFND * p_afnd);

int AFNDLTransicionIJ(AFND * p_afnd, int i , int j);

int AFNDTransicionIndicesEstadoiSimboloEstadof(AFND * p_afnd, int i_e1, int i_s, int i_e2);
int AFNDCierreLTransicionIJ(AFND * p_afnd, int i, int j);
int AFNDIndicePrimerEstadoFinal(AFND * p_afnd);

/* FUNCIONES PARA IMPRIMIR DIAGRAMA */
void AFNDADot(AFND * p_afnd);

/* FUNCIONES PARA OBTENER INFORMACIÓN DEL AUTÓMATA */
int AFNDNumSimbolos(AFND * p_afnd);
int AFNDNumEstados(AFND * p_afnd);
int AFNDTipoEstadoEn(AFND * p_afnd, int pos);

#endif
