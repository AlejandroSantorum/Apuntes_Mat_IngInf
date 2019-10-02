#include <stdio.h>

#include "tree4.h"
#include "functions4.h"

#define MAX 500

Tree* read_data_from_file(char *filename){
    FILE *in=NULL;
    Tree *t=NULL;
    destroy_elementtree_function_type f1;
    copy_elementtree_function_type f2;
    print_elementtree_function_type f3;
    cmp_elementtree_function_type f4;
    char buff[MAX];
    
    f1 = destroy_str_function;
    f2 = copy_str_function;
    f3 = print_str_function;
    f4 = cmp_str_function;
    
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
        fscanf(in,"%s",buff);
        if(tree_insert(t, buff)==ERROR){
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
    char in[MAX];
    
    if (argc < 2){
	fprintf(stdout, "Parámetros de entrada insuficientes: %d\n", argc);
	fprintf(stdout, "Introduzca nombre del programa y nombre del fichero de texto con los números a introducir.\n"); 
	return -1;
    }
    
    t = read_data_from_file(argv[1]);
    if(t==NULL){
        return EXIT_FAILURE;
    }
    
    fprintf(stdout, "Numero de nodos: %d\n", tree_numNodes(t));
    
    fprintf(stdout, "Profundidad: %d\n", tree_depth(t));
    
    fprintf(stdout, "Orden previo:");
    tree_preOrder(stdout, t);
    
    fprintf(stdout, "\nOrden medio:");
    tree_inOrder(stdout, t);
    
    fprintf(stdout, "\nOrden posterior:");
    tree_postOrder(stdout, t);
    fprintf(stdout, "\n");
    
    fprintf(stdout, "> Introduzca una cadena para buscar en el arbol (siguiendo el mismo formato que el fichero de entrada): ");
    scanf("%s", in);
    fprintf(stdout, "Cadena introducida: %s\n", in);
    
    if(tree_find(t, in) == TRUE){
        fprintf(stdout, "La cadena \"%s\" se encuentra dentro del Arbol.\n", in);
    }
    else if(tree_find(t, in) == FALSE){
        fprintf(stdout, "La cadena \"%s\" NO se encuentra dentro del Arbol.\n", in);
    }
    
    tree_destroy(t);
    
    return EXIT_SUCCESS;
}
