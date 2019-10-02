#include <stdio.h>
#include "elemento.h"
#include "conjunto.h"

int main() {
    Conjunto *pc1, *pc2, *pc3;
    Elemento *pe;
    
    pc1 = conjunto_crear();
    if(!pc1)
        return -1;
    
    pc2 = conjunto_crear();
    if(!pc1) {
        conjunto_liberar(pc2);
        return -1;
    }
    
    pe = elemento_crear("blablabla");
    // habría que controlar errores.
    conjunto_insertar(pc1, pe);        
    elemento_liberar(pe);

    pe = elemento_crear("pi = 3.14...");
    conjunto_insertar(pc1, pe);
    elemento_liberar(pe);
        
    pe = elemento_crear("HOLA");
    conjunto_insertar(pc2, pe);
    elemento_liberar(pe);
    
    pe = elemento_crear("blablabla");
    conjunto_insertar(pc2, pe);
    elemento_liberar(pe);
        
    printf("*** Conjunto 1:\n");
    conjunto_imprimir(stdout, pc1);
    printf("\n*** Conjunto 2:\n");
    conjunto_imprimir(stdout, pc2);
    
    pc3 = conjunto_union(pc1, pc2);
    printf("\n*** Conjunto unión:\n");
    conjunto_imprimir(stdout, pc3);
    
    conjunto_liberar(pc3);
    
    pc3 = conjunto_interseccion(pc1, pc2);
    printf("\n*** Conjunto intersección:\n");
    conjunto_imprimir(stdout, pc3);
    
    pe = elemento_crear("blablabla");
    conjunto_eliminar(pc1, pe);
    elemento_liberar(pe);
    printf("\n*** Conjunto 1 sin elemento ");
    elemento_imprimir(stdout, pe);
    conjunto_imprimir(stdout, pc1);
    
    conjunto_liberar(pc1);
    conjunto_liberar(pc2);
    conjunto_liberar(pc3);    
    
    return 0;
}
