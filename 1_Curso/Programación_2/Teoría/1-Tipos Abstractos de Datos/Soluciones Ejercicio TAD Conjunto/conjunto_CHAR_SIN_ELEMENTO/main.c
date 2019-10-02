#include <stdio.h>
#include "conjunto.h"

int main() {

    Conjunto *pc1, *pc2, *pc3;
        
    pc1 = conjunto_crear();
    if(!pc1)
        return -1;
    
    pc2 = conjunto_crear();
    if(!pc1) {
        conjunto_liberar(pc2);
        return -1;
    }
        
    conjunto_insertar(pc1, 'A');
    // habría que controlar errores.
    conjunto_insertar(pc1, 'B');
    conjunto_insertar(pc1, 'A');
    conjunto_insertar(pc1, 'C');
    
    conjunto_insertar(pc2, 'D');
    conjunto_insertar(pc2, 'B');
    conjunto_insertar(pc2, 'F');
    conjunto_insertar(pc2, 'A');
    
    printf("Conjunto 1:\n");
    conjunto_imprimir(stdout, pc1);
    printf("\nConjunto 2:\n");
    conjunto_imprimir(stdout, pc2);
    
    pc3 = conjunto_union(pc1, pc2);
    printf("\nConjunto unión:\n");
    conjunto_imprimir(stdout, pc3);
    
    conjunto_liberar(pc3);
    
    pc3 = conjunto_interseccion(pc1, pc2);
    printf("\nConjunto intersección:\n");
    conjunto_imprimir(stdout, pc3);
    
    conjunto_eliminar(pc1, 'A');
    printf("\nConjunto 1 sin A:\n");
    conjunto_imprimir(stdout, pc1);
    
    conjunto_liberar(pc1);
    conjunto_liberar(pc2);
    conjunto_liberar(pc3);
    
    return 0;
}
