
int main(int argc, char **argv)
{
        int                             listenfd, connfd;
        pthread_t               tid;
        socklen_t               clilen, addrlen;
        struct sockaddr *cliaddr;

        /* Contiene las llamadas a socket(), bind() y listen() */                
        listenfd = Tcp_listen(argv[1], argv[2], &addrlen);

        for ( ; ; ) {        
                connfd = Accept(listenfd, cliaddr, &clilen);

                Pthread_create(&tid, NULL, &doit, (void *) connfd);
        }
}

void * doit(void *arg)
{
        void    web_child(int);

        Pthread_detach(pthread_self());
        process_request((int) arg);
        Close((int) arg);
        return(NULL);
}
