########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic -ansi
EJS = p4_e4
########################################################
## list.o se necesita si se tiene implementado el opcional en P4_E3
OBJECTSP4_E4 = p4_e4.o tree.o functions.o
########################################################

all: $(EJS) clear

p4_e4: $(OBJECTSP4_E4)
	$(CC) $(CFLAGS) -o p4_e4 $(OBJECTSP4_E4)

p4_e4.o: p4_e4.c tree.h functions.h
	$(CC) $(CFLAGS) -c p4_e4.c
	
tree.o: tree.c tree.h
	$(CC) $(CFLAGS) -c tree.c

functions.o: functions.c functions.h
	$(CC) $(CFLAGS) -c functions.c

clear:
	rm -rf *.o 

clean:
	rm -rf *.o $(EJS)

run:
	@echo ">>>>>>Running p4_e4"
	./p4_e4

runv:
	@echo ">>>>>>Running p4_e4 with valgrind"
	valgrind --leak-check=full ./p4_e4
