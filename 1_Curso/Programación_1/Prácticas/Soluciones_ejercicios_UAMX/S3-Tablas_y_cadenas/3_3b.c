#include <stdio.h>

#define TAM 3

int main() 
{
    int matriz[TAM][TAM];

    printf ("Introduce un d�a: ");
    scanf ("%d", &matriz[0][0]);

    printf ("Introduce un mes: ");
    scanf ("%d", &matriz[0][1]);

    printf ("Introduce un a�o: ");
    scanf ("%d", &matriz[0][2]);

    printf ("\nIntroduce otro d�a: ");
    scanf ("%d", &matriz[1][0]);

    printf ("Introduce otro mes: ");
    scanf ("%d", &matriz[1][1]);

    printf ("Introduce otro a�o: ");
    scanf ("%d", &matriz[1][2]);

    matriz[2][0] = matriz[0][0] - matriz[1][0];
    matriz[2][1] = matriz[0][1] - matriz[1][1];
    matriz[2][2] = matriz[0][2] - matriz[1][2];

    printf("\nLa diferencia en d�as es: %d\n", matriz[2][0]);
    printf("La diferencia en meses es: %d\n", matriz[2][1]);
    printf("La diferencia en a�os es: %d", matriz[2][2]);

    return 0;
}