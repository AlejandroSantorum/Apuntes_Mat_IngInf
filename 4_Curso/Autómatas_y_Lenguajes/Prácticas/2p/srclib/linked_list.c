#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "linked_list.h"

struct lnode *__lnode_new(void *val);

void __lnode_free();

llist *llist_new(){
    llist *l = calloc(1, sizeof(llist));
    return l;
}

void llist_delete(llist *l){
    if(l) free(l);
}

void llist_destroy(llist *l){
    struct lnode *aux;
    struct lnode *first;
    if(l){
        first = l->first;
            while(first){
                aux = first->next;
                __lnode_free(first);
                first = aux;
            }
        l->first = NULL;
    }
}

void *llist_head(llist *l){
    if(l)
        return l->first->val;
    return NULL;
}

int llist_add(llist *l, void *elem){
    if(l){
        struct lnode *new = __lnode_new(elem);
        new->next=l->first;
        l->first = new;
        return 1;
    }
    return 0;
}

void *llist_del(llist *l, void *elem, int (*cmp_func) (void *, void *)){
    void *aux;
    if(l){
        struct lnode *temp = l->first, *prev;
        if(temp && !cmp_func(elem, temp->val)){
            l->first = temp->next;
            aux = temp->val;
            __lnode_free(temp);
            return aux;
        }
        while( temp && cmp_func(elem, temp->val)){
            prev = temp;
            temp = temp->next;
        }
        if(!temp) return NULL;
        prev->next = temp->next;
        aux = temp->val;
        __lnode_free(temp);
        return aux;
    }
    return NULL;
}

bool llist_in(llist *l, void *elem, int (*cmp_func) (void *, void *)){
    if(l){
        struct lnode *temp = l->first;
        if(temp && !cmp_func(elem, temp->val)){
            return true;
        }
        while( temp && cmp_func(elem, temp->val)){
            temp = temp->next;
        }
        if (!temp) return false;
        return true;
    }
    return false;
}

void *llist_pop(llist *l){
    if(l && l->first){
        void *aux = l->first->val;
        struct lnode *to_pop = l->first;
        l->first = l->first->next;
        __lnode_free(to_pop);
        return aux;
    }
    return NULL;
}

int llist_print(FILE *f, llist *l, char * (*to_string) (void *)){
    size_t sum = 0;
    char *string;
    if(l){
        if(l->first){

        struct lnode *curr=l->first;
        while (curr->next) {
            string = to_string(curr->val);
            sum+=fprintf(f, "[%s]->", string);
            if(string) free(string);
            curr=curr->next;
        }
        string = to_string(curr->val);
        sum+=fprintf(f, "[%s]\n", string);
        free(string);
        }else{
            sum+=printf("[]\n");

        }
        return sum;
    }
    return 0;
}

struct lnode *__lnode_new(void *val){
    struct lnode *new = calloc(1, sizeof(struct lnode));
    new->val = val;
    return new;
}

void __lnode_free(struct lnode *ln){
    free(ln);
}
