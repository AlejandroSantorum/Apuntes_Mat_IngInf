#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void destroy_node_function(void* e);

void * copy_node_function(const void* e);

int  print_node_function(FILE * f, const void* e);

int cmp_node_function(const void *v1, const void *v2);


#endif /* FUNCTIONS_H */

