#include <stdio.h>
#include <math.h>

int esPrimo (int n){
    int i=2;
    
    while(i<=(sqrt(n))){
        if(n%i==0){
            return 0;
        }
        else
            i++;
    }
    return 1;
}

int main(){
    int n, x, primo, primogemelo1, primogemelo2;
    
    printf("Introduce un número para evaluarlo: ");
    scanf("%d", &n);
    
    primo = esPrimo(n);
    
    if (primo==0){
        printf("%d no es primo", n);
    }   
    else{
        primogemelo1 = esPrimo(n+2);
        primogemelo2 = esPrimo(n-2);
        
        if((primogemelo1==1)&&(primogemelo2==0)){
            printf("El numero %d es primo y el %d es primo gemelo", n, n+2);
        }
        else if((primogemelo1==0)&&(primogemelo2==1)){
            printf("El numero %d es primo y el %d es primo gemelo", n, n-2);
        }
        else if((primogemelo1==1)&&(primogemelo2==1)){
            printf("El numero %d es primo y el %d y el %d son primos gemelos", n, n-2, n+2);
        }
        else{
            printf("El numero %d no tiene primos gemelos", n);
        }
    }
    
    return 0;
}    
    