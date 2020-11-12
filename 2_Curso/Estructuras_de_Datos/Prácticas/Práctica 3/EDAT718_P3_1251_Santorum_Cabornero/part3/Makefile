CC = gcc
CFLAGS = -Wall
LDLIBS = -lodbc

EXE = create_files score suggest scorematch

all : $(EXE)

clean :
	rm -f *.o core $(EXE)

$(EXE) : % : %.o odbc.o type.o table.o index.o
