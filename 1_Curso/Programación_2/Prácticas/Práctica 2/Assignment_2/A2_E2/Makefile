CC = gcc
CFLAGS = -Wall -g
EXE = a2_e2_test

all : $(EXE)

.PHONY : clean text
clean :
	rm -f *.o core $(EXE)

text :
	rm -f *.txt core $(EXE)

$(EXE) : % : %.o stack_element.o element_node.o graph.o node.o
	$(CC) $(CFLAGS) -o $@ $@.o -lm stack_element.o element_node.o graph.o node.o types.h

element_node.o : element_node.c element_node.h
	$(CC) $(CFLAGS) -c $<

stack_element.o : stack_element.c stack_element.h
	$(CC) $(CFLAGS) -c $<

graph.o : graph.c graph.h
	$(CC) $(CFLAGS) -c $<

node.o : node.c node.h
	$(CC) $(CFLAGS) -c $<
