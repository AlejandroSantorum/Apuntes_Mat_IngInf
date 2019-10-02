#ifndef ELEMENT_H
#define ELEMENT_H

#include "types.h"
#include <stdio.h>

typedef struct _Element Element;


/**------------------------------------------------------------------
Inicializa un elemento de pila. Salida: Puntero al elemento inicializado o NULL en caso de error
------------------------------------------------------------------*/
Element * element_ini();


/**------------------------------------------------------------------
Elimina un elemento. Entrada: Elemento a destruir.
------------------------------------------------------------------*/
void element_destroy(Element *);


/**------------------------------------------------------------------
Modifica los datos de un elemento. Entrada: El elemento a modificar y el contenido a guardar en dicho
elemento. Salida: El elemento a modificar o NULL si ha habido error.
------------------------------------------------------------------*/
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


#endif /*ELEMENT_H*/