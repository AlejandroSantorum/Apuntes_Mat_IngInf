/**************************************************************************
*	This is a simple echo server.  This demonstrates the steps to set up
*	a streaming server.
**************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

#define SERVER_PORT		9999
#define MAXBUF		1024

int main(void)
{   int sockfd;
	struct sockaddr_in self;
	char buffer[MAXBUF];

	// Creamos el socket tipo TCP */
    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
	{
		perror("Error en la creación del socket");
		exit(errno);
	}

	// Inicializamos estructura de dirección y puerto
	bzero(&self, sizeof(self));
	self.sin_family = AF_INET;
	self.sin_port = htons(SERVER_PORT);
	self.sin_addr.s_addr = INADDR_ANY;

	// Ligamos puerto al socket
    if ( bind(sockfd, (struct sockaddr*)&self, sizeof(self)) != 0 )
	{
		perror("socket--bind");
		exit(errno);
	}

	// OK, listos para escuchar...
	if ( listen(sockfd, 20) != 0 )
	{
		perror("socket--listen");
		exit(errno);
	}
	
	printf("Escuchando en [%s:%d]...\n", inet_ntoa(self.sin_addr), ntohs(self.sin_port));

	while (1)
	{	int clientfd;
		struct sockaddr_in client_addr;
		int addrlen=sizeof(client_addr);

		// Aceptamos conexiones
		clientfd = accept(sockfd, (struct sockaddr*)&client_addr, &addrlen);
		printf("Conexión desde [%s:%d]\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

		// De momento, solo hacemos eco
		send(clientfd, buffer, recv(clientfd, buffer, MAXBUF, 0), 0);

		// Cerramos la conexión
		close(clientfd);
	}

	close(sockfd);
	return 0;
}