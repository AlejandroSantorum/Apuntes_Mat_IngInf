#include <stdio.h>

#define TAM 3

int main ()
{
    int i, j;
    int a [TAM][TAM] = {1,2,3,4,5,6,7,8,9};
    int b [TAM][TAM] = {0,1,2,4,2,3,1,4,5};
    int c [TAM][TAM];

    for (i=0; i<TAM; i++)
        for (j=0; j<TAM; j++)
            c[i][j] = a[i][j] + b[i][j];

    for (i=0; i<TAM; i++)
    {
        for (j=0; j<TAM; j++)
            printf ("%3d ", c[i][j]);
        printf ("\n");
    }
 
    return 0;
}