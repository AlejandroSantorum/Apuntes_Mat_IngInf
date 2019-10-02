CC = gcc
CFLAGS = -Wall -g
EXE = a1_e1_test

all : $(EXE)

.PHONY : clean text
clean :
	rm -f *.o core $(EXE)

text :
	rm -f *.txt core $(EXE)

$(EXE) : % : %.o node.o
	$(CC) $(CFLAGS) -o $@ $@.o -lm -lpthread node.o types.h

node.o : node.c node.h
	$(CC) $(CFLAGS) -c $<
