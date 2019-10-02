/**
*  Project: Assignment 3 - ProgII subject
*  File: a3_e2_test.c
*  Version: 2.0
*  Date: Apr 15, 2017
*  Revision date: May 30, 2018
*
*  (C) Alejandro Santorum Varela
*  alejandro.santorum@gmail.com
*
*/
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "graph.h"
#include "functions.h"
#include "element_int.h"

#define MAX 255

#define FOUND 1
#define NOT_FOUND 0
#define _ERROR_ -1
#define FATHER 1
#define CHILD 0

int **path_matrix=NULL; /* Global variable to know the followed path between the two nodes (if the path exists) */

/**
*  Auxiliary function that loads a graph from a given file
*/
Graph* read_graph_from_file(char *filename){
   FILE *in=NULL;
   Graph *g=NULL;
   Node *n=NULL;
   char buff[MAX], name[MAX];
   int i, nnodes, id1, id2;

   if(!(g = graph_ini())){
      printf("Error: RGFF 1\n");
      return NULL;
   }

   in = (FILE*) fopen(filename, "r");
   if(!in){
      printf("Error: RGFF 2\n");
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
         printf("Error: RGFF 3\n");
         fclose (in);
         node_destroy(n);
         graph_destroy(g);
         return NULL;
      }
      if (node_setName(n, name) == NULL){
         printf("Error: RGFF 4\n");
         fclose (in);
         node_destroy(n);
         graph_destroy(g);
         return NULL;
      }
      /* add node to graph */
	   if (graph_addNode(g, n) == NULL){
         printf("Error: RGFF 5\n");
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
      if(graph_addEdge(g, id1, id2) == NULL){
         printf("Error: RGFF 5\n");
		   fclose (in);
		   graph_destroy(g);
		   return NULL;
      }
	}
   fclose (in);
   return g;
}
/**
*  It allocates the memory for the path matrix.
*  The total number of nodes of the graph is given as a parameter
*/
Status allocate_matrix(int n_nodes){
   int i, j;

   path_matrix = (int**) malloc(n_nodes*sizeof(int*));
   if(!path_matrix){
      printf("Error allocating path matrix\n");
      return ERROR;
   }

   for(i=0; i<n_nodes; i++){
      path_matrix[i] = (int*) malloc(2*sizeof(int));
      if(!path_matrix[i]){
         printf("Error allocating path matrix (2)\n");
         for(j=0; j<i; j++){
            free(path_matrix[j]);
         }
         free(path_matrix);
      }
   }
   return OK;
}

/**
*  It frees all the memory reserved for the path matrix
*/
void free_matrix(int n_nodes){
   int i;

   for(i=0; i<n_nodes; i++){
      free(path_matrix[i]);
   }
   free(path_matrix);
}

/**
*  It inserts into the matrix the integer pair (child, father).
*  It allows us to know from what node we visited another one
*/
void setPath(int father, int child, int count){
   path_matrix[count][CHILD] = child;
   path_matrix[count][FATHER] = father;
}

/**
*  It checks if one node is already visited
*/
int visited(int num, int count){
   int i;

   for(i=0; i<count; i++){
      if(path_matrix[i][CHILD]==num) return 1;
   }
   return 0;
}

/**
*  Given the id of the origen node, the id of the destiny node, the number of visited nodes and the graph,
*  this function prints in stdout all the nodes from the source until the destiny (the followed path)
*/
void print_path(int src, int dest, int count, Graph *g){
   int i, actual, flag=0;
   Node *nod=NULL;

   actual = dest;
   printf("\t=== PATH ===\n");
   printf("DESTINY ===> ");
   while(1){
      for(i=0; i<count; i++){
         if(path_matrix[i][CHILD] == actual){
            printf("Hi\n");
            nod = graph_getNode(g, actual);
            node_print(stdout, nod);
            printf("\n");
            node_destroy(nod);
            if(path_matrix[i][FATHER] != src) actual = path_matrix[i][FATHER];
            else{
               flag=1;
               break;
            }
         }
      }
      if(flag) break;
   }
   printf("ORIGIN ===> ");
   nod = graph_getNode(g, src);
   node_print(stdout, nod);
   printf("\n===========================\n");
   node_destroy(nod);
}

/**
*  It marks a node (its ID) in order to indicate it has been already explored
*/
int labeled(int id, int *labels, int n_labeled){
   int i;

   for(i=0; i<=n_labeled; i++){
      if(labels[i]==id) return 1;
   }
   return 0;
}

/**
*  This function is a implementation of the breadth first search (BFS) algorithm.
*  This algorithm is quite used in order to determine if there is a path between
*  two nodes of a graph
*/
int _breadth_first_search(Graph *g, int src, int dest){
   destroy_elementqueue_function_type f1;
   copy_elementqueue_function_type f2;
   print_elementqueue_function_type f3;
   Queue *q=NULL;
   int *labels=NULL, *connected=NULL;
   int n_nodes, n_labeled=0, count=0, actual, i;
   void *auxiliar=NULL;

   f1 = destroy_intp_function;
   f2 = copy_intp_function;
   f3 = print_intp_function;

   n_nodes = graph_getNnodes(g);
   if(allocate_matrix(n_nodes)==ERROR) return _ERROR_;

   q = queue_ini(f1,f2,f3);
   if(!q) return _ERROR_;

   labels = (int*) malloc(n_nodes*sizeof(int));
   if(!labels){
      printf("DFS 1\n");
      queue_destroy(q);
      free_matrix(n_nodes);
      return _ERROR_;
   }
   for(i=0; i<n_nodes; i++){
      labels[i] = 0;
   }
   labels[0] = src;

   connected = graph_getConnectionsFrom(g, src);
   if(!connected){
      printf("DFS 2\n");
      queue_destroy(q);
      free_matrix(n_nodes);
      free(labels);
      return _ERROR_;
   }
   for(i=0; i<graph_getNumberOfConnectionsFrom(g, src); i++){
      if(!queue_insert(q, &connected[i])){
         printf("DFS 3\n");
         free(labels);
         free(connected);
         free_matrix(n_nodes);
         return _ERROR_;
      }
      if(!visited(connected[i], count)){
         setPath(src, connected[i], count);
         count++;
      }
   }
   free(connected);

   while(queue_isEmpty(q)==FALSE){
      auxiliar = queue_extract(q);
      if(!auxiliar){
         printf("DFS 4\n");
         free(labels);
         queue_destroy(q);
         free_matrix(n_nodes);
         return _ERROR_;
      }
      actual = *((int*)auxiliar);
      if(actual==dest){
         free(labels);
         queue_destroy(q);
         print_path(src, dest, count, g);
         free_matrix(n_nodes);
         destroy_intp_function(auxiliar);
         return FOUND;
      } else{
         if(!labeled(actual, labels, n_labeled)){
            n_labeled++;
            labels[n_labeled] = actual;
            connected = graph_getConnectionsFrom(g, actual);
            if(!connected){
               printf("DFS 5\n");
               queue_destroy(q);
               free_matrix(n_nodes);
               free(labels);
               return _ERROR_;
            }
            for(i=0; i<graph_getNumberOfConnectionsFrom(g, actual); i++){
               if(!(queue_insert(q, &connected[i]))){
                  printf("DFS 6\n");
                  free(labels);
                  free(connected);
                  free_matrix(n_nodes);
                  return _ERROR_;
               }
               if(!visited(connected[i], count)){
                  setPath(actual, connected[i], count);
                  count++;
               }
            }
            free(connected);
         }
      }
      destroy_intp_function(auxiliar);
   }
   queue_destroy(q);
   free_matrix(n_nodes);
   free(labels);
   return NOT_FOUND;
}

/**
*
*/
int main(int argc, char** argv){
   Graph *g=NULL;
   int id_source, id_target, retval;
   Node *n1=NULL, *n2=NULL;

   if (argc < 3){
	   fprintf(stdout, "Insufficient number of parameters: %d\n", argc);
	   fprintf(stdout, "Introduce the ID of the origin node and the ID of the destiny node\n");
	   return EXIT_FAILURE;
   }

   g = read_graph_from_file("graph_test.txt");
   if(!g){
      return EXIT_FAILURE;
   }

   id_source = atoi(argv[1]);
   id_target = atoi(argv[2]);
   n1 = graph_getNode(g, id_source);
   if(!n1){
      node_destroy(n1);
      graph_destroy(g);
      return EXIT_SUCCESS;
   }
   n2 = graph_getNode(g, id_target);
   if(!n2){
      node_destroy(n2);
      graph_destroy(g);
      return EXIT_SUCCESS;
   }
   node_destroy(n1);
   node_destroy(n2);
   if(id_source == id_target){
      printf("The introduced ID's are equal. Is obvious that there is a path\n");
      return EXIT_SUCCESS;
   }

   retval = _breadth_first_search(g, id_source, id_target);
   if(retval==FOUND){
      printf("YES, there is a path between node with ID %d and node with ID %d\n", id_source, id_target);
   } else if(retval==NOT_FOUND){
      printf("NO, there is not a path between node with ID %d and node with ID %d\n",id_source, id_target);
   } else{
      printf("Error searching\n");
      graph_destroy(g);
      return EXIT_FAILURE;
   }
   graph_destroy(g);
   return EXIT_SUCCESS;
}
