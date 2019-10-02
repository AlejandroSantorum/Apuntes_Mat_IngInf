#include <stdio.h>

#include "tree3.h"
#include "list3.h"
#include "functions3.h"


Tree* read_data_from_file(char *filename){
    FILE *in=NULL;
    Tree *t=NULL;
    destroy_elementtree_function_type f1;
    copy_elementtree_function_type f2;
    print_elementtree_function_type f3;
    cmp_elementtree_function_type f4;
    int aux;
    
    f1 = destroy_intp_function;
    f2 = copy_intp_function;
    f3 = print_intp_function;
    f4 = cmp_intp_function;
    
    t = tree_ini(f1, f2, f3, f4);
    if(t == NULL){
        return NULL;
    }
    
    in = (FILE*) fopen(filename, "r");
    if (in == NULL){
	tree_destroy(t);
	return NULL;
    }
    
    while(feof(in)==0){
        fscanf(in,"%d",&aux);
        if(tree_insert(t, &aux)==ERROR){
                tree_destroy(t);
                fclose(in);
                return NULL;
        }
    }
    
    fclose(in);
    return t;
}



int main(int argc, char** argv){
    Tree *t=NULL;
    List *l1=NULL, *l2=NULL, *l3=NULL;
    destroy_elementlist_function_type f1;
    copy_elementlist_function_type f2;
    print_elementlist_function_type f3;
    cmp_elementlist_function_type f4;
    int num;
        
    if (argc < 2){
	fprintf(stdout, "Parámetros de entrada insuficientes: %d\n", argc);
	fprintf(stdout, "Introduzca nombre del programa y nombre del fichero de texto con los números a introducir.\n"); 
	return -1;
    }
    
    f1 = destroy_intp_function;
    f2 = copy_intp_function;
    f3 = print_intp_function;
    f4 = cmp_intp_function;
    
    t = read_data_from_file(argv[1]);
    if(t==NULL){
        return EXIT_FAILURE;
    }
    
    l1 = list_ini(f1, f2, f3, f4);
    if(l1 == NULL){
        return EXIT_FAILURE;
    }
    
    l2 = list_ini(f1, f2, f3, f4);
    if(l2 == NULL){
        list_free(l1);
        return EXIT_FAILURE;
    }
    
    l3 = list_ini(f1, f2, f3, f4);
    if(l3 == NULL){
        list_free(l1);
        list_free(l2);
        return EXIT_FAILURE;
    }
    
    fprintf(stdout, "Numero de nodos: %d\n", tree_numNodes(t));
    
    fprintf(stdout, "Profundidad: %d\n", tree_depth(t));
    
    /*OUTPUT CON ÁRBOLES*/
    fprintf(stdout, "Output usando árboles: \n");
    
    fprintf(stdout, "Orden previo:");
    tree_preOrder(stdout, t);
    
    fprintf(stdout, "\nOrden medio:");
    tree_inOrder(stdout, t);
    
    fprintf(stdout, "\nOrden posterior:");
    tree_postOrder(stdout, t);
    fprintf(stdout, "\n");
    
    /*OUTPUT USANDO LISTAS(OPCIONAL)*/
    fprintf(stdout, "Output usando listas (opcional): \n");
    
    tree_preOrderToList(l1, t);
    fprintf(stdout, "Orden previo:");
    list_print(stdout, l1);
    
    tree_inOrderToList(l2, t);
    fprintf(stdout, "\nOrden medio:");
    list_print(stdout, l2);
    
    tree_postOrderToList(l3, t);
    fprintf(stdout, "\nOrden posterior:");
    list_print(stdout, l3);
    
    fprintf(stdout, "\n");
    
    /*Se pide un número*/
    fprintf(stdout, "> Introduzca un numero: ");
    scanf("%d", &num);
    fprintf(stdout, "Numero introducido: %d\n", num);
    
    if(tree_find(t, &num) == TRUE){
        fprintf(stdout, "El dato %d se encuentra dentro del Arbol.\n", num);
    }
    else if(tree_find(t, &num) == FALSE){
        fprintf(stdout, "El dato %d NO se encuentra dentro del Arbol.\n", num);
    }
    
    /*Zona de liberación*/
    tree_destroy(t);
    list_free(l1);
    list_free(l2);
    list_free(l3);
    
    return EXIT_SUCCESS;
}