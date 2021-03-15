/****************** CLIENT CODE ****************/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define MAXLINE 1024

int main(int argc, char **argv){
  int clientSocket;
  char buffer[1024];
  char sendline[MAXLINE], recvline[MAXLINE];
  struct sockaddr_in serverAddr;
  socklen_t addr_size;
  
  
  if (argc!=2)
  {
    fprintf(stderr,"Usage: %s <direccion IP servidor>\n",argv[0]);
    return 1;
  }


  clientSocket = socket(PF_INET, SOCK_STREAM, 0);
  

  serverAddr.sin_family = AF_INET;

  serverAddr.sin_port = htons(7891);

  
  // Server IP address
  serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
  
  /* Set all bits of the padding field to 0 */
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  


  addr_size = sizeof serverAddr;
    
  if (connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size)==-1)
  {
    fprintf(stderr,"Error conectando con servidor\n");
    return 1;
  }
  
     memset(recvline,0,MAXLINE);
    if (recv(clientSocket, recvline, MAXLINE,0) == 0){
      //error: server terminated prematurely
      perror("The server terminated prematurely");
      return 1;
    }
    printf("%s", "String received from the server:\n");
    fputs(recvline, stdout);
    printf("**************\n\n");
      
  
  
   memset(sendline,0,MAXLINE);
   memset(recvline,0,MAXLINE);
  
   while (fgets(sendline, MAXLINE, stdin) != NULL) {

      send(clientSocket, sendline, strlen(sendline), 0);

      if (recv(clientSocket, recvline, MAXLINE,0) == 0){
	//error: server terminated prematurely
	perror("The server terminated prematurely");
	return 1;
      }
      printf("%s", "String received from the server:\n");
      fputs(recvline, stdout);
      printf("\n**************\n\n");
      
      memset(recvline,0,MAXLINE);
      memset(sendline,0,MAXLINE);
  }


  close(clientSocket);

  return 0;
}