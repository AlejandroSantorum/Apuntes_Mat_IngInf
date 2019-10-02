/**
*  Project: Assignment 2 - ProgII subject
*  File: element_int.h
*  Version: 2.0
*  Date: Feb 20, 2017
*  Revision date: May 27, 2018
*
*  (C) Alejandro Santorum Varela
*  alejandro.santorum@gmail.com
*
*/
#ifndef ELEMENT_INT_H
#define ELEMENT_INT_H

#include <stdio.h>
#include "types.h"

typedef struct _Element Element;

/**
*  Initializes a new integer element, allocating memory and returning it, or NULL in error case
*/
Element * element_ini();

/**
*  Frees the allocated memory for a given element
*/
void element_destroy(Element *e);

/**
*  It modifies the element data with a new one, given as a parameter.
*  It returns the modified element or NULL if any error ocurrs
*/
Element * element_setInfo(Element *, void*);


/**------------------------------------------------------------------
Devuelve el contenido de Element. Entrada: El elemento. Salida: El contenido de Element o NULL si ha
habido error.
------------------------------------------------------------------*/
void * element_getInfo(Element *);


/**------------------------------------------------------------------
Copia un elemento en otro, reservando memoria. Entrada: el elemento a copiar. Salida: Devuelve un puntero
al elemento copiado o NULL en caso de error.
------------------------------------------------------------------*/
Element * element_copy(const Element *);


/**------------------------------------------------------------------
Compara dos elementos. Entrada: dos elementos a comparar. Salida: Devuelve TRUE en caso de ser iguales
y si no FALSE
------------------------------------------------------------------*/
Bool element_equals(const Element *, const Element *);


/**------------------------------------------------------------------
Imprime en un fichero ya abierto el elemento. Entrada: Fichero en el que se imprime y el elemento a imprimir.
Salida: Devuelve el número de caracteres escritos.
------------------------------------------------------------------*/
int element_print(FILE *, const Element *);


#endif /*ELEMENT_INT_H*/
