#include <stdio.h>
 
int main ()
{
    int    altura;
    double peso, indice;
  
    printf ("Introduzca peso (kg): ");
    scanf ("%lf", &peso);
 
    printf ("Introduzca altura (cm): ");
    scanf ("%d", &altura);
 
    indice = 10000 * peso / (altura * altura);
 
    if (indice < 21)
        printf ("Peso por debajo de lo normal\n");
    else if (indice < 25)
        printf ("Peso normal\n");
    else
        printf ("Sobrepeso\n");
    
    printf ("Indice = %.2lf\n", indice);
 
    return 0;
}