#include "graph.h"
#include "stack_fp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 255

/*Funci√≥n copiada de graph_test.c*/
Graph * read_graph_from_file(char * filename){
    FILE * in;
    Graph * g;
    Node * n;
    char buff[MAX], name[MAX];
    int i, nnodes, id1, id2;

    g = graph_ini();
    if (g == NULL){
        return NULL;
    }
    
    in = (FILE*) fopen(filename, "r");
    if (in == NULL){
	graph_destroy(g);
	return NULL;
    }
    
	/* Format: nnodes \n node1id node1name ... nodenid nodenname connection1a connection1b ... */
    fgets(buff, MAX, in);
    sscanf(buff, "%d", &nnodes);
    /* read nodes line by line */
    for(i=0; i<nnodes;i++) {
        fgets(buff, MAX, in);
	sscanf(buff, "%d %s", &id1, name);
        
	/* create node */
	n = node_ini();
	if (node_setId(n, id1) == NULL){
            fclose (in);
            node_destroy(n);
            graph_destroy(g);
            return NULL;
	}
        
	if (node_setName(n, name) == NULL){
            fclose (in);
            node_destroy(n);
            graph_destroy(g);
            return NULL;
	}
        
	/* add node to graph */
	if (graph_addNode(g, n) == NULL){
            fclose (in);
            node_destroy(n);
            graph_destroy(g);
            return NULL;
	}
	/* destroy node */
	node_destroy(n);
    }
    
    
	/* read connections */
	while (!feof(in)){
            fgets(buff, MAX, in);
            sscanf(buff, "%d %d", &id1, &id2);
            if (graph_addEdge(g, id1, id2) == NULL){
		fclose (in);
		graph_destroy(g);
		return NULL;
            }
	}

	fclose (in);

	return g;
}

int format(Graph *g, FILE *f){
    destroy_element_function_type f1nodo, f1entero;
    copy_element_function_type f2nodo, f2entero;
    print_element_function_type f3nodo, f3entero;
    
    Stack *pNodos, *pEnteros;
    Node *auxNode;
    int i, j;
    int *ids;
    
    f1nodo = destroy_node_function;
    f1entero = destroy_intp_function;
    f2nodo = copy_node_function;
    f2entero = copy_intp_function;
    f3nodo = print_node_function;
    f3entero = print_intp_function;
    
    if(g==NULL || f==NULL){
        return -1;
    }
    
    pNodos = stack_ini(f1nodo, f2nodo, f3nodo);
    if(pNodos==NULL){
        return -1;
    }
    
    pEnteros = stack_ini(f1entero, f2entero, f3entero);
    if(pNodos==NULL){
        stack_destroy(pNodos);
        return -1;
    }
    
    /*Array con todos los ids de los nodos del grafo*/
    ids = graph_getNodeIds(g);
    if(ids == NULL){
        stack_destroy(pNodos);
        stack_destroy(pEnteros);
        return -1;
    }

    /*Bucle doble que percorre la matriz de adyacencia en busca de conexiones*/
    for(i=(graph_getNnodes(g)-1); i>=0; i--){
        for(j=(graph_getNnodes(g)-1); j>=0; j--){
            if(graph_areConnected(g, ids[i], ids[j])==TRUE){
                auxNode = graph_getNode(g, ids[i]);
                if(auxNode==NULL){
                    free(ids);
                    stack_destroy(pNodos);
                    stack_destroy(pEnteros);
                    return -1;
                }
                
                /*Metemos el nodo origen en la pila de nodos
                 y su ID en la pila de enteros*/
                stack_push(pNodos, auxNode);
                if(pNodos==NULL){
                    free(ids);
                    node_destroy(auxNode);
                    stack_destroy(pEnteros);
                    return -1;
                }
                
                stack_push(pEnteros, &ids[i]);
                if(pEnteros==NULL){
                    free(ids);
                    node_destroy(auxNode);
                    stack_destroy(pNodos);
                    return -1;
                }
                
                node_destroy(auxNode);
                
                
                
                /*Procedemos a hacer lo mismo con el nodo destino*/
                auxNode = graph_getNode(g, ids[j]);
                if(auxNode==NULL){
                    free(ids);
                    node_destroy(auxNode);
                    stack_destroy(pEnteros);
                    return -1;
                }
                
                /*Metemos el nodo destino en la pila de nodos
                 y su ID en la pila de enteros*/
                stack_push(pNodos, auxNode);
                if(pNodos==NULL){
                    free(ids);
                    node_destroy(auxNode);
                    stack_destroy(pEnteros);
                    return -1;
                }
                stack_push(pEnteros, &ids[j]);
                if(pEnteros==NULL){
                    free(ids);
                    node_destroy(auxNode);
                    stack_destroy(pNodos);
                    return -1;
                }
                node_destroy(auxNode);
            }
        }
    }
    /*Imprimimos la pila de enteros*/
    fprintf(stdout, "Pila de enteros:\n");
    stack_print(f, pEnteros);
    /*Imprimimos la pila de nodos*/
    fprintf(stdout, "Pila de nodos:\n");
    stack_print(f, pNodos);
    
    free(ids);
    stack_destroy(pNodos);
    stack_destroy(pEnteros);
    
    return 0;
}

int main(int argc, char** argv) {
    Graph * g = NULL;
    if (argc < 2){
	fprintf(stdout, "Par·metros de entrada insuficientes: %d\n", argc);
	fprintf(stdout, "Introduzca nombre del programa y nombre del fichero de texto con el grafo.\n"); 
	return -1;
    }
    
    /*OBSERSVACION: Por defecto en el fichero "grafo.txt" contiene el grafo 1 subido en Moodle
     para la comprobaciOn de la practica 1. Si desea probar otro grafo, modifique el contenido
     del fichero "grafo.txt" que se encuentra en la carpeta P2_E2*/
    g = read_graph_from_file(argv[1]);
    if(g==NULL){
        return EXIT_FAILURE;
    }
    
    format(g, stdout);

    graph_destroy(g);

    return EXIT_SUCCESS;
}