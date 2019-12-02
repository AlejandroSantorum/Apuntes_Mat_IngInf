
int
main(int argc, char **argv)
{
	int					listenfd, connfd;	
	socklen_t			clilen, addrlen;
	struct sockaddr		*cliaddr;

	/* Contiene las llamadas a socket(), bind() y listen() */
	listenfd = Tcp_listen(argv[1], argv[2], &addrlen);	

	for ( ; ; ) {		
		connfd = Accept(listenfd, cliaddr, &clilen);

		if ( (childpid = Fork()) == 0) {				
			process_request(connfd);	/* Procesa la peticion */
			exit(0);
		}

		/* Padre cierra el descriptor de la conexion del hijo (duplicada) */
		Close(connfd);	
	}
}
