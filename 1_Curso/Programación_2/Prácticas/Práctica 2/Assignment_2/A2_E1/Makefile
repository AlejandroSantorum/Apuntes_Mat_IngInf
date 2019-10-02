CC = gcc
CFLAGS = -Wall -g
EXE = a2_e1_test

all : $(EXE)

.PHONY : clean text
clean :
	rm -f *.o core $(EXE)

text :
	rm -f *.txt core $(EXE)

$(EXE) : % : %.o stack_element.o element_int.o
	$(CC) $(CFLAGS) -o $@ $@.o -lm stack_element.o element_int.o types.h

element_int.o : element_int.c element_int.h
	$(CC) $(CFLAGS) -c $<

stack_element.o : stack_element.c stack_element.h
	$(CC) $(CFLAGS) -c $<
