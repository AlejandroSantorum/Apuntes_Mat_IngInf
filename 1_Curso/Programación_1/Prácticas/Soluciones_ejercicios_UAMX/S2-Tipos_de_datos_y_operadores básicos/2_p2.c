#include <stdio.h>

int main () 
{

    int edad;
    double altura, pesoIdeal;
    char inicial;

    printf ("Por favor, introduce la altura en cm: ");
    scanf ("%lf", &altura);

    printf ("Por favor, introduce la edad en años: ");
    scanf ("%d", &edad);

    printf ("Por último, introduce la inicial del nombre: ");
    scanf ("\n%c", &inicial);

    pesoIdeal = altura - 100 + (9 * edad) / 100.0;

    printf ("\nEl peso ideal de %c, que mide %.1lf cm y tiene %d años es de %.3lf kg.", inicial, altura, edad, pesoIdeal);

    return 0;

}