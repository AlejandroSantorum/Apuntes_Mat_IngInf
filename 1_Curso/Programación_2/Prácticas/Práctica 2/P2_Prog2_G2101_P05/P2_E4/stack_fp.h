#ifndef STACK_FP_H
#define STACK_FP_H

#include <stdio.h>
#include "types.h"
#include "functions.h"

#define MAXSTACK 100

typedef struct _Stack Stack;

/* Tipos de los punteros a función soportados por la pila */ 
typedef void (*destroy_element_function_type)(void*);
typedef void *(*copy_element_function_type)(const void*);
typedef int (*print_element_function_type)(FILE *, const void*);


/**------------------------------------------------------------------
 *  Inicializa la pila reservando memoria y almacenando los tres punteros a función
 *  pasados como parámetro (el primero para destruir elementos, el segundo para copiar
 *  elementos y el tercero para imprimir elementos).
 *  Salida: NULL si ha habido error o la pila si ha ido bien
 *  ------------------------------------------------------------------*/ 
Stack * stack_ini(destroy_element_function_type f1, copy_element_function_type f2, print_element_function_type f3); 


/**------------------------------------------------------------------
 *  Elimina la pila Entrada: la pila que se va a eliminar
 *  ------------------------------------------------------------------*/
void stack_destroy(Stack *);


/**------------------------------------------------------------------
 *  Inserta un elemento en la pila. Entrada: un elemento y la pila donde insertarlo.
 *  Salida: NULL si no logra insertarlo o la pila resultante si lo logra
 *  ------------------------------------------------------------------*/
Stack * stack_push(Stack *, const void *);


/**------------------------------------------------------------------
 *  Extrae un elemento en la pila. Entrada: la pila de donde extraerlo.
 *  Salida: NULL si no logra extraerlo o el elemento extraido si lo logra.
 *  Nótese que la pila quedará modificada
 *  ------------------------------------------------------------------*/
void * stack_pop(Stack *);


/**------------------------------------------------------------------
 *  Copia un elemento (reservando memoria) sin modificar el top de la pila.
 *  Entrada: la pila de donde copiarlo.
 *  Salida: NULL si no logra copiarlo o el elemento si lo logra
 *  ------------------------------------------------------------------*/
void * stack_top(const Stack *);


/**------------------------------------------------------------------
 *  Comprueba si la pila esta vacia. Entrada: pila.
 *  Salida: TRUE si está vacia o FALSE si no lo esta
 *  ------------------------------------------------------------------*/
Bool stack_isEmpty(const Stack *); 


/**------------------------------------------------------------------
 *  Comprueba si la pila esta llena. Entrada: pila.
 *  Salida: TRUE si está llena o FALSE si no lo esta
 *  ------------------------------------------------------------------*/
Bool stack_isFull(const Stack *);


/**------------------------------------------------------------------
 *  Imprime toda la pila, colocando el elemento en la cima al principio
 *  de la impresión (y un elemento por línea). Entrada: pila y fichero donde imprimirla.
 *  Salida: Devuelve el número de caracteres escritos.
 *  ------------------------------------------------------------------*/
int stack_print(FILE*, const Stack*);


#endif /* STACK_FP_H */
