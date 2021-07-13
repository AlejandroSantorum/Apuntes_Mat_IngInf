/*******************************************************************************

    Authors:
        · Rafael Sanchez Sanchez - rafael.sanchezs@estudiante.uam.es
        · Alejandro Santorum Varela - alejandro.santorum@estudiante.uam.es
    File: minimiza.h
    Project: First assignment AUTLEN
    Date: November 14, 2019

*******************************************************************************/

#ifndef MINIMIZA_H
#define MINIMIZA_H

#include <stdbool.h>
#include "linked_list.h"
#include "current_state.h"

typedef struct _distinct {
    uint8_t val;
    llist *lst;
} distinct;

/**
    AFNDMinimiza
    Input:
        AFND *afnd: pointer to a dfa object
    Returns:
        dfa object, or NULL in error case
    Advanced description:

*/
AFND *AFNDMinimiza(AFND *afnd);

// uint8_t *** _delete_unacc_states(uint8_t ***trans_tb, size_t nstates, uint8_t initial, size_t alph_sz);

#endif
