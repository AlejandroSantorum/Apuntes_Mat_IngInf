
int
main(int argc, char **argv)
{
        int             listenfd, i;
        socklen_t       addrlen;        

        /* Contiene las llamadas a socket(), bind() y listen() */                
        listenfd = Tcp_listen(argv[1], argv[2], &addrlen);
        
        my_lock_init(NULL);
        for (i = 0; i < nchildren; i++)
                if ( (childpid = Fork()) == 0) {     
                        child_main(i, listenfd, addrlen);       /* Esta funcion nunca retorna */
                }

        for ( ; ; )
                pause();        /* Todo el trabajo lo hacen los hijos */
}

void
child_main(int i, int listenfd, int addrlen)
{
        
        for ( ; ; ) {
                clilen = addrlen;
                my_lock_wait();
                connfd = Accept(listenfd, cliaddr, &clilen);
                my_lock_release();

                process_request(connfd);              
                Close(connfd);
        }
}
