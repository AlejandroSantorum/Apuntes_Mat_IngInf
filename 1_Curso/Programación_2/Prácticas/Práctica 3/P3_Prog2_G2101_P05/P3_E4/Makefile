########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic -ansi
EJS = p3_e4
########################################################
OBJECTSP3_E4 = p3_e4.o list.o graph.o node.o functions.o
########################################################

all: $(EJS) clear

p3_e4: $(OBJECTSP3_E4)
	$(CC) $(CFLAGS) -o p3_e4 $(OBJECTSP3_E4)

p3_e4.o: p3_e4.c graph.h
	$(CC) $(CFLAGS) -c p3_e4.c

list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c

graph.o: graph.c graph.h
	$(CC) $(CFLAGS) -c graph.c

node.o: node.c node.h
	$(CC) $(CFLAGS) -c node.c

functions.o: functions.c functions.h
	$(CC) $(CFLAGS) -c functions.c

clear:
	rm -rf *.o 

clean:
	rm -rf *.o $(EJS)

run:
	@echo ">>>>>>Running p3_e4”
	./p3_e4 grafo.txt

runv:
	@echo ">>>>>>Running p3_e4  with valgrind"
	valgrind --leak-check=full ./p3_e4 grafo.txt
