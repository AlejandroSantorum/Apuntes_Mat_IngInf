########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic -ansi
EJS = p2_e4
########################################################
OBJECTSP2_E4 = p2_e4.o graph.o stack_fp.o node.o functions.o
########################################################

all: $(EJS) clear

p2_e4: $(OBJECTSP2_E4)
	$(CC) $(CFLAGS) -o p2_e4 $(OBJECTSP2_E4)


p2_e4.o: p2_e4.c graph.h stack_fp.h
	$(CC) $(CFLAGS) -c p2_e4.c

graph.o: graph.c graph.h
	$(CC) $(CFLAGS) -c graph.c

stack_fp.o: stack_fp.c stack_fp.h
	$(CC) $(CFLAGS) -c stack_fp.c

node.o: node.c node.h
	$(CC) $(CFLAGS) -c node.c

functions.o: functions.c functions.h
	$(CC) $(CFLAGS) -c functions.c

clear:
	rm -rf *.o 

clean:
	rm -rf *.o $(EJS)

run:
	@echo ">>>>>>Running p2_e4”
	./p2_e4 grafo.txt

runv:
	@echo ">>>>>>Running graph_test with valgrind"
	valgrind --leak-check=full ./p2_e4 grafo.txt
