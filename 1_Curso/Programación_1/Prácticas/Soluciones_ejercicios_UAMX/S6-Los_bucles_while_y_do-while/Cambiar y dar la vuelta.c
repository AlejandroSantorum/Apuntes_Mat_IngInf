#include <stdio.h>
#include <string.h>

#define TAM 50

int main(){
    char cadena[50], min, may;
    int i=0;
    
    printf("Introduzca una cadena de caracteres: ");
    scanf("%s", cadena);
    
    while (min<'a' || min>'z'){
        printf("Introduzca un caracter en minúscula: ");
        scanf("\n%c", &min);
        
        if(min<'a' || min>'z'){
            printf("Error. Introduzca un caracter en minuscula. Reintentelo.\n");
        }
    }
    
    while (may<'A' || may>'Z'){
        printf("Introduzca un caracter en mayuscula: ");
        scanf("\n%c", &may);
        
        if(may<'A' || may>'Z'){
            printf("Error. Introduzca un caracter en mayuscula. Reintentelo.\n");
        }
    }
    
    while(i<strlen(cadena)){
        if (cadena[i]==min){
            cadena[i]=may;
        }
        i++;
    }
    
    i=strlen(cadena);
    
    printf("%s", cadena);
    
    while(i>=0){
        printf("%c", cadena[i]);
        i--;
    }
    return 0;
}
