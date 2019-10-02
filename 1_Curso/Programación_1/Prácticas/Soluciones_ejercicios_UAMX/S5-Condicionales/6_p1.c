/* NOTA: Este programa admite otras posibles soluciones */

#include <stdio.h>

typedef struct
{
    int uno;
    int dos;
    int tres;
}Numeros;

int main () 
{
    Numeros num;

    printf("Introduce el primer número: ");
    scanf("%d", &num.uno);
    printf("Introduce el segundo número: ");
    scanf("%d", &num.dos);
    printf("Introduce el tercer número: ");
    scanf("%d", &num.tres);

    if ( (num.uno==num.dos) && (num.dos==num.tres) )
        printf("Los tres números son iguales");
    else if ( (num.uno!=num.dos) && (num.dos!=num.tres) && (num.uno!=num.tres) )
        printf("Los tres números son diferentes");
    else
        printf("Hay dos números iguales y uno diferente");

    return 0;
}