#ifndef _COMPLEJO_H_
#define	_COMPLEJO_H_

#include "tipos.h"
#include <stdio.h>
#include <stdlib.h>

struct Complejo {  // Definimos la EdD aquí (y por tanto es visible al usuario),
    float re, im;  // lo que consideraremos erróneo a lo largo de este curso
};

Status complejo_actualizar(Complejo *pc, float r, float i);
float complejo_getReal(const Complejo c);
float complejo_getImaginaria(const Complejo c);
Complejo complejo_conjugado(const Complejo c);
Complejo complejo_sumar(const Complejo c1, const Complejo c2);
Complejo complejo_restar(const Complejo c1, const Complejo c2);
Status complejo_imprime(Complejo c, FILE *f);

#endif	/* _COMPLEJO__H */
