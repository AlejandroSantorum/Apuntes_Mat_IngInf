/*******************************************************************************

    Authors:
        · Rafael Sanchez Sanchez - rafael.sanchezs@estudiante.uam.es
        · Alejandro Santorum Varela - alejandro.santorum@estudiante.uam.es
    File: current_state.h
    Project: First assignment AUTLEN
    Date: November 14, 2019

*******************************************************************************/

#ifndef CURRENTSTATE_H
#define CURRENTSTATE_H

#include <stdint.h>

/* Current State data structure */
typedef struct _cstate cstate;


/**
    struct _row
    Description:
        It represents a row of the DFA transition table
    Members:
        cstate *state_from
            DFA State to which this row corresponds
        cstate **state_to
            Each i-th element of this array corresponds to the arrival
            state from state_from with the i-th element of the alphabet.
*/
typedef struct _row {
    cstate *state_from;
    cstate **state_to;
} row;


/**
    cstate_size
    Input:
        None
    Returns:
        size of a cstate structure
*/
size_t cstate_size();


/**
    cstate_create
    Input:
        size_t nstates: number of NDFA states
    Returns:
        cstate struct pointer with allocated memory for itself and
        the array of integers that represents a DFA state.
        NULL on error case
*/
cstate *cstate_create(size_t nstates);


/**
    cstate_new
    Input:
        None
    Returns:
        cstate struct pointer with allocated memory for itself.
        It does not allocate memory for the inner int array
*/
cstate *cstate_new();


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
cstate *cstate_init(cstate *c, uint8_t *states);


/**
    cstate_remove
    Input:
        cstate *cst: pointer to a cstate struct
    Returns:
        Void.
        It frees allocated memory for the inner int array and the cstate struct
*/
void cstate_remove(cstate *cst);


/**
    cstate_delete
    Input:
        cstate *cst: pointer to a cstate struct
    Returns:
    Void.
    It frees allocated memory for the cstate struct
*/
void cstate_delete(cstate *cst);


/**
    cstate_destroy
    Input:
        cstate *cst: pointer to a cstate struct
    Returns:
        Void.
        It frees allocated memory for the inner int array
*/
void cstate_destroy(cstate *cst);


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
cstate *cstate_add_state(cstate *cst, int index);


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
cstate *cstate_or_cstate(cstate *dst, cstate *src);


/**
    cstate_get_states
    Input:
        cstate *cst: pointer to a cstate struct
    Returns:
        inner uint8_t array (representing a DFA state)
*/
uint8_t *cstate_get_states(cstate *cst);


/**
    cstate_to_string
    Input:
        cstate *cst: pointer to a cstate struct
        char *string: pointer to a char array (pre-allocated)
        size_t str_sz: size of the pre-allocated char array
        char **state_names: name of the original states
    Returns:
        Void.
        *string is set to the string representation of the cstate
*/
void cstate_to_string(cstate *cst, char *string, size_t str_sz, char **state_names);


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
int cstate_cmp(cstate *c1, cstate *c2);


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
int cstate_cmp_v(void *c1_v, void *c2_v);


/**
    cstate_set_initial
    Input:
        cstate *cs: pointer to a cstate struct
    Returns:
        pointer to the modified cstate
    Advanced description:
        It sets a cstate to be initial
*/
cstate *cstate_set_initial(cstate *cs);


/**
    cstate_set_final
    Input:
        cstate *cs: pointer to a cstate struct
    Returns:
        pointer to the modified cstate
    Advanced description:
        It sets a cstate to be final
*/
cstate *cstate_set_final(cstate *cs);


/**
    cstate_get_type
    Input:
        cstate *cst: pointer to a cstate struct
    Returns:
        uint8_t that represents the state type (initial, final, both or normal)
*/
uint8_t cstate_get_type(cstate *cst);


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
uint8_t cstate_is_final(cstate *cs, uint8_t *final_states);


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
uint8_t cstate_is_valid(cstate *cs);


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
cstate *cstate_copy(cstate *src);


#endif /* CURRENTSTATE_H */
