CC = gcc
CFLAGS = -Wall
LDLIBS = -lodbc

EXE = create_table_file score suggest

all : $(EXE)

clean :
	rm -f *.o core $(EXE)

$(EXE) : % : %.o odbc.o type.o table.o
