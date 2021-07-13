/*******************************************************************************

    Authors:
        · Rafael Sanchez Sanchez - rafael.sanchezs@estudiante.uam.es
        · Alejandro Santorum Varela - alejandro.santorum@estudiante.uam.es
    File: minimiza.c
    Project: First assignment AUTLEN
    Date: November 14, 2019

*******************************************************************************/

#include <stdbool.h>
#include "utils.h"
#include "linked_list.h"
#include "stack.h"
#include "afnd.h"
#include "current_state.h"
#include "minimiza.h"

row * __get_min_dfa(uint8_t ***trans_tb, distinct **d_mtx, uint8_t *i_states, uint8_t *f_states, size_t nstates, size_t alph_sz, size_t *min_states);
row * __explore_states(distinct **d_mtx, uint8_t *i_states, uint8_t *f_states, size_t nstates, size_t *min_states);
void __set_transitions(row *min_dfa, uint8_t ***trans_tb, size_t nstates, size_t min_states, size_t alph_sz);
size_t __find_min_state(row *min_dfa, size_t min_states, size_t delta);

uint8_t *** __delete_unacc_states(uint8_t ***trans_tb, size_t nstates, uint8_t initial, size_t alph_sz, size_t *n_acc, uint8_t **acc);
void __update_acc(uint8_t ***trans_tb, size_t nstates, uint8_t state, size_t alph_sz, uint8_t *acc, stack *stack_acc);
void __update_metadata(uint8_t *acc, size_t nstates, size_t n_acc, uint8_t **i_states, uint8_t **f_states, char ***state_names);

distinct ** __calc_distinct_mtx(uint8_t ***trans_tb, uint8_t *fstates, size_t nstates, size_t alph_sz);
uint8_t __exists_marked_transition(uint8_t ***trans_tb, distinct ** d_mtx,size_t nstates, size_t alph_sz, size_t i, size_t j);
void __mark_recursively(distinct **d_mtx, llist *lst);
/**
    AFNDMinimiza
    Input:
        AFND *afnd: pointer to a dfa object
    Returns:
        dfa object, or NULL in error case
    Advanced description:

*/
AFND *AFNDMinimiza(AFND *afnd){
    if (!afnd){
        return NULL;
    }
    size_t nstates, alph_sz;
    tuple *t;

    // Fill our structures from the AFND object information
    //// Get the DFA transition table
    uint8_t ***trans_tb = get_nfa_transition_table(afnd);
    //// Get the initial state
    uint8_t *i_states = get_initial_states(afnd, &nstates);
    uint8_t init = 0;
    for (size_t j = 0; i_states[j] == 0; init = ++j);
    //// Get the set of final states
    uint8_t *f_states = get_final_states(afnd, &nstates);
    //// Get the names of the states
    char **state_names = get_states_names(afnd, &nstates);
    //// Get alphabet of the NDFA
    char **alphabet = get_alphabet(afnd, &alph_sz);

    // Delete unaccesibles states.
    size_t n_acc;
    uint8_t *acc;
    trans_tb = __delete_unacc_states(trans_tb, nstates, init, alph_sz, &n_acc, &acc);
    //// Update initials, finals and names (arrays can be shifted)
    __update_metadata(acc, nstates, n_acc, &i_states, &f_states, &state_names);
    distinct **d_mtx = __calc_distinct_mtx(trans_tb, f_states, n_acc, alph_sz);

    // Build the transition table of the minimum DFA
    size_t dfa_states;
    row *min_dfa = __get_min_dfa(trans_tb, d_mtx, i_states, f_states, n_acc, alph_sz, &dfa_states);

    // Translate our table to the AFND object this function has to return
    AFND *dfa = get_dfa_object(min_dfa, alphabet, alph_sz, dfa_states, nstates, state_names);

    // Free's resources
    for (size_t i = 0; i < n_acc; i++) {
        for (size_t j = 0; j < n_acc; j++) {
            while( (t = llist_pop(d_mtx[i][j].lst)) ){
                free(t);
            }
            llist_destroy(d_mtx[i][j].lst);
            llist_delete(d_mtx[i][j].lst);
        }
        free(d_mtx[i]);
    }
    free(d_mtx);

    for (size_t i = 0; i < dfa_states; i++) {
        for (size_t j = 0; j < alph_sz; j++) {
            cstate_remove(min_dfa[i].state_to[j]);
        }
        free(min_dfa[i].state_to);
        cstate_remove(min_dfa[i].state_from);
    }

    free(acc);
    free(min_dfa);
    free(f_states);
    free(i_states);
    free(state_names);
    free(alphabet);
    delete_nfa_transition_table(trans_tb, n_acc, alph_sz);
    return dfa;
}


row * __get_min_dfa(uint8_t ***trans_tb, distinct **d_mtx, uint8_t *i_states, uint8_t *f_states, size_t nstates, size_t alph_sz, size_t *min_states) {
    *min_states = 0;
    row *min_dfa = __explore_states(d_mtx, i_states, f_states, nstates, min_states);

    __set_transitions(min_dfa, trans_tb, nstates, *min_states, alph_sz);
    return min_dfa;
}

row * __explore_states(distinct **d_mtx, uint8_t *i_states, uint8_t *f_states, size_t nstates, size_t *min_states){ //TODO: ADD FINALS AND INITIALS
    row *min_dfa = calloc(nstates, sizeof(row));
    uint8_t *explored = calloc(nstates, sizeof(uint8_t));
    uint8_t *aux = calloc(nstates, sizeof(uint8_t));
    uint8_t is_init, is_final;
    is_init = is_final = 0;
    for (size_t i = 0; i < nstates; i++) {
        if (!explored[i]){
            min_dfa[*min_states].state_from = cstate_create(nstates);
            for (size_t j = 0; j < nstates; j++) {
                aux[j] = !d_mtx[i][j].val;
                explored[j] |= aux[j];
                if (aux[j]){
                    if (i_states[j]) is_init = 1;
                    if (f_states[j]) is_final = 1;
                }
            }
            cstate_init(min_dfa[*min_states].state_from, aux);
            if (is_init) cstate_set_initial(min_dfa[*min_states].state_from);
            if (is_final) cstate_set_final(min_dfa[*min_states].state_from);
            is_init = is_final = 0;
            (*min_states)++;
        }
    }
    free(aux);
    free(explored);
    return min_dfa;
}

void __set_transitions(row *min_dfa, uint8_t ***trans_tb, size_t nstates, size_t min_states, size_t alph_sz){

    for (size_t i = 0; i < min_states; i++) {
        uint8_t *state = cstate_get_states(min_dfa[i].state_from);
        min_dfa[i].state_to = calloc(alph_sz, sizeof(cstate *));

        size_t from = 0;
        for (size_t j = 0; state[j] == 0; from = ++j);

        for (size_t sym = 0; sym < alph_sz; sym++) {
            size_t delta = dfa_delta(trans_tb, nstates, from, sym);
            size_t idx = __find_min_state(min_dfa, min_states, delta);
            min_dfa[i].state_to[sym] = cstate_copy(min_dfa[idx].state_from);
        }
    }
}

size_t __find_min_state(row *min_dfa, size_t min_states, size_t delta){
    for (size_t i = 0; i < min_states; i++) {
        uint8_t *states = cstate_get_states(min_dfa[i].state_from);
        if (states[delta]){
            return i;
        }
    }
    return -1;
}

uint8_t *** __delete_unacc_states(uint8_t ***trans_tb, size_t nstates, uint8_t initial, size_t alph_sz, size_t *n_acc_states, uint8_t **access){
    // List of accesible states
    uint8_t *acc = calloc(nstates, sizeof(uint8_t));
    // Stack of states to check its accesibility
    stack *stack_acc = stack_init(stack_new(), nstates, sizeof(uint8_t));

    // Inserting initial state into accesible list and stack
    acc[initial] = 1;
    stack_push(stack_acc, &initial);

    // Discover all accessibles states
    uint8_t state;
    while (stack_top(stack_acc)){

        stack_pop(stack_acc, &state);
        __update_acc(trans_tb, nstates, state, alph_sz, acc, stack_acc);
    }

    // Create new adjacency matrix
    size_t n_acc = 0;
    for (size_t i = 0; i < nstates; n_acc += acc[i++]);
    uint8_t ***new_trans_tb = calloc(n_acc, sizeof(uint8_t **));
    for (size_t i = 0; i < n_acc; i++) {
        new_trans_tb[i] = calloc(alph_sz, sizeof(uint8_t *));
        for (size_t j = 0; j < alph_sz; j++) {
            new_trans_tb[i][j] = calloc(n_acc, sizeof(uint8_t));
        }
    }
    //// Copy trans_tb to new adjacency matrix
    // size_t new_i, new_k;
    for (size_t i = 0, new_i = 0; i < nstates; i++) {
        if (acc[i]){
            for (size_t j = 0; j < alph_sz; j++) {
                for (size_t k = 0, new_k = 0; k < nstates; k++) {
                    if (acc[k]){
                        new_trans_tb[new_i][j][new_k] = trans_tb[i][j][k];
                        new_k++;
                    }
                }
            }
            new_i++;
        }
    }

    delete_nfa_transition_table(trans_tb, nstates, alph_sz);

    *access = acc;
    stack_destroy(stack_acc);
    stack_delete(stack_acc);
    *n_acc_states = n_acc;
    return new_trans_tb;
}

void __update_acc(uint8_t ***trans_tb, size_t nstates, uint8_t state, size_t alph_sz, uint8_t *acc, stack *stack_acc){
    for (size_t sym = 0; sym < alph_sz; sym++) {
        for (uint8_t j = 0; j < nstates; j++) {
            if(trans_tb[state][sym][j]){
                if (!acc[j]){
                    stack_push(stack_acc, &j);
                    acc[j] = 1;
                }
                break;
            }
        }
    }
}

void __update_metadata(uint8_t *acc, size_t nstates, size_t nacc, uint8_t **i_states, uint8_t **f_states, char ***state_names){
    uint8_t *finals = calloc(nacc, sizeof(uint8_t));
    uint8_t *initials = calloc(nacc, sizeof(uint8_t));
    char **names = calloc(nacc, sizeof(char *));
    size_t new_i = 0;
    for (size_t i = 0; i < nstates; i++) {
        if (acc[i]){
            initials[new_i] = (*i_states)[i];
            finals[new_i] = (*f_states)[i];
            names[new_i] = (*state_names)[i];
            new_i++;
        }
    }
    free(*f_states);
    free(*i_states);
    free(*state_names);
    *f_states = finals;
    *i_states = initials;
    *state_names = names;
}

distinct ** __calc_distinct_mtx(uint8_t ***trans_tb, uint8_t *fstates, size_t nstates, size_t alph_sz){
    // TODO: error handling
    distinct ** d_mtx = calloc(nstates, sizeof(distinct *));
    for (size_t i = 0; i < nstates; i++) {
        d_mtx[i] = calloc(nstates, sizeof(distinct));
    }

    // Mark distinct states between finals and not finals
    for (size_t i = 0; i < nstates; i++) {
        if (fstates[i]){
            for (size_t j = 0; j < nstates; j++) {
                if (!fstates[j]){
                    d_mtx[i][j].val = 1;
                }
            }
        } else {
            for (size_t j = 0; j < nstates; j++) {
                if (fstates[j]){
                    d_mtx[i][j].val = 1;
                }
            }
        }
    }

    size_t di, dj;
    for (size_t i = 0; i < nstates; i++) {
        for (size_t j = 0; j < nstates; j++) {
            if (__exists_marked_transition(trans_tb, d_mtx ,nstates, alph_sz, i, j)) {
                d_mtx[i][j].val = 1;
                __mark_recursively(d_mtx, d_mtx[i][j].lst);
            } else {
                for (size_t sym = 0; sym < alph_sz; sym++) {
                    di = dfa_delta(trans_tb, nstates, i, sym);
                    dj = dfa_delta(trans_tb, nstates, j, sym);
                    if (di == dj){
                        continue;
                    }
                    if (!d_mtx[di][dj].lst) {
                        d_mtx[di][dj].lst = llist_new();
                    }

                    tuple *t = calloc(1, sizeof(tuple));
                    t->a = i; t->b = j;
                    llist_add(d_mtx[di][dj].lst, t);
                }
            }
        }
    }
    return d_mtx;
}


uint8_t __exists_marked_transition(uint8_t ***trans_tb, distinct ** d_mtx,size_t nstates, size_t alph_sz, size_t i, size_t j){
    size_t di, dj;
    for (size_t sym = 0; sym < alph_sz; sym++) {
        di = dfa_delta(trans_tb, nstates, i, sym);
        dj = dfa_delta(trans_tb, nstates, j, sym);
        if (d_mtx[di][dj].val){
            return 1;
        }
    }
    return 0;
}

void __mark_recursively(distinct **d_mtx, llist *lst){
    tuple *t;
    while( (t = llist_pop(lst)) ){
        d_mtx[t->a][t->b].val = 1;

        __mark_recursively(d_mtx, d_mtx[t->a][t->b].lst);
        free(t);
    }
}
