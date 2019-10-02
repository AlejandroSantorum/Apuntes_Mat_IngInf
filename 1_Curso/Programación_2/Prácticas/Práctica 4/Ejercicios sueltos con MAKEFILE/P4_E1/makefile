########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic -ansi
EJS = p4_e1
########################################################
## list.o se necesita si se tiene implementado el opcional en P4_E3
OBJECTSP4_E1 = p4_e1.o tree.o functions.o
########################################################

all: $(EJS) clear

p4_e1: $(OBJECTSP4_E1)
	$(CC) $(CFLAGS) -o p4_e1 $(OBJECTSP4_E1)

p4_e1.o: p4_e1.c tree.h functions.h
	$(CC) $(CFLAGS) -c p4_e1.c
	
tree.o: tree.c tree.h
	$(CC) $(CFLAGS) -c tree.c

functions.o: functions.c functions.h
	$(CC) $(CFLAGS) -c functions.c

clear:
	rm -rf *.o 

clean:
	rm -rf *.o $(EJS)

run:
	@echo ">>>>>>Running p4_e1"
	./p4_e1

runv:
	@echo ">>>>>>Running p4_e1 with valgrind"
	valgrind --leak-check=full ./p4_e1
