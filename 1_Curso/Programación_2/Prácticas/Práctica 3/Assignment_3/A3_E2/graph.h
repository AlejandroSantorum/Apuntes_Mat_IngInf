/**
*  Project: Assignment 1, 2 and 3 - ProgII subject
*  File: graph.h
*  Version: 2.0
*  Date: Feb 20, 2017
*  Revision date: May 26, 2018
*
*  (C) Alejandro Santorum Varela
*  alejandro.santorum@gmail.com
*
*/
#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"

#define MAX_NODES 4096 /** Maximum number of nodes that a graph can contain */

typedef struct _Graph Graph;

/**
*  Initializes a graph, allocating memory and returning the initialized graph on success, MULL otherwise
*/
Graph * graph_ini();

/**
*  It frees the memory allocated for a given graph
*/
void graph_destroy(Graph *g);

/**
*  Returns the number of nodes of a given graph
*/
int graph_getNnodes(Graph *g);

/**
*  Returns a array of ID's of all the nodes contained in the given graph allocating memory for it.
*  If any error occurs, NULL is returned
*/
int* graph_getNodeIds(Graph *g);

/**
*  Returns the number of connections that are contained in the given graph, -1 if any error occurs
*/
int graph_getNedges(Graph *g);

/**
*  A new node is introduced into the graph. A node is given as a parameter, and a COPY of that
*  is added to the graph. It returns the modified graph, or NULL if any error appears
*/
Graph * graph_addNode(Graph *g, Node* n);

/**
*  A new connection is introduced into the graph, from node with ID=nId1 to node with ID=nId2.
*  It returns the modified graph, NULL otherwise
*/
Graph * graph_addEdge(Graph *g, int nId1, int nId2);

/**
*  Returns a pointer to A COPY (new allocated memory) of the node with ID=nId.
*  If it is not found, NULL is returned
*/
Node * graph_getNode(Graph *g, int nId);

/**
*  Checks if two nodes are connected (from nId1 node to nId2 node),
*  returning TRUE in affirmative case, or FALSE otherwise
*/
Bool graph_areConnected(Graph *g, int nId1, int nId2);

/**
*  Returns the number of connections FROM a given node (its ID is used as a parameter).
*  If there're none, -1 is returned
*/
int graph_getNumberOfConnectionsFrom(Graph *g, int fromId);

/**
*  Returns a list with the node ID'S connected FROM a given node (its ID is used as a parameter).
*  NULL is returned in error case
*/
int* graph_getConnectionsFrom(Graph *g, int fromId);

/**
*  Returns the number of connections TO a given node (its ID is used as a parameter).
*  If there're none, -1 is returned
*/
int graph_getNumberOfConnectionsTo(Graph *g, int toId);

/**
*  Returns a list with the node ID's connected TO a given node (its ID is used as a parameter).
*  NULL is returned in error case
*/
int* graph_getConnectionsTo(Graph *g, int toId);

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
int graph_print(FILE *pf, Graph *g);

#endif /* GRAPH_H */
