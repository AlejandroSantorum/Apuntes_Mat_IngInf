/**
*  Project: Assignment 2 - ProgII subject
*  File: a2_e2_test.c
*  Version: 2.0
*  Date: Mar 19, 2017
*  Revision date: May 27, 2018
*
*  (C) Alejandro Santorum Varela
*  alejandro.santorum@gmail.com
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"
#include "graph.h"
#include "stack_element.h"
#include "element_node.h"

#define MAX 255

/**
*	Auxiliary function to read a graph from a file
*/
Graph* read_graph_from_file(char * filename){
	FILE *in=NULL;
	Graph *g=NULL;
	Node *n=NULL;
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

/**
*	Auxiliary function that inserts all nodes of the graph into a stack and then prints the stack
*/
int format(Graph *g, FILE *f){
   Stack *p=NULL;
   Node *auxNode=NULL;
   int i, j;
   Element *ele=NULL;
   int *ids=NULL;

   if(g==NULL || f==NULL){
      return -1;
   }

   p = stack_ini();
   if(p==NULL){
      return -1;
   }

   ids = graph_getNodeIds(g);
   if(ids == NULL){
      stack_destroy(p);
      return -1;
   }

   /* Visiting the whole adjacency matrix */
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
				/* Introducing the origin node of the connection into the stack */
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
				/* Introducing the destiny node of the connection into the stack */
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
   stack_print(f, p);

   free(ids);
   stack_destroy(p);

   return 0;
}

/*
 * Testing
 */
int main(int argc, char** argv) {
	Graph *g = NULL;

	if(!(g = read_graph_from_file("graph_test.txt"))) return EXIT_FAILURE;

	graph_print(stdout, g);
	if(format(g, stdout) == -1) return EXIT_FAILURE;

	graph_destroy(g);

   return EXIT_SUCCESS;
}
