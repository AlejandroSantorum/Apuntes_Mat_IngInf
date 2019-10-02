#include "stack_element.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX 255

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


int etiquetar_nodo(Node *n, int *array, int posicion){
    int id;
    
    if(n==NULL||array==NULL||posicion<0){
        return -1;
    }
    
    id = node_getId(n);
    array[posicion] = id;
    
    return 0;
}


Bool marcado(Node *n, int *array, int nNodes){
    int id, i;
    
    if(n==NULL||array==NULL||nNodes<0){
        return FALSE;
    }
    
    id = node_getId(n);
    for(i=0; i<nNodes; i++){
        if(array[i]==id){
            return TRUE;
        }
    }
    return FALSE;
}


Bool mas_caminos(Graph *g, Node *n, int *conectados, int *marcados){
    int i;
    Node *nAux;
    
    if(n==NULL||conectados==NULL||marcados==NULL){
        return FALSE;
    }
    
    for(i=0; i<graph_getNumberOfConnectionsFrom(g, node_getId(n)); i++){
        nAux = graph_getNode(g, conectados[i]);
        if(marcado(nAux, marcados, graph_getNnodes(g))==FALSE){
            node_destroy(nAux);
            return TRUE;
        }
        node_destroy(nAux);
    }
    
    return FALSE;
}


Bool recorrer(Graph *g, Node *nSource, Node *nGoal){
    Stack *pMain;
    Element *ele;
    int *arrayMarcados, *arrayConectados;
    int nNodos, contador=0, i;
    Node *nodoAux, *nodoAux2;
    
    if(g==NULL||nSource==NULL||nGoal==NULL){
        return FALSE;
    }
    
    pMain = stack_ini();
    if(pMain==NULL){
        return FALSE;
    }
    
    ele = element_ini();
    if(ele==NULL){
        stack_destroy(pMain);
        return FALSE;
    }
    
    ele = element_setInfo(ele, nSource);
    if(ele==NULL){
        stack_destroy(pMain);
        return FALSE;
    }
    
    nNodos = graph_getNnodes(g);
    
    arrayMarcados = (int *) malloc(nNodos*sizeof(int));
    for(i=0; i<nNodos; i++){
        arrayMarcados[i]=-1;
    }
    
    stack_push(pMain, ele);
    if(pMain==NULL){
        stack_destroy(pMain);
        element_destroy(ele);
        return FALSE;
    }
    
    element_destroy(ele);
    
    while(stack_isEmpty(pMain)==FALSE){
        ele = stack_pop(pMain);
        nodoAux = (Node *) element_getInfo(ele);
        if(marcado(nodoAux, arrayMarcados, nNodos)==FALSE){
            etiquetar_nodo(nodoAux, arrayMarcados, contador);
            contador++;
            
            arrayConectados = graph_getConnectionsFrom(g, node_getId(nodoAux));
            /* si no hay mas caminos y el nodo aux es el destino, devuelvo TRUE */
            if(mas_caminos(g, nodoAux, arrayConectados, arrayMarcados)==FALSE){
                if(node_getId(nodoAux) == node_getId(nGoal)){
                    free(arrayConectados);
                    free(arrayMarcados);
                    element_destroy(ele);
                    stack_destroy(pMain);
                    return TRUE;
                }
            }
            
            
            for(i=0; i<graph_getNumberOfConnectionsFrom(g, node_getId(element_getInfo(ele))); i++){
                if(arrayConectados[i] == node_getId(nGoal)){
                    free(arrayConectados);
                    free(arrayMarcados);
                    element_destroy(ele);
                    stack_destroy(pMain);
                    return TRUE;
                }
                else{
                    element_destroy(ele);
                    ele=element_ini();
                    nodoAux2 = graph_getNode(g, arrayConectados[i]);
                    ele = element_setInfo(ele, nodoAux2);
                    stack_push(pMain, ele);
                    node_destroy(nodoAux2);
                }             
            }
            free(arrayConectados);
            element_destroy(ele);
        } 
            
    }
    free(arrayMarcados);
    stack_destroy(pMain);
    
    return FALSE;
}


int main(int argc, char** argv){
    Graph * g = NULL;
    Node *nAux1, *nAux2;
    int IdSource, IdTarget;
    
    if (argc < 4){
	fprintf(stdout, "Parametros de entrada insuficientes: %d\n", argc);
	fprintf(stdout, "Introduzca el nombre del programa, nombre del fichero de texto con el grafo, ID del nodo origen e ID del nodo destino.\n");
	return -1;
    }
    
    IdSource = atoi(argv[2]);
    IdTarget = atoi(argv[3]);
    /*OBERSVACION: Por defecto en el fichero "grafo.txt" contiene el grafo 2 subido en Moodle
     para la comprobacion de la practica 1. Si desea probar otro grafo, modifique el contenido
     del fichero "grafo.txt" que se encuentra en la carpeta P2_E2*/
    g = read_graph_from_file(argv[1]);
    if(g==NULL){
        return -1;
    }
    nAux1 = graph_getNode(g, IdSource);
    nAux2 = graph_getNode(g, IdTarget);
    if(recorrer(g, nAux1, nAux2)==TRUE){
        printf("SI existe un camino entre el nodo de ID %d y el nodo de ID %d.", IdSource, IdTarget);
    }
    else{
        printf("NO existe un camino entre el nodo de ID %d y el nodo de ID %d.",IdSource, IdTarget);
    }
    node_destroy(nAux1);
    node_destroy(nAux2);
    graph_destroy(g);
       
    return 0;
}
