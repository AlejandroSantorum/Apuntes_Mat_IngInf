/****************** SERVER CODE ****************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <time.h>

#define MAXLINE 1024

int main(){
  int welcomeSocket, newSocket;
  char buffer[MAXLINE];
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;
  int n;


  
  welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);
  
  if (welcomeSocket==-1)
  {
      fprintf(stderr,"ERROR creando socket\n");
      return 1;
  }
  

  serverAddr.sin_family = AF_INET;

  serverAddr.sin_port = htons(7891);

  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  
  /* Set all bits of the padding field to 0 */
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  


  if (bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr))==-1)
  {
    fprintf(stderr,"ERROR en bind\n");
    return 1;
  }


  if(listen(welcomeSocket,5)==0)
    printf("Listening\n");
  else
    printf("Error\n");


  addr_size = sizeof serverStorage;
  
  
  // suma, resta, multiplicación, y división de dos numeros enteros positivos
  // Formato: 2 bytes: tipo (0: suma, 1: resta, 2: multiplicacion, 3: division)
  // 2 bytes: primer entero
  // 2 bytes: segundo entero
  
   for ( ; ; ) {
      
     newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
  
     printf("%s\n","Received request...");
     
     

      strcpy(buffer,"Bienvenido a la libreria de numeros enteros entre 0 y 9: <type>(0: suma / 1:resta / 2: multiplicacion / 3: division)<operador1><operador2>\n");
      if (send(newSocket,buffer,strlen(buffer),0)==-1)
      {
	fprintf(stderr,"ERROR en send\n");
	return 1;
      }

     memset(buffer,0,MAXLINE);
     while ( (n = recv(newSocket, buffer, 1024,0)) > 0)  {
      printf("%s","String received from the client:\n");
      puts(buffer);
      
      
      char aux[2];
      aux[0]=buffer[0];
      aux[1]='\0';
      int type=atoi(aux);
      aux[0]=buffer[1];
      int op1=atoi(aux);
      aux[0]=buffer[2];  
      int op2=atoi(aux);
      int res=0;
      
      printf("Operation Request: type = %d op1=%d op2=%d\n",type,op1,op2);
      
      switch(type)
      {
	case 0: res=op1+op2; break;
	case 1: res=op1-op2; break;
	case 2: res=op1*op2; break;
	case 3: res=op1/op2; break;
	default: res=-1;
      }
      
      sprintf(buffer,"%d",res); 
      
      
      send(newSocket, buffer, n, 0);
     }

      if (n < 0) {
	perror("Read error");
	exit(1);
      }
      close(newSocket);

  }
 //close listening socket
 close (welcomeSocket);

  return 0;
}


