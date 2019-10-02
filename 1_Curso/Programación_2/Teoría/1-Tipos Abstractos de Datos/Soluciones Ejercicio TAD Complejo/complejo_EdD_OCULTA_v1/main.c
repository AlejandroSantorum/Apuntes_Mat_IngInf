#include <stdio.h>
#include "complejo.h"

int main() {
    Complejo *pc;
    
    pc = complejo_crear(1.0, 2.0);
    if(!pc)
        return -1;
    complejo_actualizar(pc, 1.0, 2.0);
    complejo_imprime(pc, stdout);
    complejo_liberar(pc);
    
    return 0;
}

