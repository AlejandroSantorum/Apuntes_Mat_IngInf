CC = gcc
CFLAGS = -Wall -g
EXE = a3_e1_test

all : $(EXE)

.PHONY : clean text
clean :
	rm -f *.o core $(EXE)

text :
	rm -f *.txt core $(EXE)

$(EXE) : % : %.o queue.o node.o functions.o
	$(CC) $(CFLAGS) -o $@ $@.o -lm queue.o node.o functions.o
	
functions.o : functions.c functions.h
	$(CC) $(CFLAGS) -c $<

node.o : node.c node.h
	$(CC) $(CFLAGS) -c $<

queue.o : queue.c queue.h
	$(CC) $(CFLAGS) -c $<
