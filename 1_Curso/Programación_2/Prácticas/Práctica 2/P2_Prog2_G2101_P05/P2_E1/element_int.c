/**
*  Project: Assignment 1 - ProgII subject
*  File: a1_e1_test.c
*  Version: 2.0
*  Date: Feb 20, 2017
*  Revision date: May 26, 2018
*
*  (C) Alejandro Santorum Varela
*  alejandro.santorum@gmail.com
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "element_int.h"

struct _Element{
    int *info;
};

Element * element_ini(){
    Element *ele=NULL;

    ele = (Element *) malloc(sizeof(Element));
    if(ele == NULL){
        return NULL;
    }
    ele->info = (int *) malloc(sizeof(int));
    if(ele->info == NULL){
        return NULL;
    }
    return ele;
}


void element_destroy(Element * ele){
    if(ele==NULL)
        return;
    free(ele->info);
    free(ele);

}


Element * element_setInfo(Element *ele, void *contenido){
    if(ele==NULL || contenido==NULL){
        return NULL;
    }
    *(ele->info) = *((int *)contenido);

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

    ele_copy = element_ini();
    if(ele_copy == NULL){
        return NULL;
    }
    *(ele_copy->info) = *(ele->info);

    return ele_copy;
}


Bool element_equals(const Element *ele1, const Element *ele2){
    if(ele1 == NULL || ele2 == NULL){
        return FALSE;
    }

    if(*(ele1->info) == *(ele2->info)){
        return TRUE;
    }

    return FALSE;
}


int element_print(FILE *f, const Element *ele){
    int num;

    if(f == NULL || ele == NULL){
        return -1;
    }
    num = fprintf(f, "%d", *(ele->info));

    return num;
}
