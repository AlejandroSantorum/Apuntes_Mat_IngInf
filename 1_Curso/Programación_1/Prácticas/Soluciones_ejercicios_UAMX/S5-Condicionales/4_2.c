#include <stdio.h>

int main ()
{
    int edad, mayor;

    printf("Introduce tu edad: ");
    scanf("%d", &edad);

    mayor = ((edad>17) && (edad%3 != 0)); //Una alternativa sería:  mayor = ((edad>17) && (edad%3));

    printf("La variable mayor es: %d", mayor);

    return 0;
}