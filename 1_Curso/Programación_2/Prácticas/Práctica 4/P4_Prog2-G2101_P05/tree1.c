#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree1.h"


typedef struct _NodeBT {
    void* info;
    struct _NodeBT *left;
    struct _NodeBT *right;
} NodeBT;

struct _Tree {
    NodeBT *root;
    destroy_elementtree_function_type   destroy_element_function;
    copy_elementtree_function_type      copy_element_function;
    print_elementtree_function_type     print_element_function;
    cmp_elementtree_function_type     cmp_element_function;
};


NodeBT* nodeBT_ini(){
    NodeBT *n=NULL;
    
    n = (NodeBT *) malloc(sizeof(NodeBT));
    if(n == NULL){
        return NULL;
    }
    
    n->info = NULL;
    n->left = NULL;
    n->right = NULL;
    
    return n;
}

void nodeBT_destroy(NodeBT *n, Tree *t){
    if(n == NULL || t == NULL){
        return;
    }
    
    if(n->info != NULL){
        t->destroy_element_function(n->info);
    }
    
    free(n);
}


Tree* tree_ini(destroy_elementtree_function_type f1, copy_elementtree_function_type f2, print_elementtree_function_type f3, cmp_elementtree_function_type f4){
    Tree *t=NULL;
    
    t = (Tree *) malloc(sizeof(Tree));
    if(t == NULL){
        return NULL;
    }
    
    t->destroy_element_function = f1;
    t->copy_element_function = f2;
    t->print_element_function = f3;
    t->cmp_element_function = f4;
    
    t->root = NULL;
    
    return t;
}


void tree_destroy_rec(NodeBT *n, Tree *t){
    if(n == NULL){
        return;
    }
    
    tree_destroy_rec(n->left, t);
    tree_destroy_rec(n->right, t);
    nodeBT_destroy(n, t);
    return;
}
void tree_destroy (Tree *t){
    if(t == NULL){
        return ;
    }
    
    if(t->root == NULL){
        free(t);
        return;
    }
    
    tree_destroy_rec(t->root, t);
    
    free(t);
}


Status tree_insert_rec(NodeBT **n, void *ele, Tree *t){
    int cmp;
    
    if(n == NULL){
        return ERROR;
    }
    
    if((*n) == NULL){
        *n = nodeBT_ini();
        if((*n)==NULL){
            return ERROR;
        }
        (*n)->info = t->copy_element_function(ele);
        if((*n)->info == NULL){
            nodeBT_destroy(*n, t);
            *n = NULL;
            return ERROR;
        }
        return OK;
    }
    
    cmp = t->cmp_element_function(ele, (*n)->info);
    
    if(cmp < 0){
        return tree_insert_rec(&((*n)->left), ele, t);
    }
    
    if(cmp > 0){
        return tree_insert_rec(&((*n)->right), ele, t);
    }
    
    if(cmp == 0){
        fprintf(stdout, "The element ");
        t->print_element_function(stdout, ele);
        fprintf(stdout, "is already in the tree.\n");
        return OK;
    }
    return OK;
}
Status tree_insert(Tree *t, void *ele){
    if(t == NULL || ele == NULL){
        return ERROR;
    }
    
    return tree_insert_rec(&(t->root), ele, t);
}



Bool tree_find_rec(NodeBT *n, void *ele, Tree *t){
    int cmp;
    
    if(n == NULL){
        return FALSE;
    }
    
    cmp = t->cmp_element_function(ele, n->info);
    
    if(cmp < 0){
        return tree_find_rec(n->left, ele, t);
    }
    
    if(cmp > 0){
        return tree_find_rec(n->right, ele, t);
    }
    
    return TRUE;
}
Bool tree_find(Tree *t, void *ele){
    if(t == NULL || ele == NULL){
        return ERROR;
    }
    
    return tree_find_rec(t->root, ele, t);
}



Bool tree_isEmpty(const Tree *t){
    if(t == NULL){
        fprintf(stdout, "The tree doesn't exist.\n");
        return FALSE;
    }
    
    if(t->root == NULL){
        return TRUE;
    }
    
    return FALSE;
}


int tree_depth_rec(NodeBT *n){
    int i, j;
    
    if(n == NULL){
        return 0;
    }
    
    i = tree_depth_rec(n->left);
    j = tree_depth_rec(n->right);
    
    if(i>=j){
        return i+1;
    }
    else{
        return j+1;
    }
}
int tree_depth(const Tree *t){
    if(t == NULL){
        fprintf(stdout, "The tree doesn't exist.\n");
        return -2;
    }
    
    if(t->root == NULL){
        return -1;
    }
    
    return tree_depth_rec(t->root)-1;
}


int tree_numNodes_rec(NodeBT *n){
    int i, j;
    
    if(n == NULL){
        return 0;
    }
    
    i = tree_numNodes_rec(n->left);
    j = tree_numNodes_rec(n->right);
    
    return i+j+1;
}
int tree_numNodes(const Tree *t){
    if(t == NULL){
        fprintf(stdout, "The tree doesn't exist.\n");
        return -1;
    }
    
    if(t->root == NULL){
        return 0;
    }
    
    return tree_numNodes_rec(t->root);
}
