/*******************************************************************************

    Authors:
        · Rafael Sanchez Sanchez - rafael.sanchezs@estudiante.uam.es
        · Alejandro Santorum Varela - alejandro.santorum@estudiante.uam.es
    File: utils.c
    Project: First assignment AUTLEN
    Date: November 14, 2019

*******************************************************************************/

#include "utils.h"


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
void sq_mtx_mult(uint8_t **mtxA, uint8_t **mtxB, uint8_t **res, size_t size){
    if (!mtxA || !mtxB || !res){
        return;
    }
    uint8_t **res_tmp = sq_mtx_new(size);
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            for (size_t k = 0; k < size; k++) {
                res_tmp[i][j] += mtxA[i][k] * mtxB[k][j];
            }
        }
    }

    sq_mtx_cpy(res, res_tmp, size);
    sq_mtx_delete(res_tmp, size);
}

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
void sq_mtx_power (uint8_t **mtx, uint8_t **res, size_t size, size_t power) {
    if (!mtx || !res){
        return;
    }
    //Initialize res to identity matrix
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            if (i - j){
                res[i][j] = 0;
            }else{
                res[i][j] = 1;
            }
        }
    }
    //Multiply
    for (size_t i = 1; i <= power; i++) {
        sq_mtx_mult(mtx, res, res, size);
    }
}

/**
 sq_mtx_new
 Input:
     size_t sz: matrix size
 Returns:
     uint8_t double pointer: pointer to a squared uint8_t matrix of size 'sz'
     with allocated memory
*/
uint8_t **sq_mtx_new(size_t sz){
    uint8_t **mtx;
    mtx = calloc(sz, sizeof(uint8_t *));
    for (size_t i = 0; i < sz; i++) {
        mtx[i] = calloc(sz, sizeof(uint8_t));
    }
    return mtx;
}

/**
 sq_mtx_delete
 Input:
     uint8_t **mtx: squared matrix of uint8_t
     size_t sz: matrix size
 Returns:
     Void.
     It frees the allocated memory for a given matrix
*/
void sq_mtx_delete(uint8_t **mtx, size_t sz){
    if (mtx) {
        for (size_t i = 0; i < sz; i++) {
            if (mtx[i]){
                free(mtx[i]);
                mtx[i] = NULL;
            }
        }
        free(mtx);
        mtx = NULL;
    }
}

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
void sq_mtx_cpy(uint8_t **dest, uint8_t **src, size_t sz){
    if(!dest || !src){
        return;
    }
    for (size_t i = 0; i < sz; i++) {
        memcpy(dest[i], src[i], sz * sizeof(uint8_t));
    }
}

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
int fprintf_sq_mtx(FILE *f, uint8_t **mtx, size_t sz) {
    if (!f || !mtx) return 0;
    int chars = 0;
    chars += fprintf(f, "\n\n------- MTX --------\n");
    for (size_t i = 0; i < sz; i++) {
        for (size_t j = 0; j < sz; j++) {
            chars += fprintf(f, "%d\t", mtx[i][j]);
        }
        chars += fprintf(f, "\n");
    }
    chars += fprintf(f, "--------------------\n\n");

    return chars;
}


/******************************************************************
 *
 * Utilities for deterministic finite automata
 *
*******************************************************************/
int dfa_delta(uint8_t ***trans_tb, uint8_t nstates, uint8_t from, uint8_t sym_idx){
    for (size_t i = 0; i < nstates; i++) {
        if (trans_tb[from][sym_idx][i] == 1){
            return i;
        }
    }
    return -1;
}

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
char **get_alphabet(AFND *afnd, size_t *arr_sz){
    if (!afnd) {
        return NULL;
    }
    *arr_sz = AFNDNumSimbolos(afnd);
    char **alphabet = calloc(*arr_sz, sizeof(char *));
    for (size_t i = 0; i < *arr_sz; i++) {
        alphabet[i] = AFNDSimboloEn(afnd, i);
    }
    return alphabet;
}

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
uint8_t *get_initial_states(AFND *afnd, size_t *arr_sz){
    if (!afnd) {
        return NULL;
    }
    *arr_sz = AFNDNumEstados(afnd);
    uint8_t *initial_states = calloc(*arr_sz, sizeof(uint8_t));
    for (size_t i = 0; i < *arr_sz; i++) {
        initial_states[i] = (AFNDTipoEstadoEn(afnd, i) == INICIAL);
        initial_states[i] |= (AFNDTipoEstadoEn(afnd, i) == INICIAL_Y_FINAL);
    }
    return initial_states;
}

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
uint8_t *get_final_states(AFND *afnd, size_t *arr_sz){
    if (!afnd) {
        return NULL;
    }
    *arr_sz = AFNDNumEstados(afnd);
    uint8_t *final_states = calloc(*arr_sz, sizeof(uint8_t));
    for (size_t i = 0; i < *arr_sz; i++) {
        final_states[i] = (AFNDTipoEstadoEn(afnd, i) == FINAL);
        final_states[i] |= (AFNDTipoEstadoEn(afnd, i) == INICIAL_Y_FINAL);
    }
    return final_states;
}

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
char ** get_states_names(AFND *afnd, size_t *arr_sz){
    if (!afnd) {
        return NULL;
    }
    *arr_sz = AFNDNumEstados(afnd);
    char **state_names = calloc(*arr_sz, sizeof(char *));
    for (size_t i = 0; i < *arr_sz; i++) {
        state_names[i] = AFNDNombreEstadoEn(afnd, i);
    }
    return state_names;
}

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
uint8_t ***get_nfa_transition_table(AFND *afnd){
    size_t nstates = AFNDNumEstados(afnd);
    size_t nsym = AFNDNumSimbolos(afnd);

    uint8_t ***trans_tb = calloc(nstates, sizeof(uint8_t **));
    for (size_t i = 0; i < nstates; i++) {
        trans_tb[i] = calloc(nsym, sizeof(uint8_t *));
        for (size_t j = 0; j < nsym; j++) {
            trans_tb[i][j] = calloc(nstates, sizeof(uint8_t));
        }
    }

    for (size_t i = 0; i < nstates; i++) {
        for (size_t j = 0; j < nsym; j++) {
            for (size_t k = 0; k < nstates; k++) {
                trans_tb[i][j][k] = AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, i, j, k);
            }
        }
    }

    return trans_tb;
}

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
void delete_nfa_transition_table(uint8_t ***trans_tb, size_t nstates, size_t nsym){
    if(!trans_tb) {
        return;
    }
    for (size_t i = 0; i < nstates; i++) {
        if (!trans_tb[i]){
            continue;
        }
        for (size_t j = 0; j < nsym; j++) {
            if (trans_tb[i][j]) {
                free(trans_tb[i][j]);
                trans_tb[i][j] = NULL;
            }
        }
        free(trans_tb[i]);
        trans_tb[i] = NULL;
    }
    free(trans_tb);
    trans_tb = NULL;
}

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
uint8_t **get_lambda_clausure(AFND *afnd, size_t *tb_sz){
    AFND *c_afnd = AFNDCierraLTransicion(afnd);
    size_t nstates = AFNDNumEstados(c_afnd);
    *tb_sz = nstates;
    uint8_t **lambda_cl = sq_mtx_new(nstates);

    for (size_t i = 0; i < nstates; i++) {
        for (size_t j = 0; j < nstates; j++) {
            lambda_cl[i][j] = AFNDCierreLTransicionIJ(afnd, i, j);
        }
    }

    return lambda_cl;
}



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
     It creates the DFA from the precalculated transition table and alphabet.
     It translates our structures to afnd.h structures
*/
AFND *get_dfa_object(row *afd_table, char **alphabet, size_t alph_sz, size_t dfa_states, size_t nstates, char **state_names){

    if (!afd_table || !alphabet) return NULL;
    AFND *afd;
    char *state_name_1 = calloc(2*(nstates+2), sizeof(char));
    char *state_name_2 = calloc(2*(nstates+2), sizeof(char));
    afd = AFNDNuevo("determinista", dfa_states, alph_sz);

    for (size_t i = 0; i < alph_sz; i++) {
        AFNDInsertaSimbolo(afd, alphabet[i]);
    }

    for (size_t i = 0; i < dfa_states; i++) {
        cstate_to_string(afd_table[i].state_from, state_name_1, 2*(nstates + 1), state_names);
        AFNDInsertaEstado(afd, state_name_1, cstate_get_type(afd_table[i].state_from));
    }

    for (size_t i = 0; i < dfa_states; i++) {
        cstate_to_string(afd_table[i].state_from, state_name_1, 2*(nstates + 1), state_names);
        for (size_t j = 0; j < alph_sz; j++) {
            if (cstate_is_valid(afd_table[i].state_to[j])){
                cstate_to_string(afd_table[i].state_to[j], state_name_2, 2*(nstates + 1), state_names);
                AFNDInsertaTransicion(afd, state_name_1, alphabet[j], state_name_2);
            }
        }
    }
    free(state_name_1);
    free(state_name_2);
    return afd;
}
