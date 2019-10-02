#include "complejo.h"

#define NaN -1e50 /* NaN = not a number (valor no válido) */

struct _Complejo {
    float v[2];
};

Complejo *complejo_crear(float r, float i) {
    Complejo *pc;    
    pc = (Complejo *) malloc(sizeof(Complejo));
    pc->v[0] = r;
    pc->v[1] = i;
    return pc;
}

void complejo_liberar(Complejo *pc) {
    free(pc);
}

float complejo_getReal(const Complejo *pc) {
    return pc->v[0];
}

float complejo_getImaginaria(const Complejo *pc) {
    return pc->v[1];
}

Status complejo_actualizar(Complejo *pc, float re, float im) {
    if(!pc)
        return ERR;
    pc->v[0] = re;
    pc->v[1] = im;
    
    return OK;
}

Status complejo_conjugado(const Complejo *pc, Complejo *pconj) {
    float r, i;
    
    r = complejo_getReal(pc);
    i = complejo_getImaginaria(pc);
    
    if((r == NaN) || (i == NaN)) /* NAN = not a number (valor no válido) */
        return ERR;
    
    return complejo_actualizar(pconj, r, -i);
}

/* res es la variable donde guardar el resultado de la función */
Status complejo_sumar(Complejo *pc1, Complejo *pc2, Complejo *pres) {
    float r1, i1, r2, i2, r, i;
    
    r1 = complejo_getReal(pc1);
    i1 = complejo_getImaginaria(pc1);
    r2 = complejo_getReal(pc2);
    i2 = complejo_getImaginaria(pc2);

    if( (r1 == NaN) || (i1 == NaN) || (r2 = NaN) || (i2 = NaN))
        return ERR;

    r = r1 + r2;
    i = i1 + i2;

    return complejo_actualizar(pres, r, i);
}

/* res es la variable donde guardar el resultado de la función */
Status complejo_restar(Complejo *pc1, Complejo *pc2, Complejo *pres) {
    float r1, i1, r2, i2, r, i;
    
    r1 = complejo_getReal(pc1);
    i1 = complejo_getImaginaria(pc1);
    r2 = complejo_getReal(pc2);
    i2 = complejo_getImaginaria(pc2);

    if( (r1 == NaN) || (i1 == NaN) || (r2 = NaN) || (i2 = NaN))
        return ERR;

    r = r1 - r2;
    i = i1 - i2;

    return complejo_actualizar(pres, r, i);
}

/* res es la variable donde guardar el resultado de la función */
Status complejo_multiplicar(Complejo *pc1, Complejo *pc2, Complejo *pres) {
    float r1, i1, r2, i2, r, i;
    
    r1 = complejo_getReal(pc1);
    i1 = complejo_getImaginaria(pc1);
    r2 = complejo_getReal(pc2);
    i2 = complejo_getImaginaria(pc2);

    if( (r1 == NaN) || (i1 == NaN) || (r2 = NaN) || (i2 = NaN))
        return ERR;

    r = r1 * r2 - i1 * i2;
    i = r1 * i2 + r2 * i1;

    return complejo_actualizar(pres, r, i);
}

Status complejo_imprime(Complejo *pc, FILE *f) {  
    if(!pc || !f)
        return ERR;
    
    fprintf(f, "%f + %fi", complejo_getReal(pc), complejo_getImaginaria(pc));
    
    return OK;
}
