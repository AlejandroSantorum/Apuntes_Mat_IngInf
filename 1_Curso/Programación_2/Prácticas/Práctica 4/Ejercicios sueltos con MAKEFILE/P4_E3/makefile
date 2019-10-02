########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic -ansi
EJS = p4_e3
########################################################
## list.o se necesita si se tiene implementado el opcional en P4_E3
OBJECTSP4_E3 = p4_e3.o tree.o list.o functions.o
########################################################

all: $(EJS) clear

p4_e3: $(OBJECTSP4_E3)
	$(CC) $(CFLAGS) -o p4_e3 $(OBJECTSP4_E3)

p4_e3.o: p4_e3.c tree.h list.h functions.h
	$(CC) $(CFLAGS) -c p4_e3.c
	
tree.o: tree.c tree.h
	$(CC) $(CFLAGS) -c tree.c
	
list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c

functions.o: functions.c functions.h
	$(CC) $(CFLAGS) -c functions.c

clear:
	rm -rf *.o 

clean:
	rm -rf *.o $(EJS)

run:
	@echo ">>>>>>Running p4_e3"
	./p4_e3

runv:
	@echo ">>>>>>Running p4_e3 with valgrind"
	valgrind --leak-check=full ./p4_e3
