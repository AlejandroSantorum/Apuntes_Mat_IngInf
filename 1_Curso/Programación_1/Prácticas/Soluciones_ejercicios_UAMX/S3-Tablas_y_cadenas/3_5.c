#include <stdio.h>
#include <string.h>

#define TAM 20

int main ()
{
    char cadena1[TAM], cadena2[TAM];
    int valor;

    printf("Introduce una cadena: ");
    scanf("%s", cadena1);

    printf("Introduce otra cadena: ");
    scanf("%s", cadena2);

    valor = strcmp (cadena1, cadena2);

    printf("El valor devuelto por la comparación de las cadenas es: %d", valor);

    return 0;
}