#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"

struct s_pstack {
    unsigned int index;
    struct s_node *first;
};

struct s_node {
    pstack_elem elem;
    priority_t priority;
    struct s_node *next;
};

static struct s_node * create_node(pstack_elem e, priority_t priority) {
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


static bool invrep(pstack s) {
    bool b = (s != NULL);
    unsigned int size = 0;
    struct s_node *p=s->first;
    while (b && p != NULL){
         b = (p->next == NULL || p->priority >= p->next->priority);
         p = p->next;
         size++;
    }
    return b && (s->index == size);
}

pstack pstack_empty(void) {
    pstack s=NULL;
    s = malloc(sizeof(struct s_pstack));
    s->first = NULL;
    s->index = 0;
    assert(invrep(s) && pstack_is_empty(s));
    return s;
}

pstack pstack_push(pstack q, pstack_elem e, priority_t priority) {
    assert(invrep(q));
    struct s_node *new_node = create_node(e, priority);
    if (q->first == NULL){
        q->first = new_node;
    } else {
        struct s_node *right=q->first;
        struct s_node *left=NULL;
        while (right != NULL && right->priority > new_node->priority){
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
    assert(invrep(q) && !pstack_is_empty(q));
    return q;
}

bool pstack_is_empty(pstack s) {
    return (s->first == NULL);
}

pstack_elem pstack_top(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    return s->first->elem;
}

priority_t pstack_top_priority(pstack s) {
    assert(!pstack_is_empty(s));
    return s->first->priority;
}

unsigned int pstack_size(pstack s) {
    assert(invrep(s));
    return s->index;
}

pstack pstack_pop(pstack s) {
    assert(invrep(s));
    struct s_node *kill = s->first;
    s->first = s->first->next;
    kill = destroy_node(kill);
    s->index--;
    assert(invrep(s));
    return s;
}

pstack pstack_destroy(pstack s) {
    assert(invrep(s));
    struct s_node *p = s->first;
    while(s->first != NULL) {
      p = s->first;
      s->first = p->next;
      p = destroy_node(p);
    }
    free(s);
    s = NULL;
    assert(s == NULL);
    return s;
}

