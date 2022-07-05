#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"
//No compila
struct s_pqueue {
    unsigned int size;
    struct s_node* *array;
    priority_t min_priority;
};

struct s_node {
    pqueue_elem elem;
    struct s_node *next;
};

static struct s_node * create_node(pqueue_elem e) {
    struct s_node* new_node=NULL;
    new_node = malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->next = NULL;
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    assert(node != NULL);
    free(node);
    node=NULL;
    return node;
}


static bool invrep(pqueue q) {
    return (q != NULL);
}

pqueue pqueue_empty(priority_t min_priority) {
    pqueue q=NULL;
    q = malloc(sizeof(struct s_pqueue));
    q->array = malloc((min_priority+1)*sizeof(struct s_pqueue));
    for (unsigned int i=0; i<min_priority; i++){
        q->array[i] = NULL;
    }
    q->min_priority = min_priority+1;
    q->size = 0;
    assert(invrep(q) && pqueue_is_empty(q));
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, priority_t priority) {
    assert(invrep(q) && priority < q->min_priority);
    struct s_node *new_node = create_node(e);
    if (q->array[priority] == NULL){
        q->array[priority] = new_node;
    } else {
        struct s_node *p=q->array[priority];
        while (p->next != NULL){
            p = p->next;
        }
        p->next = new_node;
    }
    q->size++;
    assert(invrep(q) && !pqueue_is_empty(q));
    return q;
}

bool pqueue_is_empty(pqueue q) {
    assert(invrep(q));
    return (q->size == 0);
}

pqueue_elem pqueue_peek(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    pqueue_elem p;
    for (unsigned int i=0; i<q->min_priority; i++){
        if (q->array[i] != NULL){
            p = q->array[i]->elem;
            break;
        }
    }
    assert(invrep(q));
    return p;
}

priority_t pqueue_peek_priority(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    priority_t p;
    for (unsigned int i=0; i<q->min_priority; i++){
        if (q->array[i] != NULL){
            p = i;
            break;
        }
    }
    assert(invrep(q));
    return p;
}

size_t pqueue_size(pqueue q) {
    assert(invrep(q));
    return q->size;
}

pqueue pqueue_dequeue(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    struct s_node *kill;
    for (unsigned int i=0; i<q->min_priority; i++){
        if (q->array[i] != NULL){
            kill = q->array[i];
            q->array[i] = q->array[i]->next;
            kill = destroy_node(kill);
            q->size--;
            break;
        }
    }
    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q) {
    assert(invrep(q));
    for (unsigned int i=0; i<q->min_priority; i++){
        struct s_node *p = q->array[i];
        while (p != NULL){
            struct s_node *kill=p;
            p = p->next;
            kill = destroy_node(kill);
        }
    }
    free(q);
    q = NULL;
    return q;
}

