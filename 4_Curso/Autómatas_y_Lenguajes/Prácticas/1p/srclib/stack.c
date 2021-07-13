#include <stddef.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "stack.h"

// #pragma pack(1)
struct stack {
    size_t top;
    size_t size;
    size_t memb_sz;
    void *elems;
};

stack *stack_new(){
    return malloc(sizeof(stack));
}

void stack_delete(stack *s){
    if(s){
        free(s);
    }
}

stack *stack_init(stack *s, size_t size, size_t memb_sz){
    if(s){
        if(size){
            s->top = 0;
            s->size = size;
            s->elems = malloc(size*memb_sz);
            s->memb_sz = memb_sz;
            if(!s->elems) s->size = 0;
        }else{
            *s = (stack){0};
        }
    }
    return s;
}

void stack_destroy(stack *s){
    if(s){
        free(s->elems);
        stack_init(s, 0, 0);
    }
}

void stack_peek(stack *s, void *dest){
    if(!s || !s->elems){
        errno = EINVAL;
        perror("stack_peek");
    }else if(!s->top){
        errno = EPERM;
        perror("stack is empty");
    }else{
        uint8_t *tmp = s->elems;
        void *src = tmp+(s->top-1)*s->memb_sz;
        memcpy(dest, src, s->memb_sz);
    }
}

void stack_pop(stack *s, void *dest){
    if(!s || !s->elems){
        errno = EINVAL;
        perror("stack_peek");
    }else if(!s->top){
        errno = EPERM;
        perror("stack is empty");
    }else{
        stack_peek(s, dest);
        s->top--;
    }
}

void stack_push(stack *s, void *elem){
    if(!s || !s->elems){
        errno = EINVAL;
        perror("stack_push");
        return;
    }
    if(s->top == s->size){
        void *old = s->elems;
        s->elems = realloc(s->elems, 2*s->size*s->memb_sz);
        if(!s->elems){
            errno = EPERM;
            perror("stack is full");
            s->elems = old;
            return;
        }
        s->size *=2;
    }
    uint8_t *tmp = s->elems;
    void *dest = tmp + s->top * s->memb_sz;
    memcpy(dest, elem, s->memb_sz);
    s->top++;
}

size_t stack_top(stack *s){
    if (s) return s->top;
    return 0;
}

void stack_print(FILE *fout, stack *s, char *(*to_str)(void *, size_t)){
    uint8_t *tmp = s->elems;
    for(int i = s->top-1; i>= 0; i--){
        char *str = to_str(tmp + (i*s->memb_sz), s->memb_sz);
        fprintf(fout, "( %s ) ", str);
        free(str);
    }
    fprintf(fout, "\n");
}
