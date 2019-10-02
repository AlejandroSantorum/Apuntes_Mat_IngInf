/* 
 * File:   graph_test.c
 * Author: Profesores de PROG2
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"
#include "graph.h"

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

int format_graph(FILE * file, const Graph * g, int (*node_print_function)(FILE *, const Node *)){
    int i, j, n, c, ctemp, n2;
    Node* node;
    int* ids;
    int* conn;
	
    /* For each node: */
    n = graph_getNnodes(g);
    ids = graph_getNodeIds(g);
    for (i=0; i < n; i++){
	/* we print the node */
	node = graph_getNode(g, ids[i]);
	/* using the function pointer */
	ctemp = node_print_function(file, node);
	if (ctemp <= 0){
            return c;
	}
	c += ctemp;
	/* and print the connections to this node */
	n2=graph_getNumberOfConnectionsTo(g, ids[i]);
	conn = graph_getConnectionsTo(g, ids[i]);
        if (n2 > 0){
            c += fprintf(file, "\n\t connected to ");
            /* using the function pointer */
            ctemp = node_print_function(file, graph_getNode(g, conn[0]));
            if (ctemp <= 0){
                return c;
            }
            c += ctemp;
            for (j=1; j < n2; j++){
		c += fprintf(file, ", ");
		/* using the function pointer */
		ctemp = node_print_function(file, graph_getNode(g, conn[j]));
		if (ctemp <= 0){
                    return c;
		}
                c += ctemp;
            }
	}
	free(conn);

	/* and also the connections from this node */
	n2=graph_getNumberOfConnectionsFrom(g, ids[i]);
	conn = graph_getConnectionsFrom(g, ids[i]);
	if (n2 > 0){
            c += fprintf(file, "\n\t connected from ");
            /* using the function pointer */
            ctemp = node_print_function(file, graph_getNode(g, conn[0]));
            if (ctemp <= 0){
		return c;
            }
            c += ctemp;
            for (j=1; j < n2; j++){
		c += fprintf(file, ", ");
		/* using the function pointer */
		ctemp = node_print_function(file, graph_getNode(g, conn[j]));
		if (ctemp <= 0){
                    return c;
                }
		c += ctemp;
            }
	}
	free(conn);

	c += fprintf(file, "\n\n");
    }
    free(ids);

    return c;
}

/*
 * 
 */
int main(int argc, char** argv) {
    Graph * g = NULL;

    if (argc < 2){
	fprintf(stdout, "Not enough parameters: %d\n", argc);
	return -1;
    }
	
    g = read_graph_from_file(argv[1]);
	
    graph_print(stdout, g);
    format_graph(stdout, g, &node_print);

    graph_destroy(g);

    return EXIT_SUCCESS;
}
