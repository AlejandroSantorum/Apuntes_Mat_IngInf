#include "complejo.h"

float complejo_getReal(const Complejo c) {
    return c.re;
}

float complejo_getImaginaria(const Complejo c) {
    return c.im;
}

Status complejo_actualizar(Complejo *pc, float re, float im) {
    if(!pc)
        return ERR;
    pc->re = re;
    pc->im = im;
    
    return OK;
}

Complejo complejo_conjugado(const Complejo c) {
    Complejo res;
    
    res.re = c.re;
    res.re = -c.im;
    
    return res;
}

/* res es la variable donde guardar el resultado de la función */
Complejo complejo_sumar(Complejo c1, Complejo c2) {
    float r1, i1, r2, i2, r, i;
    Complejo res;
    
    r1 = complejo_getReal(c1);
    i1 = complejo_getImaginaria(c1);
    r2 = complejo_getReal(c2);
    i2 = complejo_getImaginaria(c2);

    r = r1 + r2;
    i = i1 + i2;

    complejo_actualizar(&res, r, i);
    return res;
}

Complejo complejo_restar(Complejo c1, Complejo c2) {
    float r1, i1, r2, i2, r, i;
    Complejo res;
    
    r1 = complejo_getReal(c1);
    i1 = complejo_getImaginaria(c1);
    r2 = complejo_getReal(c2);
    i2 = complejo_getImaginaria(c2);

    r = r1 - r2;
    i = i1 - i2;

    complejo_actualizar(&res, r, i);
    return res;
}

Complejo complejo_multiplicar(Complejo c1, Complejo c2) {
    float r1, i1, r2, i2, r, i;
    Complejo res;
    
    r1 = complejo_getReal(c1);
    i1 = complejo_getImaginaria(c1);
    r2 = complejo_getReal(c2);
    i2 = complejo_getImaginaria(c2);

    r = r1 * r2 - i1 * i2;
    i = r1 * i1 + r2 * i2;

    complejo_actualizar(&res, r, i);
    return res;
}

Status complejo_imprime(Complejo c, FILE *f) {    
    if(!f)
        return ERR;
    
//    fprintf(f, "%f + %fi", complejo_getReal(c), complejo_getImaginaria(c));
    fprintf(f, "%f + %fi", c.re, c.im);
    
    return OK;
}
