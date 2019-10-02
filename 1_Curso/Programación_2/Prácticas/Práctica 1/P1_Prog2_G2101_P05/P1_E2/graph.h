#ifndef GRAPH_H
#define GRAPH_H
#include "node.h"
#define MAX_NODES 4096


typedef struct _Graph Graph;

/* Inicializa un grafo, reservando memoria y devolviendo el grafo inicializado si lo ha hecho correctamente, o NULL
si no */
Graph * graph_ini();


/* Libera la memoria dinámica reservada para un grafo */
void graph_destroy(Graph * g);


/* Devuelve el número de nodos de un grafo, o -1 si se produce algún error */
int graph_getNnodes(const Graph * g);


/* Devuelve la lista de ids de nodos contenidos en el grafo usando nueva memoria para el puntero que se devuelve
(quien llame a esta función se tiene que encargar de liberar dicho puntero al terminar). Si hay algún error se
devuelve NULL */
int* graph_getNodeIds(const Graph * g);


/* Devuelve el número de conexiones que se almacenan en un grafo, o -1 si se produce algún error */
int graph_getNedges(const Graph * g);


/* Se añade un nodo al grafo reservando memoria nueva para dicho nodo, actualizando los atributos internos del
grafo que sean necesarios. Se devuelve el grafo actualizado si todo ha ido bien, o NULL en otro caso */
Graph * graph_addNode(Graph * g, const Node* n);


/* Se añade una conexión (entre el nodo con id nId1 y el nodo con id nId2) al grafo, actualizando los atributos
internos del grafo que sean necesarios. Se devuelve el grafo actualizado si todo ha ido bien, o NULL en otro caso
*/
Graph * graph_addEdge(Graph * g, const int nId1, const int nId2);


/*
Función privada recomendada: permite encontrar el índice (del array) en el que se almacena un nodo en el grafo
con un id dado. Devuelve ese índice si lo encuentra o -1 si no o si ha habido algún otro error
int find_node_index(Graph * g, int nId1);
*/
int find_node_index(const Graph * g, int nId1);


/* Devuelve un puntero a la estructura Node almacenada en el grafo tal que dicho nodo tiene como id nId. Si no se
encuentra o hay algún error, se devuelve NULL */
Node * graph_getNode(const Graph * g, int nId); 


/* Devuelve TRUE o FALSE según si los nodos correspondientes a los ids pasados como argumento están
conectados en el grafo o no (existe una conexión entre nId1 y nId2, en ese sentido). Si hay algún error se devuelve
FALSE */
Bool graph_areConnected(const Graph * g, const int nId1, const int nId2);


/* Devuelve el número de conexiones que se conocen en el grafo desde un nodo, si hay algún error devuelve -1 */
int graph_getNumberOfConnectionsFrom(const Graph * g, const int fromId);


/* Devuelve una lista con los ids de los nodos conectados desde un nodo dado, si hay algún error devuelve NULL*/
int* graph_getConnectionsFrom(const Graph * g, const int fromId);


/* Devuelve el número de conexiones que se conocen en el grafo hacia un nodo, si hay algún error devuelve -1 */
int graph_getNumberOfConnectionsTo(const Graph * g, const int toId);


/* Devuelve una lista con los ids de los nodos conectados desde un nodo dado, si hay algún error devuelve NULL*/
int* graph_getConnectionsTo(const Graph * g, const int toId);


/* Imprime en pf los datos de un grafo, devuelve el número de caracteres que se han escrito con éxito (mirar
documentación de fprintf). El formato a seguir es: imprimir una primera línea con el número de nodos y conexiones,
después, se imprime una línea por nodo, incluyendo la información del nodo y las conexiones con el resto de
nodos como 1 o 0.
La salida para el grafo pintado en el ejercicio 2.3 de la parte 1 es:
N=3, E=3:
[1, a]->0 1 1
[2, b]->0 0 1
[3, c]->0 0 0
*/
int graph_print(FILE *pf, const Graph * g);


#endif /* GRAPH_H */