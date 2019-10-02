#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdlib.h>
#include <stdio.h>

void destroy_intp_function(void* e);

void * copy_intp_function(const void* e);

int print_intp_function(FILE * f, const void* e);

int cmp_intp_function(void *v1,void *v2);

#endif /* FUNCTIONS_H */