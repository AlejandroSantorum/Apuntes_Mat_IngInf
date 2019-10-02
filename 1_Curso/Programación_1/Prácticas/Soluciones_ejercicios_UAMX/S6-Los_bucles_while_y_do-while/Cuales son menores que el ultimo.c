#include <stdio.h>

#define TAM 11

int main(){
    int i=0, j=0, n=0;
    double tabla[TAM];
    
    do{
        printf("¿Cuántos números quieres leer? (entre 2 y 10): ");
        scanf("%d", &n);

        if (n<2 || n>10)
            printf("Error, debes introducir un número entre 2 y 10\n");
    }while(n<2 || n>10);
    
    while (i<n){
        printf("Introduzca el numero %d de %d: ", i+1, n);
        scanf("%lf", &tabla[i]);
        i++;
    }
    
    while(j<n){
        if(tabla[j]<tabla[n-1]){
            printf("El numero %.2lf es menor que el %.2lf\n", tabla[j], tabla[n-1]);
        }
        j++;
    }
    
    return 0;
}
