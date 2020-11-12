CC = gcc
CFLAGS = -Wall -g
EXE = ejercicio2 ejercicio2_solved ejercicio3 ejercicio4 ejercicio5

all : $(EXE)

.PHONY : clean text
clean :
	rm -f *.o core $(EXE)

text :
	rm -f *.txt core $(EXE)

$(EXE) : % : %.o semaforos.o
	$(CC) $(CFLAGS) -o $@ $@.o -lm -lpthread semaforos.o

semaforos.o : semaforos.c semaforos.h
	$(CC) $(CFLAGS) -c $<
