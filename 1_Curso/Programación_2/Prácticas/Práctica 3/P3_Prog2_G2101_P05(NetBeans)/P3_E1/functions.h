#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "node.h"


void destroy_node_function(void* e);

void * copy_node_function(const void* e);

int  print_node_function(FILE * f, const void* e);

#endif /* FUNCTIONS_H */
