/**
*  Project: Assignment 1, 2 and 3 - ProgII subject
*  File: graph_list.c
*  Version: 2.0
*  Date: Apr 17, 2017
*  Revision date: May 31, 2018
*
*  (C) Alejandro Santorum Varela
*  alejandro.santorum@gmail.com
*
*/
#include <stdio.h>
#include <stdlib.h>
#include "graph_list.h"
#include "list.h"
#include "functions.h"

/** Graph data structure using lists to represent the adyacency matrix */
struct _Graph{
    Node *nodes[MAX_NODES];
    List *out_connections[MAX_NODES];
    List *in_connections[MAX_NODES];
    int numNodes;
};


/**
*  Initializes a graph, allocating memory and returning the initialized graph on success, MULL otherwise
*/
Graph* graph_ini(){
   Graph *g=NULL;
   int i;

   g = (Graph *) malloc(sizeof(Graph));
   if(!g){ /* Memory error */
      printf("Graph Error: unable to allocate memory for a new graph in graph_ini function\n");
      return NULL;
   }

   for(i=0;i<MAX_NODES;i++){
      g->out_connections[i] = NULL;
      g->in_connections[i] = NULL;
   }
   g->numNodes = 0;
   return g;
}

/**
*  It frees the memory allocated for a given graph
*/
void graph_destroy(Graph *g){
   int i;

   if(!g){ /* Trying to free a NULL graph */
      printf("Graph Warning: NULL pointer in graph_destroy function\n");
      return;
   }

   /* Freeing adyacency lists */
   for(i=0; i<g->numNodes; i++){
      list_destroy(g->out_connections[i]);
      list_destroy(g->in_connections[i]);
   }
   /* Freeing nodes */
   for(i=0;i<g->numNodes;i++){
      node_destroy(g->nodes[i]);
   }
   free(g);
}

/**
*  PRIVATE FUNCTION: it helps to find the index of a node with ID=nId1 in hte graph's data structure.
*  It returns the index, or -1 if any error is produced
*/
int find_node_index(Graph *g, int nId1){
   int i;

   if(!g) return -1;

   for(i=0;i<g->numNodes;i++){
      if(nId1==node_getId(g->nodes[i])){
         return i;
      }
   }
   return -1; /* No node with the given ID */
}

/**
*  Returns the number of nodes of a given graph
*/
int graph_getNnodes(Graph *g){
   if(!g){ /* Error */
      printf("Graph Error: NULL pointer in graph_getNnodes function\n");
      return -1;
   }

   return g->numNodes;
}

/**
*  Returns a array of ID's of all the nodes contained in the given graph allocating memory for it.
*  If any error occurs, NULL is returned
*/
int* graph_getNodeIds(Graph *g){
   int *nodesIds=NULL;
   int i;

   if(!g){ /* Error */
      printf("Graph Error: NULL pointer in graph_getNodeIds function\n");
      return NULL;
   }

   nodesIds = (int *) malloc(g->numNodes*sizeof(int)); /* Allocating memory for the array */
   if(!nodesIds){ /* Error */
      printf("Graph Error: unable to allocate memory for the array of ID's in graph_getNodeIds function\n");
      return NULL;
   }

   for(i=0; i<g->numNodes; i++){
      nodesIds[i] = node_getId(g->nodes[i]);
   }
   return nodesIds;
}

/**
*  Returns the number of connections that are contained in the given graph, -1 if any error occurs
*/
int graph_getNedges(Graph *g){
   int i, nEdges=0 ;

   if(!g){ /* Error */
      printf("Graph Error: NULL pointer in graph_getNedges function\n");
      return -1;
   }

   /* The number of edges is equal than the total number of elements there are in the lists */
   for(i=0; i<g->numNodes; i++){
      nEdges = nEdges + list_size(g->out_connections[i]); /* With g->in_connection[i] would work too */
   }
   return nEdges;
}

/**
*  A new node is introduced into the graph. A node is given as a parameter, and a COPY of that
*  is added to the graph. It returns the modified graph, or NULL if any error appears
*/
Graph* graph_addNode(Graph *g, Node* n){
   destroy_elementlist_function_type f1 = destroy_intp_function;
   copy_elementlist_function_type f2 = copy_intp_function;
   print_elementlist_function_type f3 = print_intp_function;
   cmp_elementlist_function_type f4 = cmp_intp_function;
   int *ids;
   int i, id;

   /* Error checking */
   if(!g){ /* Error */
      printf("Graph Error: graph NULL pointer in graph_addNode function\n");
      return NULL;
   }
   if(!n){ /* Error */
      printf("Graph Error: node NULL pointer in graph_addNode function\n");
      return NULL;
   }
   if(g->numNodes==MAX_NODES){ /* Error */
      printf("Graph Error: reached maximum number of nodes, unable to add a new one\n");
      return NULL;
   }

   /* Checking if there is another node with the same ID */
   ids = graph_getNodeIds(g);
   if(!ids){ /* Error */
      printf("Graph Error: unable to get the array of ID's in graph_addNode function\n");
      return NULL;
   }
   id = node_getId(n);
   for(i=0; i<g->numNodes; i++){
      if(ids[i]==id){ /* Error */
         printf("Graph Error: there is already a node with ID = %d\n", id);
         return NULL;
      }
   }
   free(ids);

   /* Copying it */
   g->nodes[g->numNodes] = node_copy(n);
   if(!g->nodes[g->numNodes]){ /* Error */
      printf("Graph Error: unable to copy the node to add it to the graph in graph_addEdge function\n");
      return NULL;
   }

   g->out_connections[g->numNodes] = list_ini(f1, f2, f3, f4);
   if(!g->out_connections[g->numNodes]){ /* Error */
      printf("Graph Error: unable to allocate memory for adyacency list (out) in graph_addEdge function\n");
      return NULL;
   }
   g->in_connections[g->numNodes] = list_ini(f1, f2, f3, f4);
   if(!g->in_connections[g->numNodes]){ /* Error */
      printf("Graph Error: unable to allocate memory for adyacency list (in) in graph_addEdge function\n");
      return NULL;
   }
   g->numNodes++;
   return g;
}

/**
*  A new connection is introduced into the graph, from node with ID=nId1 to node with ID=nId2.
*  It returns the modified graph, NULL otherwise
*/
Graph* graph_addEdge(Graph *g, int nId1, int nId2){
    int a,b;

   if(!g){ /* Error */
      printf("Graph Error: graph NULL pointer in graph_addEdge function\n");
      return NULL;
   }

   a = find_node_index(g,nId1);
   if(a==-1){ /* Error */
      printf("Graph Error: there is no node with ID = %d in the graph, in graph_addEdge function\n", nId1);
      return NULL;
   }
   b = find_node_index(g,nId2);
   if(b==-1){ /* Error */
      printf("Graph Error: there is no node with ID = %d in the graph, in graph_addEdge function\n", nId2);
      return NULL;
   }

   /* Similar to g->matriz[a][b]=1; */
   list_insertLast(g->out_connections[a], &nId2);
   if(!g->out_connections[a]){
      printf("Graph Error: unable to introduce the connection (out) in graph_addEdge function\n");
      return NULL;
   }
   list_insertLast(g->in_connections[b], &nId1);
   if(!g->in_connections[b]){
      printf("Graph Error: unable to introduce the connection (in) in graph_addEdge function\n");
      return NULL;
   }
   return g;
}

/**
*  Returns a pointer to A COPY (new allocated memory) of the node with ID=nId.
*  If it is not found, NULL is returned
*/
Node * graph_getNode(Graph * g, int nId){
   int a;
   Node *ncpy=NULL;

   if(!g){ /* Error */
      printf("Graph Error: graph NULL pointer in graph_getNode function\n");
      return NULL;
   }

   a = find_node_index(g, nId);
   if(a==-1){ /* Error */
      printf("Graph Error: there is no node with ID = %d in the graph, in graph_getNode function\n", nId);
   }

   ncpy = node_copy(g->nodes[a]);
   if(!ncpy){ /* Error */
      printf("Graph Error: unable to copy the node to add it to the graph in graph_getNode function\n");
      return NULL;
   }
   return ncpy;
}

/**
*  Checks if two nodes are connected (from nId1 node to nId2 node),
*  returning TRUE in affirmative case, or FALSE otherwise
*/
Bool graph_areConnected(Graph *g, int nId1, int nId2){
    int a;

   if(!g){ /* Error */
      printf("Graph Error: graph NULL pointer in graph_areConnected function\n");
      return FALSE;
   }

   a = find_node_index(g,nId1);
   if(a==-1){ /* Error */
      printf("Graph Error: there is no node with ID = %d in the graph, in graph_areConnected function\n", nId1);
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

/**
*  Returns the number of connections FROM a given node (its ID is used as a parameter).
*  If there're none, -1 is returned
*/
int graph_getNumberOfConnectionsFrom(Graph *g, int fromId){
    int a;

   if(!g){ /* Error */
      printf("Graph Error: graph NULL pointer in graph_getNumberOfConnectionsFrom function\n");
      return -1;
   }

   a = find_node_index(g,fromId);
   if(a==-1){ /* Error */
      printf("Graph Error: there is no node with ID = %d in the graph, in graph_getNumberOfConnectionsFrom function\n", fromId);
      return -1;
   }

   /*for(i=0;i<g->numNodes;i++){
      if(g->matriz[a][i]==1){
         nConnections++;
      }
   }*/
   return  list_size(g->out_connections[a]);
}

/**
*  Returns a list with the node ID'S connected FROM a given node (its ID is used as a parameter).
*  NULL is returned in error case
*/
int* graph_getConnectionsFrom(Graph *g, int fromId){
   int a, i, j;
   int *nConnections=NULL;
   int *aux=NULL;

   if(!g){ /* Error */
      printf("Graph Error: graph NULL pointer in graph_getConnectionsFrom function\n");
      return NULL;
   }

   nConnections = (int *) malloc(graph_getNumberOfConnectionsFrom(g, fromId)*sizeof(int));
   if(!nConnections){ /* Error */
      printf("Graph Error: unable to get the array of connection from the node %d in graph_getConnectionsFrom function\n", fromId);
      return NULL;
   }

   a = find_node_index(g,fromId);
   if(a==-1){ /* Error */
      printf("Graph Error: there is no node with ID = %d in the graph, in graph_getConnectionsFrom function\n", fromId);
      return NULL;
   }
   /*
   for(i=0;i<g->numNodes;i++){
      if(g->matriz[a][i]==1){
         nConnections[j]=node_getId(g->nodos[i]);
         j++;
      }
   }*/
   for(i=0, j=0; i<list_size(g->out_connections[a]); i++, j++){
      aux = list_get(g->out_connections[a], i);
      nConnections[j] = *(aux);
      free(aux);
   }
   return nConnections;
}

/**
*  Returns the number of connections TO a given node (its ID is used as a parameter).
*  If there're none, -1 is returned
*/
int graph_getNumberOfConnectionsTo(Graph * g, int toId){
   int a;

   if(!g){ /* Error */
      printf("Graph Error: graph NULL pointer in graph_getNumberOfConnectionsTo function\n");
      return -1;
   }

   a = find_node_index(g,toId);
   if(a==-1){ /* Error */
      printf("Graph Error: there is no node with ID = %d in the graph, in graph_getNumberOfConnectionsTo function\n", toId);
      return -1;
   }
   /*
   for(i=0;i<g->numNodes;i++){
      if(g->matriz[i][a]==1){
         nConnections++;
      }
   }*/
   return list_size(g->in_connections[a]);
}

/**
*  Returns a list with the node ID's connected TO a given node (its ID is used as a parameter).
*  NULL is returned in error case
*/
int* graph_getConnectionsTo(Graph *g, int toId){
    int i, j, a;
    int *nConnections=NULL;
    int *aux=NULL;

   if(!g){ /* Error */
      printf("Graph Error: graph NULL pointer in graph_getConnectionsTo function\n");
      return NULL;
   }

   nConnections = (int *) malloc(graph_getNumberOfConnectionsTo(g, toId)*sizeof(int));
   if(!nConnections){ /* Error */
      printf("Graph Error: unable to get the array of connection from the node %d in graph_getConnectionsTo function\n", toId);
      return NULL;
   }

   a = find_node_index(g,toId);
   if(a==-1){ /* Error */
      printf("Graph Error: there is no node with ID = %d in the graph, in graph_getConnectionsTo function\n", toId);
      return NULL;
   }
   /*
   for(i=0;i<g->numNodes;i++){
      if(g->matriz[i][a]==1){
         nConnections[j]=node_getId(g->nodos[i]);
         j++;
      }
   }*/
   for(i=0, j=0; i<list_size(g->in_connections[a]); i++, j++){
      aux = list_get(g->in_connections[a], i);
      nConnections[j] = *(aux);
      free(aux);
   }
   return nConnections;
}

/**
*  Prints in the given FILE *pf the data of a graph, returning the number of written characters.
*  The followed format is: in the first line the total number of nodes and connections and then,
*  for each line, the node data and the adjacency matrix.
*  Example:
*  NumNodes = 3, NumConnections=3:
*  [1, a] -> 0 1 1
*  [2, b] -> 0 0 1
*  [3, c] -> 1 0 0
*/
int graph_print(FILE *pf, Graph *g){
   int i, j, num=0;

   if(!pf){ /* Error */
      printf("Graph Error: file NULL pointer in graph_print function\n");
      return -1;
   }
   if(!g){ /* Error */
      printf("Graph Error: graph NULL pointer in graph_print function\n");
      return -1;
   }

   num = fprintf(pf, "N=%d, E=%d:\n", g->numNodes, graph_getNedges(g));

   for(i=0; i<g->numNodes; i++){
      num += fprintf(pf, "[%d, %s]->", node_getId(g->nodes[i]), node_getName(g->nodes[i]));
      for(j=0; j<g->numNodes; j++){
         if(graph_areConnected(g, node_getId(g->nodes[i]), node_getId(g->nodes[j]))==TRUE){
            num += fprintf(pf, " 1");
         } else{
            num += fprintf(pf, " 0");
         }
      }
      fprintf(pf, "\n");
   }
   return num;
}
