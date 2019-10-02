#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

struct _Graph{
    Node *nodes[MAX_NODES];
    List *out_connections[MAX_NODES];
    List *in_connections[MAX_NODES];
    int numNodes;
};

Graph * graph_ini(){
    Graph *g;
    int i;
    
    g = (Graph *) malloc(sizeof(Graph));
    if(g==NULL){
        return NULL;
    }
    
    /*Ponemos todos los punteros a listas a NULL*/
    for(i=0;i<MAX_NODES;i++){
        g->out_connections[i] = NULL;
        g->in_connections[i] = NULL;
    }
    
    g->numNodes = 0;
    
    return g;
}


void graph_destroy(Graph * g){
    int i;
    
    if(g==NULL){
        return;
    }
    
    /*Liberamos cada una de las Listas de adyacencia*/
    for(i=0; i<g->numNodes; i++){
        list_free(g->out_connections[i]);
        list_free(g->in_connections[i]);
    }
    
    /*Liberamos la memoria reservada para cada uno de los nodos*/
    for(i=0;i<g->numNodes;i++){
        node_destroy(g->nodes[i]);
    }
    
    free(g);
    g = NULL;
}


int graph_getNnodes(const Graph *g){
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
        nNodes[i] = node_getId(g->nodes[i]);
    }
    
    return nNodes;
}


int graph_getNedges(const Graph *g){
    int i, nEdges=0 ;
    
    if(g==NULL){
        return -1;
    }
    
    /*El número de aristas es igual al número total de elementos de todas las listas*/
    for(i=0; i<g->numNodes; i++){
        nEdges = nEdges + list_size(g->out_connections[i]);/*Podríamos haberlo implementado también*/
    }                                                      /*con g->in_connections[i]*/
    
    return nEdges;
}

Graph * graph_addNode(Graph * g, const Node* n){
    destroy_elementlist_function_type f1;
    copy_elementlist_function_type f2;
    print_elementlist_function_type f3;
    cmp_elementlist_function_type f4;
    int *ids;
    int i, id;
    
    if(g==NULL || n==NULL || g->numNodes == MAX_NODES){
        return NULL;
    }
    
    f1 = destroy_intp_function;
    f2 = copy_intp_function;
    f3 = print_intp_function;
    f4 = cmp_intp_function;
    
    /*Ayudándonos de la función graph_getNodeIds podemos averiguar si el
     nodo que se quiere introducir tiene el mismo Id que alguno ya existente
     en el grafo*/
    ids = graph_getNodeIds(g);
    id = node_getId(n);
    for(i=0; i<g->numNodes; i++){
        if(ids[i] == id){
            printf("Id del nodo repetido, el grafo no se ha modificado con éxito.\n");
            free(ids);
            return g;
        }
    }
    
    g->nodes[g->numNodes] = node_copy(n);
    if(g->nodes[g->numNodes]==NULL){
        return NULL;
    }
    
    g->out_connections[g->numNodes] = list_ini(f1, f2, f3, f4);
    if(g->out_connections[g->numNodes] == NULL){
        return NULL;
    }
    g->in_connections[g->numNodes] = list_ini(f1, f2, f3, f4);
    if(g->in_connections[g->numNodes] == NULL){
        return NULL;
    }
    
    free(ids);
    g->numNodes++;
    return g;
}

int find_node_index(const Graph *g, int nId1){
    int i;
    
    if(g==NULL){
        return -1;
    }
    
    for(i=0;i<g->numNodes;i++){
        if(nId1==node_getId(g->nodes[i])){
            return i;
        }
    }
    
    /*Si el bucle anterior no encuentra una correspondencia entre el Id especificado
     y el Id de alguno de los nodos se devuelve directamente -1*/
    return -1;
}


Graph * graph_addEdge(Graph * g, int nId1, int nId2){
    int a,b;
    
    if(g==NULL){
        return NULL;
    }
    
    a = find_node_index(g, nId1);
    if(a==-1){
        return NULL;
    }
    
    b = find_node_index(g, nId2);
    if(b==-1){
        return NULL;
    }
    
    /*g->matriz[a][b]=1;*/
    list_insertLast(g->out_connections[a], &nId2);
    if(g->out_connections[a] == NULL){
        return NULL;
    }
    list_insertLast(g->in_connections[b], &nId1);
    if(g->in_connections[b] == NULL){
        return NULL;
    }
    
    return g;
}

Node * graph_getNode(const Graph * g, int nId){
    int a;
    Node *ncpy;
    
    if(g==NULL){
        return NULL;
    }
    
    a = find_node_index(g, nId);
    if(a==-1){
        return NULL;
    }
    
    ncpy = node_copy(g->nodes[a]);
    
    return ncpy;
}


Bool graph_areConnected(const Graph *g, int nId1, int nId2){
    int a;
    
    if(g==NULL){
        return FALSE;
    }
    
    a = find_node_index(g, nId1);
    if(a==-1){
        return FALSE;
    }
    
    /*
    if(g->matriz[a][b]==1){
        return TRUE;
    }
    */
    if(list_isElement(g->out_connections[a], &nId2)==TRUE){
        return TRUE;
    }
    
    return FALSE;
}

int graph_getNumberOfConnectionsFrom(const Graph *g, const int fromId){
    int a, nConnections=0;
    
    if(g==NULL){
        return -1;
    }
    
    a = find_node_index(g,fromId);
    
    /*for(i=0;i<g->numNodes;i++){
        if(g->matriz[a][i]==1){
            nConnections++;
        }
    }*/
    nConnections = list_size(g->out_connections[a]);
    
    return nConnections;
}


int* graph_getConnectionsFrom(const Graph * g, const int fromId){
    int a, i, j;
    int *nConnections;
    int *aux=NULL;
    
    if(g==NULL){
        return NULL;
    }
    
    /*Reservamos memoria para un array de punteros a entero del tamaño del
     número de conexiones que tiene el nodo con Id expecificado*/
    nConnections = (int *) malloc (graph_getNumberOfConnectionsFrom(g, fromId)*sizeof(int));
    if(nConnections == NULL){
        return NULL;
    }
    
    a = find_node_index(g,fromId);
    
    /*
    for(i=0;i<g->numNodes;i++){
        if(g->matriz[a][i]==1){
            nConnections[j]=node_getId(g->nodos[i]);
            j++;
        }
    }*/
    for(i=1, j=0; i<=list_size(g->out_connections[a]); i++, j++){
        aux = list_get(g->out_connections[a], i);
        nConnections[j] = *(aux);
        free(aux);
    }
    
    return nConnections;
}



int graph_getNumberOfConnectionsTo(const Graph * g, const int toId){
    int a, nConnections=0;
    
    if(g==NULL){
        return -1;
    }
    
    a = find_node_index(g,toId);
    
    /*
    for(i=0;i<g->numNodes;i++){
        if(g->matriz[i][a]==1){
            nConnections++;
        }
    }*/
    nConnections = list_size(g->in_connections[a]);
    
    return nConnections;
}


int* graph_getConnectionsTo(const Graph *g, const int toId){
    int i, j, a;
    int *nConnections;
    int *aux=NULL;
    
    if(g==NULL){
        return NULL;
    }
    
    /*Reservamos memoria para un array de punteros a enteros con el tamaño del número
     de conexiones desde el nodo con Id especificado*/
    nConnections = (int *) malloc (graph_getNumberOfConnectionsTo(g, toId)*sizeof(int));
    if(nConnections == NULL){
        return NULL;
    }
    
    a = find_node_index(g,toId);
    
    /*
    for(i=0;i<g->numNodes;i++){
        if(g->matriz[i][a]==1){
            nConnections[j]=node_getId(g->nodos[i]);
            j++;
        }
    }*/
    for(i=1, j=0; i<=list_size(g->in_connections[a]); i++, j++){
        aux = list_get(g->in_connections[a], i);
        nConnections[j] = *(aux);
        free(aux);
    }
    
    return nConnections;   
}


int graph_print(FILE *pf, const Graph * g){
    int i, j, num=0;
    
    if(pf==NULL || g==NULL){
        return -1;
    }
    
    num = fprintf(pf, "N=%d, E=%d:\n", g->numNodes, graph_getNedges(g));
    
    for(i=0; i<g->numNodes; i++){
        num += fprintf(pf, "[%d, %s]->", node_getId(g->nodes[i]), node_getName(g->nodes[i]));
        for(j=0; j<g->numNodes; j++){
            if(graph_areConnected(g, node_getId(g->nodes[i]), node_getId(g->nodes[j]))==TRUE){
                num += fprintf(pf, " 1");
            }
            else{
                num += fprintf(pf, " 0");
            }
        }
        fprintf(pf, "\n"); 
    }
    
    return num;
}

