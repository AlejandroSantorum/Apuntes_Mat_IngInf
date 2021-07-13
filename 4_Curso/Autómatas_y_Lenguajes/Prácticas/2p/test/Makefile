CC = gcc
CFLAGS = -g -ansi -Wall -pedantic -std=c99
# TESTS = stack_test mtx_test cstate_test translate_from_afnd
TESTS = test_del_states
LIBS = ../srclib

all: $(TESTS)

test_del_states: test_del_states.c $(LIBS)/afnd.o $(LIBS)/minimiza.o $(LIBS)/utils.o $(LIBS)/current_state.o $(LIBS)/stack.o $(LIBS)/linked_list.o
	$(CC) $(CFLAGS) $^ -o $@

# cstate_test: cstate_test.c $(LIBS)/current_state.o
# 	$(CC) $(CFLAGS) $^ -o $@ -lm
#
# stack_test: stack_test.c $(LIBS)/stack.o
# 	$(CC) $(CFLAGS) $^ -o $@ -lm
#
# mtx_test: mtx_test.c $(LIBS)/utils.o $(LIBS)/afnd.o
# 	$(CC) $(CFLAGS) $^ -o $@
#
# translate_from_afnd: translate_from_afnd.c $(LIBS)/utils.o $(LIBS)/afnd.o
# 	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf *.o $(TESTS)
