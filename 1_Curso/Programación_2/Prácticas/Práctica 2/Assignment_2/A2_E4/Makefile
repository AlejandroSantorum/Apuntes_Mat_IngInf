CC = gcc
CFLAGS = -Wall -g
LIBS = -lm
EXE = a2_e4_test

all : $(EXE)

.PHONY : clean text
clean :
	rm -f *.o core $(EXE)

text :
	rm -f *.txt core $(EXE)

$(EXE) : % : %.o stack_fp.o functions.o graph.o node.o
	$(CC) $(CFLAGS) $(LIBS) -o $@ $@.o stack_fp.o functions.o graph.o node.o types.h

functions.o : functions.c functions.h
	$(CC) $(CFLAGS) -c $<

stack_fp.o : stack_fp.c stack_fp.h
	$(CC) $(CFLAGS) -c $<

graph.o : graph.c graph.h
	$(CC) $(CFLAGS) -c $<

node.o : node.c node.h
	$(CC) $(CFLAGS) -c $<
