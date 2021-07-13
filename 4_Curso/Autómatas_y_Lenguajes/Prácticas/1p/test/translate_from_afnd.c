#include "../srclib/afnd.h"
#include "../srclib/utils.h"

int main(int argc, char const *argv[]) {
    AFND * p_afnd;
    p_afnd= AFNDNuevo("af11", 6, 3);

    AFNDInsertaSimbolo(p_afnd,"+");
    AFNDInsertaSimbolo(p_afnd, "0");
    AFNDInsertaSimbolo(p_afnd,".");

    AFNDInsertaEstado(p_afnd, "q0",INICIAL);
    AFNDInsertaEstado(p_afnd, "q1", NORMAL);
    AFNDInsertaEstado(p_afnd, "q2", NORMAL);
    AFNDInsertaEstado(p_afnd, "q3", NORMAL);
    AFNDInsertaEstado(p_afnd, "q4", NORMAL);
    AFNDInsertaEstado(p_afnd, "q5", FINAL);

    AFNDInsertaTransicion(p_afnd, "q0", "+", "q1");
    AFNDInsertaTransicion(p_afnd, "q1", "0", "q1");
    AFNDInsertaTransicion(p_afnd, "q1", "0", "q4");
    AFNDInsertaTransicion(p_afnd, "q1", ".", "q2");
    AFNDInsertaTransicion(p_afnd, "q2", "0", "q3");
    AFNDInsertaTransicion(p_afnd, "q3", "0", "q3");
    AFNDInsertaTransicion(p_afnd, "q4", ".", "q3");

    AFNDInsertaLTransicion(p_afnd, "q0", "q1");
    AFNDInsertaLTransicion(p_afnd, "q1", "q3");
    AFNDInsertaLTransicion(p_afnd, "q3", "q5");
    AFNDCierraLTransicion(p_afnd);

    size_t alph_sz;
    char **alphabet = get_alphabet(p_afnd, &alph_sz);

    for (size_t i = 0; i < alph_sz; i++) {
        printf("%s\n", alphabet[i]);
    }

    size_t nstates;
    uint8_t **lambda_cl = get_lambda_clausure(p_afnd, &nstates);
    fprintf_sq_mtx(stdout, lambda_cl, nstates);

    uint8_t ***trans_tb = get_first_transition_table(p_afnd);

    for (size_t i = 0; i < nstates; i++) {
        for (size_t j = 0; j < alph_sz; j++) {
            for (size_t k = 0; k < nstates; k++) {
                if(trans_tb[i][j][k])
                    printf("%ld %s %ld\n",i, alphabet[j], k);
            }
        }
    }

    delete_first_transition_table(trans_tb, nstates, alph_sz);

    sq_mtx_delete(lambda_cl, nstates);
    free(alphabet);
    AFNDElimina(p_afnd);

    return 0;
}
