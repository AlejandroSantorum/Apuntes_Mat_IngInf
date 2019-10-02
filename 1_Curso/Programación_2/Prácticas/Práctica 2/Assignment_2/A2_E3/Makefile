CC = gcc
CFLAGS = -Wall -g
LIBS = -lm
EXE = a2_e3_test

all : $(EXE)

.PHONY : clean text
clean :
	rm -f *.o core $(EXE)

text :
	rm -f *.txt core $(EXE)

$(EXE) : % : %.o stack_element.o element_int.o graph.o node.o
	$(CC) $(CFLAGS) $(LIBS) -o $@ $@.o stack_element.o element_int.o graph.o node.o

element_int.o : element_int.c element_int.h
	$(CC) $(CFLAGS) -c $<

stack_element.o : stack_element.c stack_element.h
	$(CC) $(CFLAGS) -c $<

graph.o : graph.c graph.h
	$(CC) $(CFLAGS) -c $<

node.o : node.c node.h
	$(CC) $(CFLAGS) -c $<
