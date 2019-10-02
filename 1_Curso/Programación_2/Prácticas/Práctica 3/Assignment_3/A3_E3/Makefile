CC = gcc
CFLAGS = -Wall -g
EXE = a3_e3_test

all : $(EXE)

.PHONY : clean text
clean :
	rm -f *.o core $(EXE)

text :
	rm -f *.txt core $(EXE)

$(EXE) : % : %.o list.o functions.o
	$(CC) $(CFLAGS) -o $@ $@.o -lm list.o functions.o
	
functions.o : functions.c functions.h
	$(CC) $(CFLAGS) -c $<

list.o : list.c list.h
	$(CC) $(CFLAGS) -c $<
