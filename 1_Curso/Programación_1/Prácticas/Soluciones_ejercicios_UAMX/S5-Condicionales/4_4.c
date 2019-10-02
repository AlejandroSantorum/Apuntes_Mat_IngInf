#include <stdio.h>

int main ()
{
    int edad;

    printf("Introduce tu edad: ");
    scanf("%d", &edad);

    if (edad<18)
        printf("Eres menor de edad");
    else if (edad%3 == 0) //Una alternativa sería: else if (!(edad%3))
        printf("Eres mayor de edad y tu edad es múltiplo de tres");
    else
        printf("Eres mayor de edad y tu edad no es múltiplo de tres");

 return 0;

}