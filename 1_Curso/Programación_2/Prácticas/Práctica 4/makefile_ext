########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic -ansi
EJS = p4_e2 p4_e2_bal 
########################################################
## list.o se necesita si se tiene implementado el opcional en P4_E3
OBJECTSP4_E2 = p4_e2.o tree.o list.o functions.o node_p4.o
########################################################

all: $(EJS) clear

p4_e2: $(OBJECTSP4_E2)
	$(CC) $(CFLAGS) -o p4_e2 $(OBJECTSP4_E2)

p4_e2_bal: $(OBJECTSP4_E2)
	$(CC) $(CFLAGS) -o p4_e2_bal $(OBJECTSP4_E2)

p4_e2.o: p4_e2.c tree.h functions.h
	$(CC) $(CFLAGS) -c p4_e2.c

p4_e4.o: p4_e4.c tree.h functions.h
	$(CC) $(CFLAGS) -c p4_e4.c

functions.o: functions.c functions.h
	$(CC) $(CFLAGS) -c functions.c

list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c

tree.o: tree.c tree.h
	$(CC) $(CFLAGS) -c tree.c

node_p4.o: node_p4.c node.h
	$(CC) $(CFLAGS) -c node_p4.c

clear:
	rm -rf *.o 

clean:
	rm -rf *.o $(EJS)

run:
	@echo ">>>>>>Running p4_e2"
	./p4_e2 dict10.dat
	@echo ">>>>>>Running p4_e2_bal"
	./p4_e2_bal dict10.dat

runv:
	@echo ">>>>>>Running p4_e2 with valgrind"
	valgrind --leak-check=full ./p4_e2 dict10.dat
	@echo ">>>>>>Running p4_e2_bal with valgrind"
	valgrind --leak-check=full ./p4_e2_bal dict10.dat
