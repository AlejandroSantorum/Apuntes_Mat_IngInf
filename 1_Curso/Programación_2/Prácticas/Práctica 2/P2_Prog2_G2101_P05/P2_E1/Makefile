########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic -ansi
EJS = p2_e1
########################################################
OBJECTSP2_E1 = p2_e1.o element_int.o stack_element.o
########################################################

all: $(EJS) clear

p2_e1: $(OBJECTSP2_E1)
	$(CC) $(CFLAGS) -o p2_e1 $(OBJECTSP2_E1)


p2_e1.o: p2_e1.c stack_element.h
	$(CC) $(CFLAGS) -c p2_e1.c

element_int.o: element_int.c element_int.h
	$(CC) $(CFLAGS) -c element_int.c

stack_element.o: stack_element.c stack_element.h
	$(CC) $(CFLAGS) -c stack_element.c

clear:
	rm -rf *.o 

clean:
	rm -rf *.o $(EJS)

run:
	@echo ">>>>>>Running p2_e1”
	./p2_e1 grafo.txt

runv:
	@echo ">>>>>>Running p2_e1 with valgrind"
	valgrind --leak-check=full ./p2_e1 grafo.txt

