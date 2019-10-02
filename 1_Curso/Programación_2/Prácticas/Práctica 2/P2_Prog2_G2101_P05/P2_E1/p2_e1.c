#include "stack_element.h"
#include <stdio.h>
#include <stdlib.h>

void pila_total(Stack *p){
    if(stack_isEmpty(p)==TRUE){
        printf("Pila total (no llena, vacía):\n");
    }
    else if(stack_isFull(p)==TRUE){
        printf("Pila total (llena, no vacía):\n");
    }
    else{
        printf("Pila total (no llena, no vacía):\n");
    }
}


void imprimiendo_pila_pares(Stack *p){
    if(stack_isEmpty(p)==TRUE){
        printf("Imprimiendo la pila(no llena, vacía) con números pares:\n");
    }
    else if(stack_isFull(p)==TRUE){
        printf("Imprimiendo la pila (llena, no vacía) con números pares:\n");
    }
    else{
        printf("Imprimiendo la pila (no llena, no vacía) con números pares:\n");
    }
}


void imprimiendo_pila_impares(Stack *p){
    if(stack_isEmpty(p)==TRUE){
        printf("Imprimiendo la pila(no llena, vacía) con números impares:\n");
    }
    else if(stack_isFull(p)==TRUE){
        printf("Imprimiendo la pila (llena, no vacía) con números impares:\n");
    }
    else{
        printf("Imprimiendo la pila (no llena, no vacía) con números impares:\n");
    }
}

int main(int argc, char **argv){
    int i, argumento;
    int aux, info;
    Stack *p=NULL, *pImpares=NULL, *pPares=NULL;
    Element *ele=NULL;
    FILE *f;
    
    f = stdout;
    
    argumento = atoi(argv[1]); 
    
    /*COMPROBACIONES E INICIALIZACIONES DE LOS PUNTEROS*/
    ele=element_ini();
    
    p = stack_ini();
    if(p==NULL){
        return -1;
    }
    pImpares = stack_ini();
    if(pImpares==NULL){
        return -1;
    }
    pPares = stack_ini();
    if(pPares==NULL){
        return -1;
    }
    /*FIN COMPROBACIONES*/
    
    /*IMPRIMIMOS NOMBRE PROGRAMA Y ARGUMENTO PASADO POR LA CONSOLA*/
    printf("%s", argv[0]);
    printf(" %s\n", argv[1]);
    
    /*FUNCIÓN QUE SE ENCARGA DE DETERMINAR E IMPRIMIR SI LA
     PILA PRINCIPAL ESTÁ LLENA, VACÍA O NINGUNA DE LAS DOS*/
    pila_total(p);
    
    /*BUCLE QUE PIDE AL USUARIO TANTOS ELEMENTOS COMO SE INDICÓ EN EL ARGUMENTO
     E LOS INTRODUCE EN LA PILA PRINCIPAL*/
    for(i=0; i<argumento; i++){
        printf("Introduce un número: ");
        scanf("%d", &aux);
        ele = element_setInfo(ele, &aux);
        p = stack_push(p, ele);
    }
    element_destroy(ele);
    
    pila_total(p);
    stack_print(f, p);
    
    /*ORGANIZAMOS LAS PILAS pPares Y pImpares DEPENDIENDO SI EL ELEMENTO EXTRAÍDO(POP)
     * DE LA PILA PRINCIPAL ES PAR O IMPAR*/
    for(i=0; i<argumento; i++){
        ele = stack_pop(p);
        info = *((int*)element_getInfo(ele));
        if(((info)%2)==0){
            pPares = stack_push(pPares, ele);
            element_destroy(ele);
        }
        else if(((info)%2)==1){
            pImpares = stack_push(pImpares, ele);
            element_destroy(ele);
        }
    }
    
    /*FUNCIÓN QUE SE ENCARGA DE DETERMINAR E IMPRIMIR SI LA PILA DE PARES
     * ESTÁ LLENA, VACÍA O NINGUNA */
    imprimiendo_pila_pares(pPares);
    stack_print(f, pPares);
    
    /*FUNCIÓN QUE SE ENCARGA DE DETERMINAR E IMPRIMIR SI LA PILA DE PARES
     * ESTÁ LLENA, VACÍA O NINGUNA */
    imprimiendo_pila_impares(pImpares);
    stack_print(f, pImpares);
    
    pila_total(p);
    stack_print(f, p);
    
    /*LIBERACIÓN*/
    stack_destroy(p);
    stack_destroy(pPares);
    stack_destroy(pImpares);
    
    return EXIT_SUCCESS;
}
