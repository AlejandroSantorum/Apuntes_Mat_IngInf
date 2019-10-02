#include <stdio.h>

#include "Tree.h"
#include "functions.h"


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
    int num;
    
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
    
    fprintf(stdout, "> Introduzca un numero: ");
    scanf("%d", &num);
    fprintf(stdout, "Numero introducido: %d\n", num);
    
    if(tree_find(t, &num) == TRUE){
        fprintf(stdout, "El dato %d se encuentra dentro del Arbol.\n", num);
    }
    else if(tree_find(t, &num) == FALSE){
        fprintf(stdout, "El dato %d NO se encuentra dentro del Arbol.\n", num);
    }
    
    tree_destroy(t);
    
    return EXIT_SUCCESS;
}