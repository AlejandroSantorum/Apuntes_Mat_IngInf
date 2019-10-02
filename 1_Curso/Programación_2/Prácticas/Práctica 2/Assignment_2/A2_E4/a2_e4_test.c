/**
*  Project: Assignment 2 - ProgII subject
*  File: a2_e4_test.c
*  Version: 2.0
*  Date: Mar 20, 2017
*  Revision date: May 27, 2018
*
*  (C) Alejandro Santorum Varela
*  alejandro.santorum@gmail.com
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "stack_fp.h"

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
*	Auxiliary function that inserts elements of the graph into a stack and then prints the stack
*/
int format(Graph *g, FILE *f){
   destroy_element_function_type f1node, f1int;
   copy_element_function_type f2node, f2int;
   print_element_function_type f3node, f3int;
	Stack *sNodes, *sInts;
   Node *auxNode;
   int i, j;
   int *ids;

   f1node = destroy_node_function;
   f1int = destroy_intp_function;
   f2node = copy_node_function;
   f2int = copy_intp_function;
 	f3node = print_node_function;
   f3int = print_intp_function;

   if(!g || !f){
      return -1;
   }

   sNodes = stack_ini(f1node, f2node, f3node);
   if(!sNodes){
      return -1;
   }

   sInts = stack_ini(f1int, f2int, f3int);
   if(!sNodes){
      stack_destroy(sNodes);
      return -1;
   }

   ids = graph_getNodeIds(g);
   if(!ids){
      stack_destroy(sNodes);
      stack_destroy(sInts);
      return -1;
   }

   for(i=(graph_getNnodes(g)-1); i>=0; i--){
      for(j=(graph_getNnodes(g)-1); j>=0; j--){
      	if(graph_areConnected(g, ids[i], ids[j])==TRUE){
            auxNode = graph_getNode(g, ids[i]);
            if(!auxNode){
               free(ids);
               stack_destroy(sNodes);
               stack_destroy(sInts);
               return -1;
            }
            stack_push(sNodes, auxNode);
            if(!sNodes){
               free(ids);
               node_destroy(auxNode);
               stack_destroy(sInts);
               return -1;
            }
				stack_push(sInts, &ids[i]);
            if(!sInts){
               free(ids);
               node_destroy(auxNode);
               stack_destroy(sNodes);
               return -1;
            }
				node_destroy(auxNode);
            auxNode = graph_getNode(g, ids[j]);
            if(!auxNode){
               free(ids);
               node_destroy(auxNode);
               stack_destroy(sInts);
               return -1;
            }
            stack_push(sNodes, auxNode);
            if(!sNodes){
               free(ids);
               node_destroy(auxNode);
               stack_destroy(sInts);
               return -1;
            }
         	stack_push(sInts, &ids[j]);
            if(!sInts){
               free(ids);
               node_destroy(auxNode);
               stack_destroy(sNodes);
               return -1;
            }
         	node_destroy(auxNode);
         }
      }
   }
   fprintf(stdout, "\n\t=== INTEGERS STACK ===\n");
   stack_print(f, sInts);
   fprintf(stdout, "\n\t=== NODES STACK ===\n");
   stack_print(f, sNodes);

   free(ids);
   stack_destroy(sNodes);
   stack_destroy(sInts);
	return 0;
}

int main(int argc, char** argv) {
   Graph * g = NULL;

   g = read_graph_from_file("graph_test.txt");
   if(!g){
      return EXIT_FAILURE;
   }

	if(format(g, stdout)==-1) return EXIT_FAILURE;
	graph_destroy(g);
	return EXIT_SUCCESS;
}
