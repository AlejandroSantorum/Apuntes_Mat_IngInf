#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

struct _Graph{
    Node *nodos[MAX_NODES];
    int matriz[MAX_NODES][MAX_NODES];
    int numNodes;
};

Graph * graph_ini(){
    Graph *g;
    int i,j;
   
    g = (Graph *) malloc(sizeof(Graph));
    if(g==NULL){
        return NULL;
    }
    
    /*Escribimos 0 en todas las posiciones de nuestra matriz de adyacencia
     ya que el nodo no tiene aristas de serie.*/
    for(i=0;i<MAX_NODES;i++){
        for(j=0;j<MAX_NODES;j++){
            g->matriz[i][j]=0;
        }
    }
    
    g->numNodes = 0;
    
    return g;
}


void graph_destroy(Graph * g){
    int i;
    
    if(g==NULL){
        return;
    }
    
    /*Liberamos primero la memoria reservada para cada uno de los nodos*/
    for(i=0;i<g->numNodes;i++){
        node_destroy(g->nodos[i]);
    }
    
    /*Y ahora podemos liberar el grafo*/
    free(g);
}


int graph_getNnodes(const Graph * g){
    if(g==NULL){
        return -1;
    }
    
    return g->numNodes;
}


int* graph_getNodeIds(const Graph * g){
    int *nNodes;
    int i;
    
    if(g==NULL){
        return NULL;
    }
    
    /*Reservamos memoria para el array de punteros a enteros*/
    nNodes = (int *) malloc (g->numNodes*sizeof(int));
    if(nNodes == NULL){
        return NULL;
    }
    
    for(i=0;i<g->numNodes;i++){
        nNodes[i] = node_getId(g->nodos[i]);
    }
    
    return nNodes;
}


int graph_getNedges(const Graph * g){
    int i, j, nEdges=0 ;
    
    if(g==NULL){
        return -1;
    }
    
    /*Percorremos la matriz con un doble bucle buscando los "1"*/
    for(i=0; i<g->numNodes; i++){
        for(j=0; j<g->numNodes; j++){
            if(g->matriz[i][j]==1){
                nEdges++;
            }
        }
    }
    
    return nEdges;
}

Graph * graph_addNode(Graph * g, const Node* n){
    int *ids;
    int i;
    
    if(g==NULL || n==NULL || g->numNodes == MAX_NODES){
        return NULL;
    }
    
    /*AyudÃ¡ndonos de la funciÃ³n graph_getNodeIds podemos averiguar si el
     nodo que se quiere introducir tiene el mismo Id que alguno ya existente
     en el grafo*/
    ids = graph_getNodeIds(g);
    for(i=0; i<g->numNodes; i++){
        if(ids[i]==node_getId(n)){
            printf("Id del nodo repetida, el grafo no se ha modificado con Ã©xito.\n");
            return NULL;
        }
    }
    free(ids);
    
    g->nodos[g->numNodes] = node_copy(n);
    if(g->nodos[g->numNodes]==NULL){
        return NULL;
    }
    
    g->numNodes++;
    return g;
}

int find_node_index(const Graph *g, int nId1){
    int i;
    
    if(g==NULL){
        return -1;
    }
    
    for(i=0;i<g->numNodes;i++){
        if(nId1==node_getId(g->nodos[i])){
            return i;
        }
    }
    
    /*Si el bucle anterior no encuentra una correspondencia entre el Id especificado
     y el Id de alguno de los nodos se devuelve directamente -1*/
    return -1;
}


Graph * graph_addEdge(Graph * g, const int nId1, const int nId2){
    int a,b;
    
    if(g==NULL){
        return NULL;
    }
    
    a = find_node_index(g,nId1);
    if(a==-1)
        return NULL;
    b = find_node_index(g,nId2);
    if(b==-1)
        return NULL;
    
    g->matriz[a][b]=1;
    
    return g;
}

Node * graph_getNode(const Graph * g, int nId){
    int a;
    Node *ncpy;
    
    if(g==NULL){
        return NULL;
    }
    
    a = find_node_index(g, nId);
    
    ncpy = node_copy(g->nodos[a]);
    if(ncpy==NULL){
        return NULL;
    }
    
    return ncpy;
}


Bool graph_areConnected(const Graph *g, const int nId1, const int nId2){
    int a, b;
    if(g==NULL){
        return FALSE;
    }
    
    a = find_node_index(g, nId1);
    if(a==-1)
        return FALSE;
    b = find_node_index(g, nId2);
    if(b==-1)
        return FALSE;
    
    if(g->matriz[a][b]==1){
        return TRUE;
    }
    
    return FALSE;
}

int graph_getNumberOfConnectionsFrom(const Graph *g, const int fromId){
    int a, i, nConnections=0;
    
    if(g==NULL){
        return -1;
    }
    
    a = find_node_index(g,fromId);
    
    for(i=0;i<g->numNodes;i++){
        if(g->matriz[a][i]==1){
            nConnections++;
        }
    }
    
    return nConnections;
}


int* graph_getConnectionsFrom(const Graph * g, const int fromId){
    int i, a, j=0;
    int *nConnections;
    
    if(g==NULL){
        return NULL;
    }
    
    /*Reservamos memoria para un array de punteros a entero del tamaÃ±o del
     nÃºmero de conexiones que tiene el nodo con Id expecificado*/
    nConnections = (int *) malloc (graph_getNumberOfConnectionsFrom(g, fromId)*sizeof(int));
    if(nConnections == NULL){
        return NULL;
    }
    
    a = find_node_index(g,fromId);
    
    /*Percorremos la matriz de adyacencia por la fila del nodo con el Id especificado
     buscando conexiones y aumentando el contador auxiliar "nConnections*/
    for(i=0;i<g->numNodes;i++){
        if(g->matriz[a][i]==1){
            nConnections[j]=node_getId(g->nodos[i]);
            j++;
        }
    }
    
    return nConnections;
}



int graph_getNumberOfConnectionsTo(const Graph * g, const int toId){
    int a, i, nConnections=0;
    
    if(g==NULL){
        return -1;
    }
    
    a = find_node_index(g,toId);
    
    /*Percorremos la matriz de adyacencia por la columna del nodo con el Id especificado
     buscando conexiones y aumentando el contador auxiliar "nConnections*/
    for(i=0;i<g->numNodes;i++){
        if(g->matriz[i][a]==1){
            nConnections++;
        }
    }
    
    return nConnections;
}


int* graph_getConnectionsTo(const Graph * g, const int toId){
    int i, a, j=0;
    int *nConnections;
    
    if(g==NULL){
        return NULL;
    }
    
    /*Reservamos memoria para un array de punteros a enteros con el tamaÃ±o del nÃºmero
     de conexiones desde el nodo con Id especificado*/
    nConnections = (int *) malloc (graph_getNumberOfConnectionsFrom(g, toId)*sizeof(int));
    if(nConnections == NULL){
        return NULL;
    }
    
    a = find_node_index(g,toId);
    
    for(i=0;i<g->numNodes;i++){
        if(g->matriz[i][a]==1){
            nConnections[j]=node_getId(g->nodos[i]);
            j++;
        }
    }
    
    return nConnections;   
}


int graph_print(FILE *pf, const Graph * g){
    int i, j, num=0;
    
    if(pf==NULL || g==NULL){
        return -1;
    }
    
    num = fprintf(pf, "N=%d, E=%d:\r\n", g->numNodes, graph_getNedges(g)); /*El \r\n es el comando para salto de lÃ­nea en el bloc de notas de windows.*/
    
    for(i=0; i<g->numNodes; i++){
        
        num += fprintf(pf, "[%d, %s]->", node_getId(g->nodos[i]), node_getName(g->nodos[i]));
        for(j=0; j<g->numNodes; j++){
            if(graph_areConnected(g, node_getId(g->nodos[i]), node_getId(g->nodos[j]))==TRUE){
                num += fprintf(pf, " 1");
            }
            else{
                num += fprintf(pf, " 0");
            }
        }
        fprintf(pf, "\r\n"); 
    }
    
    return num;
}

