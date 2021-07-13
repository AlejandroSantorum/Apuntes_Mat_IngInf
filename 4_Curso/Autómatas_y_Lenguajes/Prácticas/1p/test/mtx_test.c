#include "../srclib/utils.h"

int main(int argc, char const *argv[]) {
    uint8_t **mtxA;
    uint8_t **mtxB;
    uint8_t **res;

    mtxA = sq_mtx_new(2);
    mtxB = sq_mtx_new(2);
    res = sq_mtx_new(2);
    mtxA[0][0] = mtxA[1][1] = 1;
    mtxA[1][0] = mtxA[0][1] = 2;
    mtxB[0][0] = 1;
    mtxB[0][1] = 2;
    mtxB[1][0] = 3;
    mtxB[1][1] = 4;

    fprintf_sq_mtx(stdout, mtxA, 2);
    fprintf_sq_mtx(stdout, mtxB, 2);
    fprintf_sq_mtx(stdout, res, 2);

    sq_mtx_power(mtxA, res, 2, 2);
    fprintf_sq_mtx(stdout, res, 2);
    sq_mtx_power(mtxA, res, 2, 4);
    fprintf_sq_mtx(stdout, res, 2);
    sq_mtx_power(mtxB, res, 2, 1);
    fprintf_sq_mtx(stdout, res, 2);
    sq_mtx_power(mtxB, res, 2, 0);
    fprintf_sq_mtx(stdout, res, 2);

    sq_mtx_delete(mtxA, 2);
    sq_mtx_delete(mtxB, 2);
    sq_mtx_delete(res, 2);
    return 0;
}
