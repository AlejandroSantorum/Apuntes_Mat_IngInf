CC = gcc
CFLAGS = -Wall -g
EXE = a1_e2_test

all : $(EXE)

.PHONY : clean text
clean :
	rm -f *.o core $(EXE)

text :
	rm -f *.txt core $(EXE)

$(EXE) : % : %.o graph.o node.o
	$(CC) $(CFLAGS) -o $@ $@.o -lm -lpthread graph.o node.o types.h

node.o : node.c node.h
	$(CC) $(CFLAGS) -c $<

graph.o : graph.c graph.h
	$(CC) $(CFLAGS) -c $<
