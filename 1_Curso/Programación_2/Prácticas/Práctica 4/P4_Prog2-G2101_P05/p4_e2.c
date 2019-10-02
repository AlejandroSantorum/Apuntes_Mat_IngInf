#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string.h>

#include "tree2.h"
#include "functions2.h"
#include "node2.h"
#include "types.h"

#define MAX_LINE 350
#define MAX 300

Node* read_node_from_file(FILE* f_in){
    Node* node = NULL;
    int id=-1;
    char name[MAX], buff[MAX_LINE];

    if (fgets(buff, MAX_LINE, f_in) != NULL){
	if (sscanf(buff, "%d %s", &id, name) == 2){
            /* create node */
            node = node_ini();
            if (node_setId(node, id) == NULL){
                node_destroy(node);
                return NULL;
            }
            if (node_setName(node, name) == NULL){
                node_destroy(node);
                return NULL;
            }
	}
    }
	
    return node;
}

int compare(const void* a, const void* b) {
    Node **e1, **e2;
    e1 = (Node **) a;
    e2 = (Node **) b;
    return node_cmp(*e1, *e2);
}

int getNumberLines(FILE* pf) {
    char line[MAX_LINE];
    int n = 0;
    while (fgets(line, MAX_LINE, pf) != NULL) {
        n++;
    }
    return n;
}

void loadDataFromFile(FILE* pf, Node*** ndata) {
    Node** naux = *ndata;
    Node* n;

    while(!feof(pf)){
	n = read_node_from_file(pf);
	if (n != NULL){
            *naux = node_copy(n);
            naux++;
            node_destroy(n);
	}
    }
}

void balance(Node** data, Tree *t, int first, int last) {
    int middle = (first + last) / 2;
    Node* n;

    if (first <= last) {
        n = *(&(data[0]) + middle);
	if (tree_insert(t, n) == ERROR){
            fprintf(stdout, "Node ");			
            node_print(stdout, n);
            fprintf(stdout, " not inserted!\n");			
	}

        balance(data, t, first, middle - 1);
        balance(data, t, middle + 1, last);
    }
}

Tree* loadBalancedTreeFromData(Node** data, int n) {
    Tree *t;
	
    t = tree_ini(destroy_node_function, copy_node_function, print_node_function, cmp_node_function);
	
    balance(data, t, 0, n - 1);
    
    return t;
}

Tree* loadTreeFromData(Node** data, int n) {
    Tree *t;
    Node* node;
    int i;
	
    t = tree_ini(destroy_node_function, copy_node_function, print_node_function, cmp_node_function);

    for (i=0; i<n; i++){
	node = data[i];
	if (tree_insert(t, node) == ERROR){
            fprintf(stdout, "Node ");			
            node_print(stdout, node);
            fprintf(stdout, " not inserted!\n");			
	}
    }

    return t;
}

int main(int argc, char const *argv[]){
    FILE *f_in = NULL, *f_out = NULL;
    Tree* pa = NULL;
    Node **data=NULL, *node=NULL;
    int i,n;
    time_t time;
    double time_in_secs;


    if(argc < 2){
	printf("Falta el fichero con nodos (un nodo por línea).\n");
	return -1;
    }

    f_in = fopen(argv[1], "r");

    if (!f_in){
	return 1;
    }

    f_out = stdout;

    n = getNumberLines(f_in);
    fclose(f_in);
    fprintf(f_out, "%d líneas leídas\n", n);
    data = (Node**) malloc(n * sizeof (Node*));
    f_in = fopen(argv[1], "r");
    loadDataFromFile(f_in, &data);
    fclose(f_in);

    if (strcmp("./p4_e2", argv[0]) == 0) {
	time = clock();
	pa = loadTreeFromData(data, n);
	time = clock() - time;
	time_in_secs = ((float) time) / CLOCKS_PER_SEC;
    } 
    else if (strcmp("./p4_e2_bal", argv[0]) == 0) {
	qsort(data, n, sizeof(Node*), &compare);
	fprintf(f_out, "Datos ordenados\n");
	time = clock();
	pa = loadBalancedTreeFromData(data, n);
	time = clock() - time;
	time_in_secs = ((float) time) / CLOCKS_PER_SEC;
    }

    for (i=0; i<n; i++){
    	node_destroy(data[i]);
    }
    free(data);
	
    fprintf(f_out, "\nTiempo de creación del árbol: %ld ticks (%f segundos)\n", (long) time, time_in_secs);
    fprintf(f_out, "Numero de nodos: %d\nProfundidad: %d\n", tree_numNodes(pa), tree_depth(pa));

    while(node == NULL){
	fprintf(stdout, "Introduce un nodo para buscar en el árbol (siguiendo el mismo formato que en el fichero de entrada):\n");
	node = read_node_from_file(stdin);
    }
    time = clock();
    if (tree_find(pa, node) == TRUE){
	fprintf(stdout, "Elemento encontrado!\n");
    }
    else{
	fprintf(stdout, "Elemento NO encontrado!\n");
    }
    time = clock() - time;
    time_in_secs = ((float) time) / CLOCKS_PER_SEC;
    node_destroy(node);
    fprintf(f_out, "\nTiempo de búsqueda en el árbol: %ld ticks (%f segundos)\n", (long) time, time_in_secs);

    tree_destroy(pa);

    return 0;
}