#include "graph.h"
#include "stack_element.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 255

/*Funci贸n copiada de graph_test.c*/
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


/*Funci贸n que lee las conexiones del grafo cargado y mete en una pila primero el
 nodo origen y despu茅s el nodo destino de cada conexi贸n encontrada, para despu茅s
 imprimir la pila*/
int format(Graph *g, FILE *f){
    Stack *p;
    Node *auxNode;
    int i, j;
    Element *ele;
    int *ids;
    
    if(g==NULL || f==NULL){
        return -1;
    }
    
    p = stack_ini();
    if(p==NULL){
        return -1;
    }
    
    /*Array con todos los ids de los nodos del grafo*/
    ids = graph_getNodeIds(g);
    if(ids == NULL){
        stack_destroy(p);
        return -1;
    }

    /*Bucle doble que percorre la matriz de adyacencia en busca de conexiones*/
    for(i=(graph_getNnodes(g)-1); i>=0; i--){
        for(j=(graph_getNnodes(g)-1); j>=0; j--){
            if(graph_areConnected(g, ids[i], ids[j])==TRUE){
                ele = element_ini();
                if(ele==NULL){
                    stack_destroy(p);
                    free(ids);
                    return -1;
                }
                auxNode = graph_getNode(g, ids[i]);
                if(auxNode==NULL){
                    free(ids);
                    element_destroy(ele);
                    stack_destroy(p);
                    return -1;
                }
                ele = element_setInfo(ele, auxNode);
                if(ele==NULL){
                    free(ids);
                    node_destroy(auxNode);
                    stack_destroy(p);
                    return -1;
                }
                /*Metemos nodo origen de la conexi贸n en la pila*/
                stack_push(p, ele);
                if(p==NULL){
                    free(ids);
                    node_destroy(auxNode);
                    element_destroy(ele);
                    return -1;
                }
                node_destroy(auxNode);
                element_destroy(ele);
                
                
                ele = element_ini();
                if(ele==NULL){
                    stack_destroy(p);
                    free(ids);
                    return -1;
                }
                auxNode = graph_getNode(g, ids[j]);
                if(auxNode==NULL){
                    free(ids);
                    element_destroy(ele);
                    stack_destroy(p);
                    return -1;
                }
                ele = element_setInfo(ele, auxNode);
                if(ele==NULL){
                    free(ids);
                    node_destroy(auxNode);
                    stack_destroy(p);
                    return -1;
                }
                /*Metemos el nodo destino de la conexi贸n en la pila*/
                stack_push(p, ele);
                if(p==NULL){
                    free(ids);
                    node_destroy(auxNode);
                    element_destroy(ele);
                    return -1;
                }
                node_destroy(auxNode);
                element_destroy(ele);
            }
        }
    }
    /*Imprimimos la pila*/
    stack_print(f, p);
    
    free(ids);
    stack_destroy(p);
    
    return 0;
}

int main(int argc, char** argv) {
    Graph * g = NULL;
    if (argc < 2){
	fprintf(stdout, "Par醡etros de entrada insuficientes: %d\n", argc);
	fprintf(stdout, "Introduzca nombre del programa y nombre del fichero de texto con el grafo separados por un espacio.\n");
	return -1;
    }
    
    /*OBSERSVACI覰: Por defecto en el fichero "grafo.txt" contiene el grafo 1 subido en Moodle
     para la comprobacion de la practica 1. Si desea probar otro grafo, modifique el contenido
     del fichero "grafo.txt" que se encuentra en la carpeta P2_E2*/
    g = read_graph_from_file(argv[1]);
    if(g==NULL){
        return EXIT_FAILURE;
    }
    
    format(g, stdout);

    graph_destroy(g);

    return EXIT_SUCCESS;
}
