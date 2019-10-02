#include <stdio.h>

#define TAM 32 //En el entorno en que estamos programando, un número entero puede ocupar un máximo de 32 bits

int main ()
{
    int i=0, numero, tabla[TAM];

    do
    {
        printf("Introduce un entero positivo: ");
        scanf("%d", &numero);
    }while(numero<=0);

    while(numero>0)
    {
        tabla[i]=numero%2;
        numero /= 2;
        i++;
    }

    i--;

    printf("El número convertido a binario es: ");

    while(i>=0)
    {
        printf("%d", tabla[i]);
        i--;
    }

    return 0;
}