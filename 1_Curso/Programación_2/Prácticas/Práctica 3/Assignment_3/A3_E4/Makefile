CC = gcc
CFLAGS = -Wall -g
EXE = a3_e4_test

all : $(EXE)

.PHONY : clean text
clean :
	rm -f *.o core $(EXE)

text :
	rm -f *.txt core $(EXE)

$(EXE) : % : %.o graph_list.o list.o functions.o node.o
	$(CC) $(CFLAGS) -o $@ $@.o -lm graph_list.o list.o functions.o node.o
	
functions.o : functions.c functions.h
	$(CC) $(CFLAGS) -c $<

list.o : list.c list.h
	$(CC) $(CFLAGS) -c $<
	
node.o : node.c node.h
	$(CC) $(CFLAGS) -c $<
	
graph_list.o : graph_list.c graph_list.h
	$(CC) $(CFLAGS) -c $<
