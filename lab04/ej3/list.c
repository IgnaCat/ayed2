#include <stdbool.h>
#include <stdlib.h>
#include "assert.h"
#include "list.h"

struct s_node_t {
  list_elem elem;
  struct s_node_t *next;
};

list empty(void){
    list l = NULL;
    return l;
}

list addl(list l, list_elem e){
    struct s_node_t *p;
    p = malloc(sizeof(struct s_node_t));
    p->elem = e;
    p->next = l;
    l = p;

    return l;
}

bool is_empty(list l){
    return (l == NULL);
}

list_elem head(list l){
    assert(!is_empty(l));
    return l->elem;
}

list tail(list l){
    assert(!is_empty(l));
    struct s_node_t *p;
    p = l;
    l = l->next;
    free(p);

    return l;
}

list addr(list l, list_elem e){
    struct s_node_t *p;
    struct s_node_t *q;
    q = malloc(sizeof(struct s_node_t));
    q->elem = e;
    q->next = NULL;

    if (!is_empty(l)){
        p = l;
        while (p->next != NULL){
            p = p->next;
        }
        p->next = q;
    }else{
        l = q;
    }

    return l;
}

unsigned int length(list l){
    struct s_node_t *p;
    unsigned int n = 0;
    p = l;
    while (p->next != NULL){
        p = p->next;
        n = n + 1;
    }
    
    return n;
}

list concat(list l, list l0){
    struct s_node_t *p;
    p = l;
    while (p->next != NULL){
        p = p->next;
    }    
    p = l0;

    return l;
}

list_elem index(list l, unsigned int n){
    assert(length(l) > n);
    struct s_node_t *p;
    unsigned int i = 0u;
    p = l;
    while (i<n && l!=NULL){
        p = p->next;
        i = i+1;
    }

    return p->elem;   
}

list take(list l, unsigned int n){
    assert(length(l) > n);
    struct s_node_t *p;
    p = l;
    unsigned int i = 0u;
    while(i<n) {
        p = p->next;
        i++;
    }
    free(p->next);

    return l;
}

list drop(list l, unsigned int n) {
    assert(length(l) > n);
    struct s_node_t *p;
    p = l;
    while(n>0) {
        p = p->next;
        n--;
    }

    return l;
}

void list_destroy(list l) {
    struct s_node_t *p;
    struct s_node_t *q;
    if (!is_empty(l)){
        p = l;
        q = p->next;
        while (p->next != NULL){
            free(p);
            p = q;
            q = p->next;
        }
    }
}