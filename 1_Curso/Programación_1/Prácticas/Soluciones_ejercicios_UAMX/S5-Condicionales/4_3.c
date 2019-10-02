#include <stdio.h>

int main ()
{
    int edad;

    printf("Introduce tu edad: ");
    scanf("%d", &edad);

    if ((edad>17) && (edad%3 != 0)) //Una alternativa sería: if ((edad>17) && (edad%3))
        printf("Eres mayor de edad y tu edad no es múlltiplo de tres");
    else
        printf("Eres menor de edad o tu edad es múltiplo de tres");

 return 0;
}