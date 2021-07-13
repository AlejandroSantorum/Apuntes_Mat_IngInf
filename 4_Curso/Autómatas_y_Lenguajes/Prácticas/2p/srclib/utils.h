/*******************************************************************************

    Authors:
        · Rafael Sanchez Sanchez - rafael.sanchezs@estudiante.uam.es
        · Alejandro Santorum Varela - alejandro.santorum@estudiante.uam.es
    File: utils.h
    Project: First assignment AUTLEN
    Date: November 14, 2019

*******************************************************************************/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include "afnd.h"
#include "current_state.h"

/******************************************************************
 *
 * Utilities to make some operations with squared matrix
 *
******************************************************************/

/**
 sq_mtx_mult
 Input:
     uint8_t **mtxA: squared matrix of uint8_t
     uint8_t **mtxB: squared matrix of uint8_t
     uint8_t **res: squared matrix of uint8_t
     size_t size: matrix sizes
 Returns:
     Void.
     It computes on matrix res the matrix multiplication A*B
*/
void sq_mtx_mult(uint8_t **mtxA, uint8_t **mtxB, uint8_t **res, size_t size);

/**
 sq_mtx_power
 Input:
     uint8_t **mtx: squared matrix of uint8_t
     uint8_t **res: squared matrix of uint8_t
     size_t size: matrix sizes
     size_t power: power value
 Returns:
     Void.
     It computes on matrix res the result of matrix mtx to the 'power'
*/
void sq_mtx_power(uint8_t **mtx, uint8_t **res, size_t size, size_t power);

/**
 sq_mtx_new
 Input:
     size_t sz: matrix size
 Returns:
     uint8_t double pointer: pointer to a squared uint8_t matrix of size 'sz'
     with allocated memory
*/
uint8_t **sq_mtx_new(size_t sz);

/**
 sq_mtx_delete
 Input:
     uint8_t **mtx: squared matrix of uint8_t
     size_t sz: matrix size
 Returns:
     Void.
     It frees the allocated memory for a given matrix
*/
void sq_mtx_delete(uint8_t **mtx, size_t sz);

/**
 sq_mtx_cpy
 Input:
     uint8_t **dest: squared matrix of uint8_t
     uint8_t **src: squared matrix of uint8_t
     size_t sz: matrix sizes
 Returns:
     Void.
     It copies the src matrix on dest matrix.
 Advanced description:
     It copies src matrix on dest matrix. Both matrices have to have
     pre-allocated memory.
*/
void sq_mtx_cpy(uint8_t **dest, uint8_t **src, size_t sz);

/**
 fprintf_sq_mtx
 Input:
     FILE *f: file pointer
     uint8_t **mtx: squared matrix of uint8_t
     size_t sz: matrix size
 Returns:
     Number of printed characters
 Advanced description:
     It outputs on FILE f the representation of the given matrix
*/
int fprintf_sq_mtx(FILE *f, uint8_t **mtx, size_t sz);

/******************************************************************
 *
 * Utilities for deterministic finite automata
 *
*******************************************************************/
int dfa_delta(uint8_t ***trans_tb, uint8_t nstates, uint8_t from, uint8_t sym_idx);

/******************************************************************
 *
 * Tuples linked list
 *
*******************************************************************/
typedef struct _tuple {
    uint8_t a;
    uint8_t b;
} tuple;


/******************************************************************
 *
 * Utilities to translate from the structures in afnd.h to a more simplified
 * structure that we know better.
 *
*******************************************************************/

/**
 get_alphabet
 Input:
     AFND *afnd: NDFA pointer
     size_t *arr_sz: pointer to a size_t
 Returns:
     The NDFA alphabet (char**)
 Advanced description:
     It returns the NDFA alphabet, that is an array of strings because each
     symbol could be a string; and it returns the alphabet size in arr_sz
*/
char **get_alphabet(AFND *afnd, size_t *arr_sz);

/**
 get_initial_states
 Input:
     AFND *afnd: NDFA pointer
     size_t *arr_sz: pointer to a size_t
 Returns:
     The NDFA initial states
 Advanced description:
     It returns the NDFA initial states, represented as an array of size equal to
     the number of NDFA total states. The initial states are marked with 1's,
     otherwise 0, i.e., state 3 is initial <=> array[3] == 1. It also returns the
     total number of states in arr_sz
*/
uint8_t *get_initial_states(AFND *afnd, size_t *arr_sz);

/**
 get_final_states
 Input:
     AFND *afnd: NDFA pointer
     size_t *arr_sz: pointer to a size_t
 Returns:
     The NDFA final states
 Advanced description:
     It returns the NDFA final states, represented as an array of size equal to
     the number of NDFA total states. The final states are marked with 1's,
     otherwise 0, i.e., state 5 is final <=> array[5] == 1. It also returns the
     total number of states in arr_sz
*/
uint8_t *get_final_states(AFND *afnd, size_t *arr_sz);

/**
 get_states_names
 Input:
     AFND *afnd: NDFA pointer
     size_t *arr_sz: pointer to a size_t
 Returns:
     The NDFA state names
 Advanced description:
     It returns the NDFA state names. It also returns the  total
     number of states in arr_sz
*/
char ** get_states_names(AFND *afnd, size_t *arr_sz);


/**
 get_nfa_transition_table
 Input:
     AFND *afnd: NDFA pointer
 Returns:
     The NDFA transition table
 Advanced description:
     It returns the NDFA transition table, represented as a 3-dimensional matrix.
     i.e, each row represents a state (ST), each column a symbol (SY) and each
     element of the table is an array of states that can be visited by state ST
     with input symbol SY. For eaxmple:
     __________________________
     |  |  'a'  |  'b'  | 'c' |
     |q0|{q1,q2}| {q1}  |  -  |  From q0 you can visit q1 or q2 with symb. 'a'
     |q1|  {q3} |{q1,q2}|  -  |
     |q2|  -    |  {q2} | {q0}|
     --------------------------
*/
uint8_t ***get_nfa_transition_table(AFND *afnd);

/**
 delete_nfa_transition_table
 Input:
     uint8_t ***trans_tb: NDFA transition table previously described
     size_t nstates: NDFA total number of states
     size_t nsym: alphabet total number of symbols
 Returns:
     Void.
     It frees pre-allocated memory for transition table
*/
void delete_nfa_transition_table(uint8_t ***trans_tb, size_t nstates, size_t nsym);

/**
 get_lambda_clausure
 Input:
     AFND *afnd: NDFA pointer
     size_t *tb_sz: pointer to a size_t value
 Returns:
     The lambda clausure matrix
 Advanced description:
     It returns the lambda clausure matrix, represented as a uint8_t matrix.
     It also returns the matrix size (it's squared) in tb_sz.
*/
uint8_t **get_lambda_clausure(AFND *afnd, size_t *tb_sz);



/******************************************************************
 *
 * Utilities to translate from our structures to afnd.h structures
 *
*******************************************************************/

/**
 get_dfa_object
 Input:
     row *afd_table: row pointer = representation of the transition table
     char **alphabet: alphabet precalculated with the get_alphabet function
     size_t alph_sz: alphabet size
     dfa_states: number of DFA states
     nstates: number of NDFA states
 Returns:
     The AFND OBJECT (IN THIS CASE IT IS ALREADY A DFA)
 Advanced description:
     It creates the DFA from the precalculated transition table and alphabet
*/
AFND *get_dfa_object(row *afd_table, char **alphabet, size_t alph_sz, size_t dfa_states, size_t nstates, char **state_names);
