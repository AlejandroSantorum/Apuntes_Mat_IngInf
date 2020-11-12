CC = gcc -ansi -pedantic -std=gnu99
CFLAGS = -Wall -g
EXE = ejercicio4a ejercicio4b ejercicio5a ejercicio5b ejercicio6 ejercicio8_1 ejercicio8_2 ejercicio9 ejercicio12a ejercicio12b ejercicio13

all : $(EXE)

.PHONY : clean
clean :
	rm -f *.o core $(EXE)

$(EXE) : % : %.o
	$(CC) $(CFLAGS) -o $@ $@.o -lm -lpthread
