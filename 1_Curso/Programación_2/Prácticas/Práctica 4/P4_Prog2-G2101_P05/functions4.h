#ifndef FUNCTIONS4_H
#define FUNCTIONS4_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void destroy_str_function(void* e);

void * copy_str_function(const void* e);

int print_str_function(FILE * f, const void* e);

int cmp_str_function(const void *v1,const void *v2);

#endif /* FUNCTIONS_H */