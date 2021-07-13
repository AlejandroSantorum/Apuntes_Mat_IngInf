#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../srclib/afnd.h"
#include "../srclib/minimiza.h"

int main(int argc, char const *argv[]) {
    uint8_t trans_tb_aux[5][2][5] = { { {0, 1, 0, 0, 0},  {0, 0, 1, 0, 0} },
                                  { {0, 0, 0, 0, 0},  {0, 0, 0, 0, 0} },
                                  { {0, 1, 0, 0, 0},  {0, 1, 0, 0, 0} },
                                  { {0, 0, 0, 0, 0},  {0, 0, 1, 0, 0} },
                                  { {0, 0, 0, 0, 0},  {0, 0, 0, 1, 0} } };

    uint8_t ***trans_tb;
    trans_tb = calloc(5, sizeof(uint8_t **));
    for (size_t i = 0; i < 5; i++) {
        trans_tb[i] = calloc(2, sizeof(uint8_t *));
        for (size_t j = 0; j < 2; j++) {
            trans_tb[i][j] = calloc(5, sizeof(uint8_t));
        }
    }

    for (size_t i = 0; i < 5; i++) {
        for (size_t j = 0; j < 2; j++) {
            memcpy(trans_tb[i][j], trans_tb_aux[i][j], 5*sizeof(uint8_t));
        }
    }


    uint8_t ***new_trans_tb;
    new_trans_tb = _delete_unacc_states(trans_tb, 5, 0, 2);

    for (size_t i = 0; i < 5; i++) {
        printf("===========================\nFrom: %ld\t", i);
        for (size_t j = 0; j < 2; j++) {
            printf("with symbol index: %ld:\n[\t", j);
            for (size_t k = 0; k < 5; k++) {
                printf("%d\t", trans_tb[i][j][k]);
            }
            printf("]\n" );
        }
    }
    return 0;
}
