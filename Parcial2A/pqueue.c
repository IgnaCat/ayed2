#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue {
    unsigned int index;
    struct s_node *first;
};

struct s_node {
    pqueue_elem elem;
    unsigned int priority;
    struct s_node *next;
};

static struct s_node * create_node(pqueue_elem e, unsigned int priority) {
    struct s_node *new_node = NULL;
    new_node = malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->priority = priority;
    new_node->next = NULL;
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    assert(node != NULL);
    free(node);
    node=NULL;
    assert(node == NULL);
    return node;
}


static bool invrep(pqueue q) {
    bool b = (q != NULL);
    unsigned int size = 0;
    struct s_node *p=q->first;
    while (b && p != NULL){
         b = (p->next == NULL || p->priority <= p->next->priority);
         p = p->next;
         size++;
    }
    return b && (q->index == size);
}

pqueue pqueue_empty(void) {
    pqueue q=NULL;
    q = malloc(sizeof(struct s_pqueue));
    q->first = NULL;
    q->index = 0;
    assert(invrep(q) && pqueue_is_empty(q));
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, unsigned int priority) {
    assert(invrep(q));
    struct s_node *new_node = create_node(e, priority);
    if (q->first == NULL){
        q->first = new_node;
    } else {
        struct s_node *right=q->first;
        struct s_node *left=NULL;
        while (right != NULL && right->priority <= new_node->priority){
            left = right;
            right = right->next;
        }
        if (left == NULL){
            new_node->next = right;
            q->first = new_node;
        } else {
            left->next = new_node;
            new_node->next = right;
        }
    }
    q->index++;
    assert(invrep(q) && !pqueue_is_empty(q));
    return q;
}

bool pqueue_is_empty(pqueue q) {
    return (q->first == NULL);
}

pqueue_elem pqueue_peek(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    pqueue_elem p=q->first->elem;
    assert(invrep(q));
    return p;
}

unsigned int pqueue_peek_priority(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    unsigned int p=q->first->priority;
    assert(invrep(q));
    return p;
}

unsigned int pqueue_size(pqueue q) {
    assert(invrep(q));
    return q->index;
}

pqueue pqueue_dequeue(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    struct s_node *kill=q->first;
    q->first = q->first->next;
    kill = destroy_node(kill);
    if (q->first == NULL){
        q->index = 0;
    } else {
        (q->index)--;
    } 
    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q) {
    assert(invrep(q));
    struct s_node *p=q->first;
    while (p != NULL){
        struct s_node *kill=p;
        p = p->next;
        kill = destroy_node(kill);
    }
    free(q);
    q = NULL;
    assert(q == NULL);
    return q;
}
