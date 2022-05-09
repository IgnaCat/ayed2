#ifndef _LIST_H
#define _LIST_H

#include <stdbool.h>

/* list as a pointer to structs to guarantee encapsulation */
typedef struct s_node_t * list;
typedef int list_elem;


/* Constructors */
list empty(void);
/*
    Create empty list.
*/

list addl(list l, list_elem e);
/*
    Add the element e to the beginning a of list l.
*/


/* Operations */
bool is_empty(list l);
/*
    Return True if l is empty.
*/

list_elem head(list l);
/*
    Return the first element of a list.
    PRE: !is_empty(l)
*/

list tail(list l);
/*
    Delete the first element of a list.
    PRE: !is_empty(l)
*/

list addr(list l, list_elem e);
/*
    Add the element e to the end of a list l.
*/

unsigned int length(list l);
/*
    Return the size of the list.
*/

list concat(list l, list l0);
/*
    Add to the end of l all the elements of l0 in the same order.
*/

list_elem index(list l, unsigned int n);
/*
    Returns the nth element of the list l
    PRE: length(l) > n
*/

list take(list l, unsigned int n);
/*
    Leave in l only the first n elements, removing the rest.
*/

list drop(list l, unsigned int n);
/*
    Delete the first n elements of the list.
*/

list copy_list(list l);
/*
    Copy all the elements of l into the new list
*/


void list_destroy(list l);
/*
   Frees memory for l.
*/

#endif
