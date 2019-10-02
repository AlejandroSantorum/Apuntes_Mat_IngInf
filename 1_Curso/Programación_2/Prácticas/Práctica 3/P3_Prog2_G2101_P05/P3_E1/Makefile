########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic -ansi
EJS = p3_e1
########################################################
OBJECTSP3_E1 = p3_e1.o queue.o node.o functions.o
########################################################

all: $(EJS) clear

p3_e1: $(OBJECTSP3_E1)
	$(CC) $(CFLAGS) -o p3_e1 $(OBJECTSP3_E1)

p3_e1.o: p3_e1.c queue.h node.h functions.h
	$(CC) $(CFLAGS) -c p3_e1.c

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c

node.o: node.c node.h
	$(CC) $(CFLAGS) -c node.c

functions.o: functions.c functions.h
	$(CC) $(CFLAGS) -c functions.c

clear:
	rm -rf *.o 

clean:
	rm -rf *.o $(EJS)

run:
	@echo ">>>>>>Running p3_e1”
	./p3_e1 nodos.txt

runv:
	@echo ">>>>>>Running p3_e1  with valgrind"
	valgrind --leak-check=full ./p3_e1 nodos.txt
