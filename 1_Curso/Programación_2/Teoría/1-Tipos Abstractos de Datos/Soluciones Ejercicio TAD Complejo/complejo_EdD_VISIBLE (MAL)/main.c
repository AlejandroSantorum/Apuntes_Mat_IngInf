#include <stdio.h>
#include "complejo.h"


int main() {

    Complejo c;
    
    complejo_actualizar(&c, 1.0, 2.0);
    complejo_imprime(c, stdout);
    printf("\n");
    
    c.re = 5; // esto no debería poder hacerlo el usuario (no debe conocer
              // ni acceder a la EdD directamente). Pero como hemos
              // definido la EdD de complejo en complejo.h , sí puede en este
              // caso. Esto lo evitaremos en este curso definiendo los
              // detalles de la EdD en complejo.c, nunca en complejo.h
    
    complejo_imprime(c, stdout);
    
    return 0;
}
