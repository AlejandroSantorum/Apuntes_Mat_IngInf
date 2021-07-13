/**
 * @brief Provides LinkedList data type.
 *
 * This file contains the needed functions to use a general linkedlist.
 * Node's data will not be copied so it just stores references to them.
 * The user is in charge of freeing up the memory which contains each node's data.
 *
 * @file linkedlist.h
 * @author Rafael Sánchez
 * @version 1.0
 * @date 11-02-2019
 */
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/** @defgroup linkedlist LinkedList module
*
* This module defines a general linked list and the needed functions to use it.
* Node's data will not be copied so it just stores references to them.
* The user is in charge of freeing up the memory which contains each node's data.
*/

/**
 * Struct that stores current node value and next node in the list.
 * @ingroup linkedlist
 */
struct lnode{
    void *val; /*!< Reference of node's data */
    struct lnode *next; /*!< Reference to next node in the list */
};

/**
 * Struct that defines the LinkedList type. Consists of a reference to the list
 * head.
 * @ingroup linkedlist
 */
typedef struct _likedlist{
    struct lnode *first; /*!< Reference to list's head */
} llist;


/**
 * Allocates memory for a new linked list
 *
 * @return pointer to linked list
 * @ingroup linkedlist
 */
llist *llist_new();

/**
 * Frees up the memory pointed to the parameter l
 *
 * @param l Linked list to free
 * @ingroup linkedlist
 */
void llist_delete(llist *l);

/**
 * Frees up the memory that is pointed with every element
 * of the linked list.
 *
 * @param l Linked list to destroy
 * @ingroup linkedlist
 */
void llist_destroy(llist *l);

/**
 * Return a pointer to the list's head.
 *
 * @param l Linked list to destroy
 *
 * @return pointer to element, NULL on error.
 * @ingroup linkedlist
 */
void *llist_head(llist *l);

/**
 * Adds a new lnode to the LinkedList containing a referece to elem as data.
 *
 * @param l Linked list to which the elem will be added
 * @param elem Element to add to the list
 *
 * @return 1 on success, 0 on error.
 * @ingroup linkedlist
 */
int llist_add(llist *l, void *elem);

/**
 * Returns a pointer to list's head memory and increase list head.
 *
 * @param l Linked list to pop head.
 *
 * @return pointer to element, NULL on error.
 * @ingroup linkedlist
 */
void *llist_pop(llist *l);

/**
 * Free internal lnode memory and gets it out of the list.
 *
 * @param l Linked list to work with
 * @param elem Value to find and delete
 * @param cmp_func Function used to compare values. Must return 0 if equal.
 * @return error code.
 * @ingroup linkedlist
 */
void *llist_del(llist *l, void *elem, int (*cmp_func) (void *, void *));

/**
 * Checks if elem is present in the list
 *
 * @param l Linked list to work with
 * @param elem Value to find
 * @param cmp_func Function used to compare values. Must return 0 if equal.
 * @return error code.
 * @ingroup linkedlist
 */
bool llist_in(llist *l, void *elem, int (*cmp_func) (void *, void *));

/**
 * Prints the linked list pointed by l, to file f, with function to_string which
 * give the representation of an element of the list as a string.
 *
 * @param f File which will contain the output.
 * @param l Linked list to work with
 * @param to_string Function used to transform an element to a string representation.
 * @return number of bytes written.
 * @ingroup linkedlist
 */
int llist_print(FILE *f, llist *l, char * (*to_string) (void *));
#endif
