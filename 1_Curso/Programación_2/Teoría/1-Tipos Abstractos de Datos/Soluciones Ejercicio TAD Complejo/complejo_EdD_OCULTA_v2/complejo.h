#ifndef _COMPLEJO_H_
#define	_COMPLEJO_H_

#include "tipos.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct _Complejo Complejo;

Complejo *complejo_crear(float r, float i);
void complejo_liberar(Complejo *pc);
Status complejo_actualizar(Complejo *pc, float r, float i);
float complejo_getReal(const Complejo *pc);
float complejo_getImaginaria(const Complejo *pc);
Status complejo_conjugado(const Complejo *pc, Complejo *pcConj);
Status complejo_sumar(const Complejo *pc1, const Complejo *pc2, Complejo *pcRes);
Status complejo_restar(const Complejo *pc1, const Complejo *pc2, Complejo *pcRes);
Status complejo_imprime(Complejo *pc, FILE *f);

#endif	/* _COMPLEJO__H */
