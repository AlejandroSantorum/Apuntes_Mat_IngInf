#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "table.h"

#define NCOLS 4

int main () {
    table_t *tb = NULL;
    type_t t[NCOLS] = {INT, STR, LLNG, DBL};
    long pos;
    int i, r=0;
    void **buff=NULL;

    buff = (void **) malloc(NCOLS * sizeof(void *));
    if(buff==NULL) return EXIT_FAILURE;

    table_create("test.txt", NCOLS, t); /* Creating the table */

    tb = table_open("test.txt");

    for (i=0; i<10; i++){ /* Inserting 10 rows in the table in the test */
        buff[0] = (int *) malloc(sizeof(int));
        if(buff[0]==NULL) return EXIT_FAILURE;
        buff[1] = (char *) malloc(100 * sizeof(char)); /* We don't need to use a macro for a simple test */
        if(buff[1]==NULL) return EXIT_FAILURE;
        buff[2] = (long long *) malloc(sizeof(long long));
        if(buff[2]==NULL) return EXIT_FAILURE;
        buff[3] = (double *) malloc(sizeof(double));
        if(buff[3]==NULL) return EXIT_FAILURE;

        *((int *) buff[0]) = 10 + i;
        strcpy((char *) buff[1], "full many a gem of purest ray serene");
        *((long long *) buff[2]) = 1000000000000000 + i;
        *((double *) buff[3]) = 123456789.5 +  i;

        table_insert_record(tb, buff); /* Inserting one tuple */

        free(buff[0]);
        free(buff[1]);
        free(buff[2]);
        free(buff[3]);

    }
    table_close(tb); /*Closing*/

    tb = table_open("test.txt"); /*Opening it again*/

    pos = table_first_pos(tb);

    while(1){
        pos = table_read_record(tb, pos);
        if(pos == -1){
            break;
        }
        r++;

        for(i=0; i < table_ncols(tb); i++) { /* Reading everything */
            buff[i] = table_column_get(tb, i);
        }

        printf("[Table Row: %d]\tCol 1: %d\tCol2: %s\tCol3: %lld\tCol4: %.2lf\n", r, *((int *)buff[0]), (char *)buff[1], *((long long *)buff[2]), *((double *)buff[3]));
    }

    table_close(tb);

    free(buff);

    return 0;
}
