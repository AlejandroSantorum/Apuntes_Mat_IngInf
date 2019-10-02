#include <stdio.h>
#include <string.h>
#define TAM 1000

long conversorADecimal(char *s, long base);

int main()

{

  long x,base;
  char s[TAM];

  /* pide los datos */
  printf("Escribe una base: ");
  scanf("%ld",&base);
  printf("Escribe un numero en base %ld: ",base);
  scanf("%s",s);
  
  /* convierte el numero decimal a base base */
  x=conversorADecimal(s, base);

  /* imprime el resultado */
  printf("%s en base %ld corresponde a %ld en decimal\n",s,base,x);

}


/***** conversor de base decimal a base "base"   **********/

long conversorADecimal(char *s, long base)

{

  long i,x,j,num;

  /* escribe la cadena en orden inverso */
  for (i=strlen(s)-1,x=0,j=1; i>=0; i--,j*=base) {
    if (s[i]>='0' && s[i]<='9') {
      num=s[i]-'0';
    } else if (s[i]>'a' && s[i]<'z') {
      num=s[i]-'a'+10;
    } else if (s[i]>'A' && s[i]<'Z') {
      num=s[i]-'A'+10;
    }
    x+=num*j;
  }

  return x;
}
