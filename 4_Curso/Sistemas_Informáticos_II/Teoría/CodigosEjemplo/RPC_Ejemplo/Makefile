
all: stubs server client

stubs: square.x
	rpcgen square.x

clean:
	rm square_clnt.c square_svc.c square.h square_xdr.c server client

server: server.c
	gcc -o server server.c square_svc.c square_xdr.c

client: client.c
	gcc -o client client.c square_clnt.c square_xdr.c
