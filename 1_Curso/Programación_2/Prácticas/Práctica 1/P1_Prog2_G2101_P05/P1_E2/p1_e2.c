#include <stdio.h>
#include "graph.h"

int ComprobacionErrores(){
    Graph *g;
    Node *n1, *n2;
    FILE *f;
    
    n1 = node_ini();
    n2 = node_ini();
    
    n1 = node_setName(n1, "first");
    n1 = node_setId(n1, 111);   
    n2 = node_setName(n2, "second");
    n2 = node_setId(n2, 222);
    
    g = graph_ini();
    
    f = fopen("grafos.txt", "a");
    
    graph_print(f, g);
    
    fprintf(f, "Insertando nodo 1...\r\n");
    
    g = graph_addNode(g, n1);
    graph_print(f, g);
    
    fprintf(f, "Insertando nodo 2...\r\n");
    
    g=graph_addNode(g, n2);
    graph_print(f, g);
    
    fprintf(f, "Conectado nodo 1 y nodo 2? ");
    if(graph_areConnected(g, 111, 222)==TRUE){
        fprintf(f, "Sí\r\n");
    }
    else{
        fprintf(f, "No\r\n");
    }
    
    fprintf(f, "Conectado nodo 2 y nodo 1? ");
    if(graph_areConnected(g, 222, 111)==TRUE){
        fprintf(f, "Sí\r\n");
    }
    else{
        fprintf(f, "No\r\n");
    }
    
    fprintf(f, "Insertando nodo 2->nodo 1\r\n");
    g = graph_addEdge(g, 222, 111);
    graph_print(f, g);
    
    fprintf(f, "Conectado nodo 1 y nodo 2? ");
    if(graph_areConnected(g, 111, 222)==TRUE){
        fprintf(f, "Sí\r\n");
    }
    else{
        fprintf(f, "No\r\n");
    }
    
    fprintf(f, "Conectado nodo 2 y nodo 1? ");
    if(graph_areConnected(g, 222, 111)==TRUE){
        fprintf(f, "Sí\r\n");
    }
    else{
        fprintf(f, "No\r\n");
    }
    
    fprintf(f, "Insertando nodo 1->nodo 2\r\n");
    g = graph_addEdge(g, 111, 222);
    graph_print(f, g);
    
    fprintf(f, "Conectado nodo 1 y nodo 2? ");
    if(graph_areConnected(g, 111, 222)==TRUE){
        fprintf(f, "Sí\r\n");
    }
    else{
        fprintf(f, "No\r\n");
    }
    
    fprintf(f, "Conectado nodo 2 y nodo 1? ");
    if(graph_areConnected(g, 222, 111)==TRUE){
        fprintf(f, "Sí\r\n");
    }
    else{
        fprintf(f, "No\r\n");
    }
    
    fprintf(f, "Insertando nodo 2->nodo 1\r\n");
    g = graph_addEdge(g, 222, 111);
    graph_print(f, g);
    
    fprintf(f, "Conectado nodo 1 y nodo 2? ");
    if(graph_areConnected(g, 111, 222)==TRUE){
        fprintf(f, "Sí\r\n");
    }
    else{
        fprintf(f, "No\r\n");
    }
    
    fprintf(f, "Conectado nodo 2 y nodo 1? ");
    if(graph_areConnected(g, 222, 111)==TRUE){
        fprintf(f, "Sí\r\n");
    }
    else{
        fprintf(f, "No\r\n");
    }
    
    fclose(f);
    
    graph_destroy(g);
    
    return 0;       
}

