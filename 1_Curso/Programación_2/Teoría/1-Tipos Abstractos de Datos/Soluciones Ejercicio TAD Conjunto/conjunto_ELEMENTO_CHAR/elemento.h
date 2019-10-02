#ifndef _ELEMENTO_H_
#define	_ELEMENTO_H_

#include "tipos.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct _Elemento Elemento;

Elemento *elemento_crear(const char *);
void elemento_liberar(Elemento *);
Elemento *elemento_copiar(const Elemento *);
int elemento_comparar(const Elemento *, const Elemento *);
Status elemento_imprimir(FILE *, const Elemento *);

#endif	/* _ELEMENTO_H */
