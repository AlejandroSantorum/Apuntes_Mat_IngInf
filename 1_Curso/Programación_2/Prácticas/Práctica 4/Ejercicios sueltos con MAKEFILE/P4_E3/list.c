#include "list.h"

typedef struct _NodeList{
    void * data;
    struct _NodeList *next;
}NodeList;

struct _List {
    NodeList *first;
    int sizeList;    /*Entero añadido a la estructura de lista para ayudar a conocer su tamaño*/
    destroy_elementlist_function_type   destroy_element_function;
    copy_elementlist_function_type      copy_element_function;
    print_elementlist_function_type     print_element_function;
    cmp_elementlist_function_type     cmp_element_function;
};

NodeList * nodeList_ini(){
    NodeList *nl=NULL;
    
    nl = (NodeList *) malloc(sizeof(NodeList));
    if(nl==NULL){
        return NULL;
    }    
    
    nl->data = NULL;
    nl->next = NULL;
    
    return nl;
}

void nodeList_destroy(NodeList *nl, List *l){
    if(nl == NULL || l==NULL){
        return;
    }    
    
    if(nl->data != NULL){
        l->destroy_element_function(nl->data);
    }
    free(nl);
}


List * list_ini(destroy_elementlist_function_type f1, copy_elementlist_function_type f2, print_elementlist_function_type f3, cmp_elementlist_function_type f4){
    List *l=NULL;
    
    if(f1==NULL || f2==NULL || f3==NULL){
        return NULL;
    }
    
    l = (List *) malloc(sizeof(List));
    if(l==NULL){
        return NULL;
    }
    
    l->destroy_element_function = f1;
    l->copy_element_function = f2;
    l->print_element_function = f3;
    l->cmp_element_function = f4;
    
    l->first = NULL;
    l->sizeList = 0;
    
    return l;
}


void list_free(List* l){
    if(l==NULL){
        return;
    }
    
    while(list_isEmpty(l) == FALSE){
        l->destroy_element_function(list_extractFirst(l));
        l->sizeList--;
    }
    
    free(l);
}


List* list_insertFirst(List *l, void *ele){
    NodeList *nl=NULL;
    
    if(l==NULL || ele==NULL){
        return NULL;
    }
    
    nl = nodeList_ini();
    if(nl==NULL)
        return NULL;
    
    nl->data = l->copy_element_function(ele);
    if(nl->data==NULL){
        nodeList_destroy(nl, l);
        return NULL;
    }
    
    nl->next = l->first;
    l->first = nl;
    l->sizeList++;
    
    return l;
}


List* list_insertLast(List *l, void *ele){
    NodeList *nl=NULL, *i=NULL;
    
    if(l==NULL || ele==NULL){
        return NULL;
    }
    
    nl = nodeList_ini();
    if(nl==NULL)
        return NULL;
    
    nl->data = l->copy_element_function(ele);
    if(nl->data==NULL){
        nodeList_destroy(nl, l);
        return NULL;
    }
    
    if(list_isEmpty(l)==TRUE){
        l->first = nl;
        l->sizeList++;
        return l;
    }
    for(i=l->first; i->next != NULL; i=i->next);
    
    i->next = nl;
    l->sizeList++;
    
    return l;
}


List* list_insertInOrder(List *l, void *ele){
    NodeList *nl=NULL, *i=NULL;
    
    if(l==NULL || ele==NULL){
        return NULL;
    }
    
    nl = nodeList_ini();
    if(nl==NULL)
        return NULL;
    
    nl->data = l->copy_element_function(ele);
    if(nl->data==NULL){
        nodeList_destroy(nl, l);
        return NULL;
    }
    
    if(list_isEmpty(l)==TRUE){ /*Si la lista está vacía lo metemos directamente*/
        l->first = nl;
        l->sizeList++;
        return l;
    }
    
    if((l->cmp_element_function(nl->data, l->first->data))<0){ /*Lo insertamos si es menor*/
        nl->next = l->first;                                   /*que el primero*/
        l->first = nl;
        l->sizeList++;
        return l;
    }
    
    i = l->first;
    while(i->next->next != NULL){
        if((l->cmp_element_function(nl->data, i->next->data))<0){
            nl->next = i->next;
            i->next = nl;
            l->sizeList++;
            return l;
        }
        i = i->next;
    }
    
    if((l->cmp_element_function(nl->data, i->next->data))<0){
        nl->next = i->next;
        i->next = nl;
        l->sizeList++;
        return l;
    }
    else{
        i->next->next = nl;
        l->sizeList++;
        return l;
    }
}


void * list_extractFirst(List *l){
    void *eleaux=NULL;
    NodeList *naux=NULL;
    
    if(l==NULL || list_isEmpty(l)==TRUE){
        return NULL;
    }
    
    naux = l->first;
    eleaux = l->copy_element_function(naux->data);
    if(eleaux==NULL){
        return NULL;
    }
    
    l->first = naux->next;
    
    nodeList_destroy(naux, l);
    
    l->sizeList--;
    
    return eleaux;
}


void * list_extractLast(List *l){
    void *eleaux=NULL;
    NodeList *naux=NULL;
    
    if(l==NULL || list_isEmpty(l)==TRUE){
        return NULL;
    }
    
    if(l->first->next == NULL){ /*Caso en que la lista tiene un solo nodo*/
        eleaux = l->copy_element_function(l->first->data);
        if(eleaux == NULL){
            return NULL;
        }
        nodeList_destroy(l->first, l);
        l->first = NULL;
        l->sizeList--;
        return eleaux;
    }
    
    /*Caso en que la lista tiene más de un nodo*/
    for(naux=l->first; (naux->next)->next!=NULL; naux=naux->next);
    
    eleaux = l->copy_element_function(naux->next->data);
    if(eleaux==NULL){
        return NULL;
    }
    
    nodeList_destroy(naux->next, l);
    naux->next=NULL;
    l->sizeList--;
    
    return eleaux;
}



Bool list_isEmpty(const List *l){
    if(l==NULL){
        return FALSE;
    }
    
    if(l->first == NULL){
        return TRUE;
    }
    
    return FALSE;
}


void* list_get(const List* l, int i){
    int j;
    NodeList *naux=NULL;
    void *eleaux=NULL;
    
    if(l==NULL){
        return NULL;
    }
    
    if(i<=0||i>l->sizeList){
        return NULL;
    }
    
    for(j=1, naux=l->first; j<i; j++,naux=naux->next);
    
    eleaux = l->copy_element_function(naux->data);
    if(eleaux==NULL){
        return NULL;
    }
    
    return eleaux;
}



int list_size(const List *l){
    if(l==NULL)
        return -1;
    
    return l->sizeList;
}


int list_print(FILE *f, const List *l){
    int num=0, contador=0;
    NodeList *nl=NULL;
    
    if(f==NULL || l==NULL){
        return -1; /*equivalente a return ERROR*/
    }
    
    for(nl = l->first; nl!=NULL; nl = nl->next){
        num += l->print_element_function(f, nl->data);
        contador++;   /*contador auxiliar que nos permite hacer una
                      *  comprobación de que se han impreso todos los nodos de la lista*/
    }
    if(contador != list_size(l)){
        return -1; /*equivalente a return ERROR*/
    }
    
    return num;
}


Bool list_isElement(List *l, void *ele){
    NodeList *nl=NULL;
    
    if(l == NULL || ele == NULL || list_isEmpty(l)==TRUE){
        return FALSE;
    }
    
    for(nl = l->first; nl->next != NULL; nl=nl->next){
        if((l->cmp_element_function(nl->data, ele))==0){
            return TRUE;
        }
    }
    if((l->cmp_element_function(nl->data, ele))==0){
        return TRUE;
    }
    
    return FALSE;
}