/**
*  Project: Assignment 1, 2 and 3- ProgII subject
*  File: graph.c
*  Version: 2.0
*  Date: Feb 20, 2017
*  Revision date: May 26, 2018
*
*  (C) Alejandro Santorum Varela
*  alejandro.santorum@gmail.com
*
*/
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

/** Graph data structure */
struct _Graph{
    Node *nodes[MAX_NODES]; /* Array of nodes */
    int matrix[MAX_NODES][MAX_NODES]; /* Adjacency matrix */
    int numNodes; /* Total number of nodes */
};

/**
*  Initializes a graph, allocating memory and returning the initialized graph on success, MULL otherwise
*/
Graph* graph_ini(){
   Graph *g=NULL;
   int i,j;

   g = (Graph *) malloc(sizeof(Graph));
   if(!g){ /* Memory error */
      printf("Graph Error: unable to allocate memory for a new graph in graph_ini function\n");
      return NULL;
   }

   for(i=0; i<MAX_NODES; i++){
      for(j=0; j<MAX_NODES; j++){
         g->matrix[i][j]=0; /* There is no connections at the beginning */
      }
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

   for(i=0; i<g->numNodes; i++){
      node_destroy(g->nodes[i]); /* Freeing allocated nodes */
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
   int i, j, nEdges=0;

   if(!g){ /* Error */
      printf("Graph Error: NULL pointer in graph_getNedges function\n");
      return -1;
   }

   for(i=0; i<g->numNodes; i++){
      for(j=0; j<g->numNodes; j++){
         if(g->matrix[i][j]==1){
            nEdges++;
         }
      }
   }
   return nEdges;
}

/**
*  A new node is introduced into the graph. A node is given as a parameter, and a COPY of that
*  is added to the graph. It returns the modified graph, or NULL if any error appears
*/
Graph* graph_addNode(Graph *g, Node *n){
   int *ids=NULL;
   int i;

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
   for(i=0; i<g->numNodes; i++){
      if(ids[i]==node_getId(n)){ /* Error */
         printf("Graph Error: there is already a node with ID = %d\n", ids[i]);
         return NULL;
      }
   }
   free(ids);

   /* Copying it */
   g->nodes[g->numNodes] = node_copy(n);
   if(!g->nodes[g->numNodes]){ /* Error */
      printf("Graph Error: unable to copy the node to add it to the graph IN graph_addEdge function\n");
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
   g->matrix[a][b]=1; /* Adding edge */
   return g;
}

/**
*  Returns a pointer to A COPY (new allocated memory) of the node with ID=nId.
*  If it is not found, NULL is returned
*/
Node* graph_getNode(Graph *g, int nId){
   int a;
   Node *ncpy=NULL;

   if(!g){ /* Error */
      printf("Graph Error: graph NULL pointer in graph_getNode function\n");
      return NULL;
   }

   a = find_node_index(g, nId);
   if(a==-1){ /* Error */
      printf("Graph Error: there is no node with ID = %d in the graph\n", nId);
      return NULL;
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
   int a, b;

   if(!g){ /* Error */
      printf("Graph Error: graph NULL pointer in graph_areConnected function\n");
      return FALSE;
   }

   a = find_node_index(g,nId1);
   if(a==-1){ /* Error */
      printf("Graph Error: there is no node with ID = %d in the graph, in graph_areConnected function\n", nId1);
      return FALSE;
   }
   b = find_node_index(g,nId2);
   if(b==-1){ /* Error */
      printf("Graph Error: there is no node with ID = %d in the graph, in graph_areConnected function\n", nId2);
      return FALSE;
   }

   if(g->matrix[a][b]==1){
      return TRUE;
   } else{
      return FALSE;
   }
}

/**
*  Returns the number of connections FROM a given node (its ID is used as a parameter).
*  If there're none, -1 is returned
*/
int graph_getNumberOfConnectionsFrom(Graph *g, int fromId){
   int a, i, nConnections=0;

   if(!g){ /* Error */
      printf("Graph Error: graph NULL pointer in graph_getNumberOfConnectionsFrom function\n");
      return -1;
   }

   a = find_node_index(g,fromId);
   if(a==-1){ /* Error */
      printf("Graph Error: there is no node with ID = %d in the graph, in graph_getNumberOfConnectionsFrom function\n", fromId);
      return -1;
   }

   for(i=0; i<g->numNodes; i++){
      if(g->matrix[a][i]==1){ /* Checking connections through row a of the adjacency matrix*/
         nConnections++;
      }
   }
   return nConnections;
}

/**
*  Returns a list with the node ID'S connected FROM a given node (its ID is used as a parameter).
*  NULL is returned in error case
*/
int* graph_getConnectionsFrom(Graph *g, int fromId){
   int i, a, j=0;
   int *nConnections=NULL;

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

   for(i=0; i<g->numNodes; i++){
      if(g->matrix[a][i]==1){ /* Checking connections through row a of the adjacency matrix*/
         nConnections[j]=node_getId(g->nodes[i]);
         j++;
      }
   }
   return nConnections;
}

/**
*  Returns the number of connections TO a given node (its ID is used as a parameter).
*  If there're none, -1 is returned
*/
int graph_getNumberOfConnectionsTo(Graph *g, int toId){
   int a, i, nConnections=0;

   if(!g){ /* Error */
      printf("Graph Error: graph NULL pointer in graph_getNumberOfConnectionsTo function\n");
      return -1;
   }

   a = find_node_index(g,toId);
   if(a==-1){ /* Error */
      printf("Graph Error: there is no node with ID = %d in the graph, in graph_getNumberOfConnectionsTo function\n", toId);
      return -1;
   }

   for(i=0; i<g->numNodes; i++){
      if(g->matrix[i][a]==1){ /* Checking connections through column a of the adjacency matrix*/
         nConnections++;
      }
   }
   return nConnections;
}

/**
*  Returns a list with the node ID's connected TO a given node (its ID is used as a parameter).
*  NULL is returned in error case
*/
int* graph_getConnectionsTo(Graph *g, int toId){
   int i, a, j=0;
   int *nConnections=NULL;

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

   for(i=0;i<g->numNodes;i++){
      if(g->matrix[i][a]==1){ /* Checking connections through column a of the adjacency matrix*/
         nConnections[j]=node_getId(g->nodes[i]);
         j++;
      }
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

   num = fprintf(pf, "NumNodes=%d, NumConnections=%d:\n", g->numNodes, graph_getNedges(g));

   for(i=0; i<g->numNodes; i++){
      num += fprintf(pf, "[%d, %s] ->", node_getId(g->nodes[i]), node_getName(g->nodes[i]));
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
