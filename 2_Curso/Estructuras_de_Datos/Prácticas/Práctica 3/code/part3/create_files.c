#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "type.h"
#include "table.h"
#include "index.h"

#define NCOLS 4

int main () {
    type_t t[NCOLS] = {STR, STR, INT, INT};

    table_create("table.txt", NCOLS, t);
    printf("Table file created correctly.\n");

    index_create(INT, "index.txt");
    printf("Index file created correctly.\n");

    return EXIT_SUCCESS;
}
