#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "functions.h"
#include "node.h"

#define MAX 300

Tree* read_data_from_file(char *filename){
    FILE *in=NULL;
    Tree *t=NULL;
    destroy_elementtree_function_type f1;
    copy_elementtree_function_type f2;
    print_elementtree_function_type f3;
    cmp_elementtree_function_type f4;
    Node *n=NULL;
    int id;
    char name[MAX];
    
    
    f1 = destroy_node_function;
    f2 = copy_node_function;
    f3 = print_node_function;
    f4 = cmp_node_function;
    
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
        fscanf(in,"%d %s",&id, name);
        n = node_ini();
        if(node_setName(n, name) == NULL){
            fclose(in);
            node_destroy(n);
            tree_destroy(t);
            return NULL;
        }
        if (node_setId(n, id) == NULL){
            fclose(in);
            node_destroy(n);
            tree_destroy(t);
            return NULL;
        }
        if(tree_insert(t, n) == ERROR){
            fclose(in);
            node_destroy(n);
            tree_destroy(t);
            return NULL;
        }
        
        node_destroy(n);
    }
    
    fclose(in);
    return t;
}

int main(int argc, char** argv){
    Tree *t=NULL;
    int i, j;
    
    if (argc < 2){
	fprintf(stdout, "Parámetros de entrada insuficientes: %d\n", argc);
	fprintf(stdout, "Introduzca nombre del programa y nombre del fichero de texto con los nodos a introducir.\n"); 
	return EXIT_FAILURE;
    }
    
    t = read_data_from_file(argv[1]);
    
    if(t == NULL){
        return EXIT_FAILURE;
    }
    i = tree_depth(t);
    
    j = tree_numNodes(t);
    
    fprintf(stdout, "Logitud: %d\n", i);
    fprintf(stdout, "Número de nodos: %d\n", j);
    
    return EXIT_SUCCESS;
}