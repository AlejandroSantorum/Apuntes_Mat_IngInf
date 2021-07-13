#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>
#include "../srclib/stack.h"

#define DECIMALS 3
/*Compile: gcc test_stack.c stack/stack.c -o test_stack */

char *int_str(void *x, size_t size){
    size_t digits = ceil(log10(* (int *) x));
    char *s = calloc(digits+1, sizeof(char));
    snprintf(s, digits+1, "%d", *(int *)x);
    return s;
}

char *double_str(void *x, size_t size){
    size_t digits = ceil(log10(* (double *) x))+DECIMALS+2;
    char *s = calloc(digits, sizeof(char));
    snprintf(s, digits, "%lf", *(double *)x);
    return s;
}

int main(){
    stack *s_int;
    stack *s_double;
    s_int = stack_init(stack_new(), 10, sizeof(int));
    s_double = stack_init(stack_new(), 10, sizeof(double));
    int a = 5;
    stack_push(s_int, &a);
    stack_push(s_int, &a);
    stack_print(stdout, s_int, int_str);
    stack_destroy(s_int);
    stack_destroy(s_double);
    stack_delete(s_int);
    stack_delete(s_double);
    return 0;
}
