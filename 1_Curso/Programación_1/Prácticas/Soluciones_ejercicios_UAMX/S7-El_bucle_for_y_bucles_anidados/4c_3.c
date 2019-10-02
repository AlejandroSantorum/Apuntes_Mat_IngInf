#include <stdio.h>

int main ()
{
    int i, numero, tabla[32];

    do
    {
        printf("Introduce un entero positivo: ");
        scanf("%d", &numero);
    }while(numero<=0);

    for(i=0; numero>0; i++)
    {
        tabla[i]=numero%2;
        numero /= 2;
    }

    printf("El número convertido a binario es: ");

    for(i--; i>=0; i--)
        printf("%d", tabla[i]);

    return 0; 
}