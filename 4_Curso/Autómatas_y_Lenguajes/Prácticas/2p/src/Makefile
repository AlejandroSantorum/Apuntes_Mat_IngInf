CC = gcc
CFLAGS = -g -ansi -Wall -pedantic -std=c99
EXE = main_de_ejemplo
LIBS = ../srclib

all : $(EXE)

.PHONY : clean
clean :
	rm -f *.o core $(EXE)

.PHONY : graph_afnd
graph_afnd :
	dot -Tpng afnd_ejemplo.dot > afnd_ejemplo.png

.PHONY : graph_afd
graph_afd :
	dot -Tpng determinista.dot > determinista.png

.PHONY : clean_dot
clean_dot :
	rm -f *.dot

.PHONY : clean_png
clean_png :
	rm -f *.png

main_de_ejemplo: $(LIBS)/afnd.o $(LIBS)/transforma.o $(LIBS)/minimiza.o  $(LIBS)/utils.o $(LIBS)/current_state.o $(LIBS)/stack.o $(LIBS)/linked_list.o
	$(CC) $(CFLAGS) $@.c $? -o $@
