#include <stdio.h>

int main ()
{
    int edad;
    double inferior, superior;
    
    printf ("Introduzca su edad: ");
    scanf ("%d", &edad);
    
    inferior = 0.65 * (220 - edad);
    superior = 0.85 * (220 - edad);
    
    printf ("El intervalo cardiovascular está entre %.0lf y %.0lf\n", inferior, superior);
    
    return 0;
}