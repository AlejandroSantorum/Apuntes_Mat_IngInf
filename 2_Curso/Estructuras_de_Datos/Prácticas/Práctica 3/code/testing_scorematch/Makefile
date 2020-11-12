#-----------------------
# IMPORTANTE: Los valores de los parametros de los ejercicio?_test deben ajustarse.
# Se asume que los ficheros fuente se llaman ejercicio1.c, ejercicio2.c,...,ordenar.h
#-----------------------

CC = gcc
CFLAGS = -Wall
EXE = scorematch

all : $(EXE)

.PHONY : clean
clean :
	rm -f *.o core $(EXE)

$(EXE) : % : %.o type.o table.o index.o
	$(CC) $(CFLAGS) -o $@ $@.o type.o table.o index.o

type.o : type.c type.h
	$(CC) $(CFLAGS) -c $<

table.o : table.c table.h
	$(CC) $(CFLAGS) -c $<
	
index.o : index.c index.h
	$(CC) $(CFLAGS) -c $<