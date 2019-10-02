########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic -ansi
EJS = p2_e2
########################################################
OBJECTSP2_E2 = p2_e2.o graph.o stack_element.o node.o element.o
########################################################

all: $(EJS) clear

p2_e2: $(OBJECTSP2_E2)
	$(CC) $(CFLAGS) -o p2_e2 $(OBJECTSP2_E2)


p2_e2.o: p2_e2.c graph.h stack_element.h
	$(CC) $(CFLAGS) -c p2_e2.c

graph.o: graph.c graph.h
	$(CC) $(CFLAGS) -c graph.c

stack_element.o: stack_element.c stack_element.h
	$(CC) $(CFLAGS) -c stack_element.c

node.o: node.c node.h
	$(CC) $(CFLAGS) -c node.c

element.o: element.c element.h
	$(CC) $(CFLAGS) -c element.c

clear:
	rm -rf *.o 

clean:
	rm -rf *.o $(EJS)

run:
	@echo ">>>>>>Running p2_e2”
	./p2_e2 grafo.txt

runv:
	@echo ">>>>>>Running graph_test with valgrind"
	valgrind --leak-check=full ./p2_e2 grafo.txt
