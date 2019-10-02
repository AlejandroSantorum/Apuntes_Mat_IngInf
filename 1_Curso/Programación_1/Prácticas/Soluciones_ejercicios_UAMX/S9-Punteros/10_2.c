#include <stdio.h>
 
/* El primer argumento se puede pasar por valor puesto que no se va a modificar su valor en la función */
/* El segundo argumento se ha de pasar necesariamente por referencia, pues se va a modificar su valor y se quiere que esta modificación permanezca al acabar la función */
void niParesNiNones(int uno, int * dos)
{
    if ( (uno%2 && *dos%2) || (!(uno%2) && !(*dos%2)) )
        (*dos)++;
}
 
int main ()
{
    int num1, num2;
    
    printf("Introduce un número entero: ");
    scanf("%d", &num1);
    
    printf("Introduce otro número entero: ");
    scanf("%d", &num2);
    
    niParesNiNones(num1, &num2);
    
    printf("Los números tras llamar a la función son: %d y %d", num1, num2);
    
    return 0;
}