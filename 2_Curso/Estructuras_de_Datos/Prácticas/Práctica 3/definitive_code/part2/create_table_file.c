#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"
#include "table.h"

#define NCOLS 4

int main () {
    type_t t[NCOLS] = {STR, STR, INT, INT}; /* Assigning types of ISBN, title, score, book_id */

    table_create("scores.txt", NCOLS, t); /* Creating the table */
    printf("Table file created correctly.\n");

    return EXIT_SUCCESS;
}
