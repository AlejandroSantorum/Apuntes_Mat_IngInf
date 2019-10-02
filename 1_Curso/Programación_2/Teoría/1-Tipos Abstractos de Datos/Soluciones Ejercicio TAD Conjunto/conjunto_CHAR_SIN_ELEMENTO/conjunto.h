#ifndef _CONJUNTO_H_
#define	_CONJUNTO_H_

#include "tipos.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct _Conjunto Conjunto;

Conjunto *conjunto_crear();
void conjunto_liberar(Conjunto *);
Status conjunto_vaciar(Conjunto *);
int conjunto_cardinalidad(const Conjunto *);
Status conjunto_insertar(Conjunto *, char);
Bool conjunto_buscar(const Conjunto *, char);
Conjunto *conjunto_union(const Conjunto *, const Conjunto *);
Status conjunto_imprimir(FILE *, const Conjunto *);
Conjunto *conjunto_interseccion(const Conjunto *, const Conjunto *);
Status conjunto_eliminar(Conjunto *, char);

#endif	/* _CONJUNTO_H */
