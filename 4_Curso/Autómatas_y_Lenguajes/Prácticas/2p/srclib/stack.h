#ifndef STACK_H
#define STACK_H

typedef struct stack stack;

/* Returns an uninitialised stack pointer */
stack *stack_new();

/* Frees stack's pointer memory */
void stack_delete(stack *);

/* Initialise an uninitialised stack pointer */
stack *stack_init(stack *, size_t stack_size, size_t memb_size);

/* Free's the initialised memory in stack_init */
void stack_destroy(stack *);

/* Returns the top element of the stack or 0 if it fails*/
void stack_peek(stack *, void *dest);

/* Push the element to the stack, resizing if necessary. If it fails set errno to appropiate value*/
void stack_push(stack *, void *elem);

/* Pops the top element of the stack or 0 if it fails*/
void stack_pop(stack *, void *dest);

/* Get the number of elements in the stack*/
size_t stack_top(stack *s);

/* Prints the stack */
void stack_print(FILE *fout, stack *s, char *(*to_str)(void *, size_t));

#endif
