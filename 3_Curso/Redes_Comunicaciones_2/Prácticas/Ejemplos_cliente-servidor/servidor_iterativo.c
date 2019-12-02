  
int
main(int argc, char **argv)
{
        int listenfd, connfd;        
        socklen_t   clilen, addrlen;
        struct sockaddr *cliaddr;

        /* Contiene las llamadas a socket(), bind() y listen() */
        listenfd = Tcp_listen(argv[1], argv[2], &addrlen); 

        for ( ; ; ) {                
                connfd = Accept(listenfd, cliaddr, &clilen);

                process_request(connfd);              

                Close(connfd);                  
        }
}
