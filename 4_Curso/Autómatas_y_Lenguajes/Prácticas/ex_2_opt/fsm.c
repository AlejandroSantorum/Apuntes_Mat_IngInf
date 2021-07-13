/**
*   Authors:
*       · Alejandro Santorum Varela - aleandro.santorum@estudiante.uam.es
*       · Rafael Sanchez Sanchez - rafael.sanchezs@estudiante.uam.es
*   File: fsm.c
*   Project: AUTLEN assignments - second optional exercise
*   Date: October 10, 2019
**/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 255

int main(int argc, char *argv[]) {
    char *string = argv[2];
    int *states;
    bool found = false;
    char ***table;
    int *finals, table_sz, finals_sz, alph_sz, n_edges;
    char buffer[SIZE];

    /* LOAD MATRIX */
    FILE *fp = fopen(argv[1], "r");
    fgets(buffer, SIZE, fp);
    table_sz = atoi(buffer);
    fgets(buffer, SIZE, fp);
    alph_sz = atoi(buffer);
    fgets(buffer, SIZE, fp);
    n_edges = atoi(buffer);

    /* Allocating memory for a 3-dim matrix */
    table = calloc(table_sz, sizeof(char **));
    for (size_t i = 0; i < table_sz; i++) {
        table[i] = calloc(table_sz, sizeof(char *));
        for (size_t j = 0; j < table_sz; j++) {
            table[i][j] = calloc(alph_sz, sizeof(char));
        }
    }

    /* Reading edges */
    for (size_t i = 0; i < n_edges; i++) {
        int in, out;
        char symb;
        fgets(buffer, SIZE, fp);
        sscanf(buffer, "%d %d %c", &out, &in, &symb);
        table[out][in][symb-'a'] = symb;
    }

    /* Reading final states */
    fgets(buffer, SIZE, fp);
    finals_sz = atoi(buffer);

    finals = calloc(finals_sz, sizeof(int));

    /* Allocating memory for final states */
    for (size_t i = 0; i < finals_sz; i++) {
        fscanf(fp, "%d\n", finals + i);
    }

    /* Printing matrix for debugging */
    for (size_t i = 0; i < table_sz; i++) {
        for (size_t j = 0; j < table_sz; j++) {
            printf("(%lu -> %lu): { ", i, j);
            for (size_t k = 0; k < alph_sz; k++) {
                printf("%c ", table[i][j][k]);
            }
            printf("}\n");
        }
    }

    printf("[ ");
    for (size_t i = 0; i < finals_sz; i++) {
        printf("%d ", finals[i]);
    }
    printf("]\n");

    /* Allocating memory for all possible current states */
    states = calloc(table_sz, sizeof(int));
    int *aux_states = calloc(table_sz, sizeof(int));
    int *lambda_states = calloc(table_sz, sizeof(int));
    states[0] = 1; // Initial state is always q0
    memcpy(lambda_states, states, table_sz * sizeof(int));

    /* Algorithm */
    while (*string) {
        printf("Voy a leer el caracter %c\n", *string);


        /* Actualizamos los estados */
        do {
            memcpy(states, lambda_states, table_sz * sizeof(int));

            for (size_t i = 0; i < table_sz; i++) {
                if (lambda_states[i] == 1){
                    for (size_t j = 0; j < table_sz; j++) {
                        if(table[i][j][alph_sz-1]){
                            lambda_states[j] = 1;
                        }
                    }
                }
            }
        }
        while ( memcmp(states, lambda_states, table_sz * sizeof(int)) );

        for (size_t i = 0; i < table_sz; i++) {
            if (!states[i]) continue;

            for (size_t j = 0; j < table_sz; j++) {
                /* *string in table[i][j] */
                for (size_t k = 0; k < alph_sz-1; k++) {
                    if (table[i][j][k] == *string){
                        aux_states[j] = 1;
                    }
                }
            }
        }

        // printf("[ ");
        // for (size_t i = 0; i < table_sz; i++) {
        //     printf("%d ", states[i]);
        // }
        // printf("]\n");
        // printf("[ ");
        // for (size_t i = 0; i < table_sz; i++) {
        //     printf("%d ", aux_states[i]);
        // }
        // printf("]\n");
        //
        // printf("----------------\n");

        memcpy(states, aux_states, table_sz * sizeof(int));
        memcpy(lambda_states, states, table_sz * sizeof(int));
        memset(aux_states, 0, table_sz * sizeof(int));

        // printf("[ ");
        // for (size_t i = 0; i < table_sz; i++) {
        //     printf("%d ", states[i]);
        // }
        // printf("]\n");
        // printf("[ ");
        // for (size_t i = 0; i < table_sz; i++) {
        //     printf("%d ", aux_states[i]);
        // }
        // printf("]\n");

        int next = 0;
        for (size_t i = 0; i < table_sz; i++) {
            if (states[i]){
                next = 1;
                break;
            }
        }

        if (!next) {
            printf("Palabra no reconocida por el autómata. (No existe transición).\n");
            return 0;
        }

        string++;
    }
    printf("He terminado la palabra.\n");

    for (size_t i = 0; i < table_sz; i++) {
        for (size_t j = 0; j < finals_sz; j++) {
            if ((states[i] == 1) && (finals[j] == i)){
                printf("Palabra reconocida por el autómata\n");
                return 0;
            }
        }
    }

    printf("Palabra no reconocida por el autómata. (Estado no final).\n");
    return 0;
}
