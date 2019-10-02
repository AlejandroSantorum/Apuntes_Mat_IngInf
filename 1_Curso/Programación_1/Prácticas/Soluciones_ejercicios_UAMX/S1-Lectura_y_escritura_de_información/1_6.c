
#include <stdio.h>

int main() 
{

    double p1, p2, p3, p4, p5, p6, p7, c1, c2, final;
    
    printf("Introduce la calificación de la prueba 1: ");
    scanf("%lf", &p1);

    printf("Introduce la calificación de la prueba 2: ");
    scanf("%lf", &p2);
    
    printf("Introduce la calificación de la prueba 3: ");
    scanf("%lf", &p3);
    
    printf("Introduce la calificación de la prueba 4: ");
    scanf("%lf", &p4);
    
    printf("Introduce la calificación de la prueba 5: ");
    scanf("%lf", &p5);
    
    printf("Introduce la calificación de la prueba 6: ");
    scanf("%lf", &p6);
    
    printf("Introduce la calificación de la prueba 7: ");
    scanf("%lf", &p7);
    
    printf("Introduce la calificación del cuestionario 1: ");
    scanf("%lf", &c1);

    printf("Introduce la calificación del cuestionario 2: ");
    scanf("%lf", &c2);

    final = (p1+p2+p3+c1+2*p4+2*p5+3*p6+4*c2+5*p7)/20;
    printf("La calificación final de evaluación continua es %lf: ", final);
    
    /* Una solución alternativa sin necesidad de utilizar la variable final sería: */
    /* printf("La calificación final de evaluación continua es %lf: ", (p1+p2+p3+c1+2*p4+2*p5+3*p6+4*c2+5*p7)/20); */
    
    return 0;
}

