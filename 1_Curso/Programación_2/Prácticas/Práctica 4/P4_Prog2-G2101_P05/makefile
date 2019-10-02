########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic -ansi
EJS = p4_e1 p4_e2 p4_e2_bal p4_e3 p4_e4
########################################################
## list.o se necesita si se tiene implementado el opcional en P4_E3
OBJECTSP4_E1 = p4_e1.o tree1.o functions1.o
OBJECTSP4_E2 = p4_e2.o tree2.o list2.o functions2.o node2.o
OBJECTSP4_E3 = p4_e3.o tree3.o list3.o functions3.o
OBJECTSP4_E4 = p4_e4.o tree4.o functions4.o
########################################################

all: $(EJS) clear

p4_e1: $(OBJECTSP4_E1)
	$(CC) $(CFLAGS) -o p4_e1 $(OBJECTSP4_E1)

p4_e2: $(OBJECTSP4_E2)
	$(CC) $(CFLAGS) -o p4_e2 $(OBJECTSP4_E2)

p4_e2_bal: $(OBJECTSP4_E2)
	$(CC) $(CFLAGS) -o p4_e2_bal $(OBJECTSP4_E2)
	
p4_e3: $(OBJECTSP4_E3)
	$(CC) $(CFLAGS) -o p4_e3 $(OBJECTSP4_E3)
	
p4_e4: $(OBJECTSP4_E4)
	$(CC) $(CFLAGS) -o p4_e4 $(OBJECTSP4_E4)

p4_e1.o: p4_e1.c tree1.h functions1.h
	$(CC) $(CFLAGS) -c p4_e1.c
	
p4_e2.o: p4_e2.c tree2.h list2.h functions2.h
	$(CC) $(CFLAGS) -c p4_e2.c

p4_e3.o: p4_e3.c tree3.h list3.h functions3.h
	$(CC) $(CFLAGS) -c p4_e3.c

p4_e4.o: p4_e4.c tree4.h functions4.h
	$(CC) $(CFLAGS) -c p4_e4.c

tree1.o: tree1.c tree1.h
	$(CC) $(CFLAGS) -c tree1.c

functions1.o: functions1.c functions1.h
	$(CC) $(CFLAGS) -c functions1.c

functions2.o: functions2.c functions2.h
	$(CC) $(CFLAGS) -c functions2.c

list2.o: list2.c list2.h
	$(CC) $(CFLAGS) -c list2.c

tree2.o: tree2.c tree2.h
	$(CC) $(CFLAGS) -c tree2.c

node2.o: node2.c node2.h
	$(CC) $(CFLAGS) -c node2.c

tree3.o: tree3.c tree3.h
	$(CC) $(CFLAGS) -c tree3.c
	
list3.o: list3.c list3.h
	$(CC) $(CFLAGS) -c list3.c

functions3.o: functions3.c functions3.h
	$(CC) $(CFLAGS) -c functions3.c	

tree4.o: tree4.c tree4.h
	$(CC) $(CFLAGS) -c tree4.c

functions4.o: functions4.c functions4.h
	$(CC) $(CFLAGS) -c functions4.c

clear:
	rm -rf *.o 

clean:
	rm -rf *.o $(EJS)

run:
	@echo ">>>>>>Running p4_e1"
	./p4_e1
	@echo ">>>>>>Running p4_e2"
	./p4_e2
	@echo ">>>>>>Running p4_e2_bal"
	./p4_e2_bal
	@echo ">>>>>>Running p4_e3"
	./p4_e3
	@echo ">>>>>>Running p4_e4"
	./p4_e4

runv:
	@echo ">>>>>>Running p4_e1 with valgrind"
	valgrind --leak-check=full ./p4_e1
	@echo ">>>>>>Running p4_e2 with valgrind"
	valgrind --leak-check=full ./p4_e2
	@echo ">>>>>>Running p4_e2_bal with valgrind"
	valgrind --leak-check=full ./p4_e2_bal
	@echo ">>>>>>Running p4_e3 with valgrind"
	valgrind --leak-check=full ./p4_e3
	@echo ">>>>>>Running p4_e4 with valgrind"
	valgrind --leak-check=full ./p4_e4
