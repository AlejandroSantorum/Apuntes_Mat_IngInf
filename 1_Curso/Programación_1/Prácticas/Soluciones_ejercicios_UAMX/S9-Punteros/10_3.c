#include <stdio.h>
 
void estadistica (int x, int y, double * pMedia, double * pVar)
{
    // Si pMedia vale &media (como ocurre tras la llamada desde main) entonces
    // la siguiente instrucción es igual a
    // media = (x + y)/2.0;
    *pMedia = (x + y)/2.0;
 
    // Si, además, pVar vale &varianza entonces
    // la siguiente instrucción es igual a
    // varianza = (x*x + y*y)/2.0 - media * media;
    *pVar = (x*x + y*y)/2.0 - *pMedia * *pMedia;
}
 
int main ()
{
    int a, b;
    double media, varianza;
 
    a = 1;
    b = 3;
 
    // Las instrucciones de la función estadistica
    // trabajan con las variables media y varianza de main,
    // no directamente, sino a través de sus direcciones
    // de memoria: &media y &varianza
     estadistica (a, b, &media, &varianza);
 
    printf ("Media = %g\nVarianza = %g\n", media, varianza);
 
    return 0;
}
 
