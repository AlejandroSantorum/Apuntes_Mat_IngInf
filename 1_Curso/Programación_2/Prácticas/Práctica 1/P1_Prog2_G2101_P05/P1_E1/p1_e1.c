#include "node.h"
#include <stdio.h>

int main(){
    Node *n1, *n2;
    FILE *f;
    
    n1 = node_ini();
    n2 = node_ini();
    
    n1 = node_setName(n1, "first");
    n1 = node_setId(n1, 111);   
    n2 = node_setName(n2, "second");
    n2 = node_setId(n2, 222);
    
    f = fopen("nodos.txt","a");
    
    /*A continuación se considera como salida tanto la terminal de NetBeans como
    el propio fichero debido a que en la Documentación de la Práctica 1,
    no se especifica cual debe ser la salida, por lo que las intrucciones
    están repetidas dos a dos, una para realizar la instrucción sobre el fichero de
    texto y otra para la terminal.*/
    
    node_print(f, n1);   
    node_print(f, n2);
    fprintf(f, "\r\n");
    
    printf("[%d, %s]", node_getId(n1), node_getName(n1));
    printf("[%d, %s]\n", node_getId(n2), node_getName(n2));
    
    fprintf(f, "Son iguales? ");
    printf("Son iguales? ");
    
    if(node_equals(n1, n2)==TRUE){
        fprintf(f, "No\r\n");
        printf("No\n");
    }
    else if(node_equals(n1, n2)==FALSE){
        fprintf(f, "Sí\r\n");
        printf("Sí\n");
    }
    
    fprintf(f, "Id del primer nodo: %d\r\n", node_getId(n1));
    printf("Id del primer nodo: %d\n", node_getId(n1));
    
    fprintf(f, "Nombre del segundo nodo es: %s\r\n", node_getName(n2));
    printf("Nombre del segundo nodo es: %s\n", node_getName(n2));
    
    n2 = node_copy(n1);
    
    node_print(f, n1);
    node_print(f, n2);
    fprintf(f, "\r\n");
    
    printf("[%d, %s]", node_getId(n1), node_getName(n1));
    printf("[%d, %s]\n", node_getId(n2), node_getName(n2));
    
    fprintf(f, "Son iguales? ");
    printf("Son iguales? ");
    
    if(node_equals(n1, n2)==TRUE){
        fprintf(f, "No\r\n");
        printf("No\n");
    }
    else if(node_equals(n1, n2)==FALSE){
        fprintf(f, "Sí\r\n");
        printf("Sí\n");
    }
    
    fclose(f);
    
    node_destroy(n1);
    node_destroy(n2);
    
    return 0;
}

