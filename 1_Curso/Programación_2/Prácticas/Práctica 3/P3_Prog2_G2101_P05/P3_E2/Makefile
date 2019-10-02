########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic -ansi
EJS = p3_e2
########################################################
OBJECTSP3_E2 = p3_e2.o queue.o graph.o node.o functions.o
########################################################

all: $(EJS) clear

p3_e2: $(OBJECTSP3_E2)
	$(CC) $(CFLAGS) -o p3_e2 $(OBJECTSP3_E2)

p3_e2.o: p3_e2.c queue.h graph.h functions.h
	$(CC) $(CFLAGS) -c p3_e2.c

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c

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
	@echo ">>>>>>Running p3_e2”
	./p3_e2 nodos.txt

runv:
	@echo ">>>>>>Running p3_e2  with valgrind"
	valgrind --leak-check=full ./p3_e2 nodos.txt

