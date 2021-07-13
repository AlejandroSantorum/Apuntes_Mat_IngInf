#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include "../srclib/current_state.h"

#define NSTATES 5
#define BUFSZ 2*NSTATES+1

int main(int argc, char const *argv[]) {
    cstate *c1, *c2;
    char *buffer;

    c1 = cstate_create(NSTATES);
    c2 = cstate_create(NSTATES);

    cstate_add_state(c1, 0);
    cstate_add_state(c1, 1);
    cstate_add_state(c2, 3);
    cstate_add_state(c2, 4);

    buffer = calloc(BUFSZ, sizeof(char *));

    cstate_to_string(c1, buffer, BUFSZ);
    printf("C1: %s\n", buffer);
    cstate_to_string(c2, buffer, BUFSZ);
    printf("C2: %s\n", buffer);
    printf("··· Adding states ···\n");
    cstate_or_cstate(c1, c2);
    cstate_to_string(c1, buffer, BUFSZ);
    printf("C1: %s\n", buffer);
    cstate_to_string(c2, buffer, BUFSZ);
    printf("C2: %s\n", buffer);

    free(buffer);
    cstate_remove(c1);
    cstate_remove(c2);
    return 0;
}
