/*******************************************************************************

    Authors:
        · Rafael Sanchez Sanchez - rafael.sanchezs@estudiante.uam.es
        · Alejandro Santorum Varela - alejandro.santorum@estudiante.uam.es
    File: current_state.c
    Project: First assignment AUTLEN
    Date: November 14, 2019

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "current_state.h"
#include "afnd.h"


/* State abbreviation by default */
/* We suppose states are names as qi, where i is a positive integer */
#define STATE_NAME 'q'

#pragma pack(1)
/* Current State data structure */
struct _cstate{
    /* Number of NDFA states */
    size_t nstates;
    /* Boolean that indicates if the current state is final or not */
    uint8_t is_final;
    /* Boolean that indicates if the current state is initial or not */
    uint8_t is_initial;
    /* Array of 0's and 1's that representes a DFA state, i.e., the state
        q0q1q3 would be represented as 110100 (assuming only 6 NDFA states) */
    uint8_t *states;
};


/**
    cstate_size
    Input:
        None
    Returns:
        size of a cstate structure
*/
size_t cstate_size(){
    return sizeof(struct _cstate);
}


/**
    cstate_create
    Input:
        size_t nstates: number of NDFA states
    Returns:
        cstate struct pointer with allocated memory for itself and
        the array of integers that represents a DFA state.
        NULL on error case
*/
cstate *cstate_create(size_t nstates){
    cstate *cst=NULL;

    cst = (cstate*) calloc(1, sizeof(cstate));
    if (!cst) { /* Memory error */
        perror("Unable to allocate memory for cstate\n");
        return NULL;
    }

    cst->states = (uint8_t*) calloc(nstates, sizeof(uint8_t));
    if (!(cst->states)) {
        perror("Unable to allocate memory for cstate states\n");
        return NULL;
    }

    cst->nstates = nstates;
    return cst;
}


/**
    cstate_new
    Input:
        None
    Returns:
        cstate struct pointer with allocated memory for itself.
        It does not allocate memory for the inner int array
*/
cstate *cstate_new() {
    return calloc(1, sizeof(cstate));
}


/**
    cstate_init
    Input:
        cstate *c: pointer to a cstate struct
        uint8_t *states: integer array to copy into inner int array,
            which represents a DFA state
    Returns:
        cstate struct pointer with the filled inner int array.
        NULL on error case
*/
cstate *cstate_init(cstate *c, uint8_t *states) {
    if (!c || !states){
        return NULL;
    }
    memcpy(c->states, states, c->nstates * sizeof(uint8_t));
    return c;
}


/**
    cstate_remove
    Input:
        cstate *cst: pointer to a cstate struct
    Returns:
        Void.
        It frees allocated memory for the inner int array and the cstate struct
*/
void cstate_remove(cstate *cst){
    if (cst) {
        if (cst->states){
            free(cst->states);
        }
        free(cst);
    }
}


/**
    cstate_delete
    Input:
        cstate *cst: pointer to a cstate struct
    Returns:
    Void.
    It frees allocated memory for the cstate struct
*/
void cstate_delete(cstate *cst){
    if (cst) free(cst);
}


/**
    cstate_destroy
    Input:
        cstate *cst: pointer to a cstate struct
    Returns:
        Void.
        It frees allocated memory for the inner int array
*/
void cstate_destroy(cstate *cst){
    if (cst) free (cst->states);
}


/**
    cstate_add_state
    Input:
        cstate *cst: pointer to a cstate struct
        int index: integer that represents a NDFA state
    Returns:
        cstate struct pointer with the added NDFA state.
        NULL on error case
    Advanced description:
        It sets to 1 the inner int array position indicated by index.
        Several calls of this function is useful to configure a DFA state
        (formed by several NDFA states).
*/
cstate *cstate_add_state(cstate *cst, int index){
    if (!cst) {
        perror("cstate NULL pointer\n");
        return NULL;
    }
    if (index < 0 || index >= cst->nstates) {
        perror("Invalid index value\n");
        return NULL;
    }
    if (!(cst->states)) {
        perror("cstate states NULL pointer\n");
        return NULL;
    }

    /* Setting transition */
    cst->states[index] = 1;
    return cst;
}


/**
    cstate_get_states
    Input:
        cstate *cst: pointer to a cstate struct
    Returns:
        inner uint8_t array (representing a DFA state)
*/
uint8_t *cstate_get_states(cstate *cst){
    if (cst) return cst->states;
    return NULL;
}


/**
    cstate_or_cstate
    Input:
        cstate *dst: pointer to a cstate struct
        cstate *src: pointer to a cstate struct
    Returns:
        cstate struct pointer to the modified dst cstate
    Advanced description:
        It performs an OR operation between inner int arrays of the given cstates.
        It is useful to get the union of two DFA states
*/
cstate *cstate_or_cstate(cstate *dst, cstate *src){
    if (!dst || !src){
        perror("cstate_or_cstate: NULL pointer\n");
        return NULL;
    }
    if (!dst->states || !src->states){
        perror("cstate_or_cstate: No states");
        return NULL;
    }
    for (size_t i = 0; i < dst->nstates; dst->states[i] |= src->states[i], i++);
    return dst;
}


/**
    cstate_to_string
    Input:
        cstate *cst: pointer to a cstate struct
        char *string: pointer to a char array (pre-allocated)
        size_t str_sz: size of the pre-allocated char array
    Returns:
        Void.
        *string is set to the string representation of the cstate
*/
void cstate_to_string(cstate *cst, char *string, size_t str_sz){
    size_t i;
    char *cst_str;

    if (!cst) {
        perror("cstate NULL pointer\n");
        return;
    }
    if (!string) {
        perror("string NULL pointer\n");
        return;
    }

    memset(string, 0, str_sz * sizeof(char));
    cst_str = string;
    for (i = 0; i < cst->nstates; i++) {
        if (cst->states[i]) {
            *cst_str = STATE_NAME;
            cst_str++;
            cst_str += sprintf(cst_str, "%lu", i);
        }
    }
}


/**
    cstate_cmp
    Input:
        cstate *c1: pointer to a cstate struct
        cstate *c2: pointer to a cstate struct
    Returns:
        memcmp int result of the comparison of the given scatates
    Advanced description:
        It compares two cstates, returning 0 if equal, otherwise returns
        the difference between the first two differing bytes
*/
int cstate_cmp(cstate *c1, cstate *c2){
    return memcmp(c1->states, c2->states, sizeof(uint8_t) * c1->nstates);
}


/**
    cstate_cmp_v
    Input:
        void *c1: pointer to void (cstate struct in the future)
        void *c2: pointer to void (cstate struct in the future)
    Returns:
        memcmp int result of the comparison of the given scatates
    Advanced description:
        It compares two cstates but passed as void pointers (a more versatile function),
        returning 0 if equal, otherwise returns the difference between the first two
        differing bytes
*/
int cstate_cmp_v(void *c1_v, void *c2_v){
    cstate *c1 = (cstate *) c1_v;
    cstate *c2 = (cstate *) c2_v;
    return memcmp(c1->states, c2->states, sizeof(uint8_t) * c1->nstates);
}


/**
    cstate_get_type
    Input:
        cstate *cst: pointer to a cstate struct
    Returns:
        uint8_t that represents the state type (initial, final, both or normal)
*/
uint8_t cstate_get_type(cstate *cst){
    if (!cst) return NORMAL;
    if (cst->is_final && cst->is_initial) return INICIAL_Y_FINAL;
    if (cst->is_final) return FINAL;
    if (cst->is_initial) return INICIAL;
    return NORMAL;
}


/**
    cstate_set_initial
    Input:
        cstate *cs: pointer to a cstate struct
    Returns:
        pointer to the modified cstate
    Advanced description:
        It sets a cstate to be initial
*/
cstate *cstate_set_initial(cstate *cs){
    if (cs) {
        cs->is_initial = 1;
        return cs;
    }
    return NULL;
}


/**
    cstate_set_final
    Input:
        cstate *cs: pointer to a cstate struct
    Returns:
        pointer to the modified cstate
    Advanced description:
        It sets a cstate to be final
*/
cstate *cstate_set_final(cstate *cs){
    if (cs) {
        cs->is_final = 1;
        return cs;
    }
    return NULL;
}


/**
    cstate_is_final
    Input:
        cstate *cs: pointer to a cstate struct
        uint8_t *final_states: array of 0's and 1's.
    Returns:
        1 if the given cstate is final, 0 otherwise
    Advanced description:
        It returns 1 if the given cstate is considered to be final.
        This function recieves the list (array) of NDFA final states
        and checks if one of them is in the inner array of the cstate.
*/
uint8_t cstate_is_final(cstate *cs, uint8_t *final_states){
    if (!cs || !final_states){
        return 0;
    }

    for (size_t i = 0; i < cs->nstates; i++) {
        if (cs->states[i] && final_states[i]){
            return 1;
        }
    }

    return 0;
}


/**
    cstate_is_valid
    Input:
        cstate *cs: pointer to a cstate struct
    Returns:
        1 if the given cstate is final, 0 otherwise
    Advanced description:
        It checks a given cstate truly represents a DFA state (at least one 1
        on its inner int array).
*/
uint8_t cstate_is_valid(cstate *cs){
    if(!cs) return 0;
    for (size_t i = 0; i < cs->nstates; i++) {
        if (cs->states[i]) return 1;
    }
    return 0;
}


/**
    cstate_copy
    Input:
        cstate *src: pointer to a cstate struct
    Returns:
        cstate struct pointer
    Advanced description:
        It copies all the given cstate into a completely new cstate (allocating
        memory for it), and returning the copy.
*/
cstate *cstate_copy(cstate *src){
    if (!src) return NULL;
    cstate *dst;
    dst = cstate_create(src->nstates);
    memcpy(dst->states, src->states, sizeof(uint8_t) * src->nstates);
    dst->nstates = src->nstates;
    dst->is_final = src->is_final;
    dst->is_initial = src->is_initial;
    return dst;
}
