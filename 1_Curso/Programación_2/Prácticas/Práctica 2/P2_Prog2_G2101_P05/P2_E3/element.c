#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "element.h"
#include "node.h"

struct _Element{
    Node *info;
};

Element * element_ini(){
    Element *ele=NULL;
    
    ele = (Element *) malloc(sizeof(Element));
    if(ele == NULL){
        return NULL;
    }
    /*ele->info = node_ini();
    if(ele->info == NULL){
        return NULL;
    }*/
    return ele;
}


void element_destroy(Element * ele){
    if(ele==NULL)
        return;
    node_destroy(ele->info);
    free(ele);
    
}


Element * element_setInfo(Element *ele, void *contenido){
    if(ele==NULL || contenido==NULL){
        return NULL;
    }
    
    /*node_destroy(ele->info);*/
    ele->info = node_copy((Node *)contenido);
    if(!ele->info){
        return NULL;
    }
    
    return ele;
}


void * element_getInfo(Element *ele){
    if(ele == NULL){
        return NULL;
    }
    
    return ((void*)ele->info);
}


Element * element_copy(const Element *ele){
    Element *ele_copy;
    
    if(ele == NULL){
        return NULL;
    }
    ele_copy=element_ini();
    if(!ele_copy){
        return NULL;
    }
    
    /*node_destroy(ele_copy->info);*/
    ele_copy->info = node_copy(ele->info);
    if(!ele_copy->info){
        return NULL;
    }
    
    return ele_copy;
}


Bool element_equals(const Element *ele1, const Element *ele2){
    if(ele1 == NULL || ele2 == NULL){
        return FALSE;
    }
    
    if(node_equals(ele1->info,ele2->info)==TRUE){
        return TRUE;
    }
    
    return FALSE;
}


int element_print(FILE *f, const Element *ele){
    int num;
    
    if(f == NULL || ele == NULL){
        return -1;
    }
    num = node_print(f, ele->info);
    
    return num;
}
