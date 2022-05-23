#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "stack.h"

struct _s_stack {
  stack_elem elem;
  struct _s_stack *next;
  unsigned int index;
};


stack stack_empty(){
    stack l = NULL;
    return l;
}
 
stack stack_push(stack s, stack_elem e){
    struct _s_stack *q;
    q = malloc(sizeof(struct _s_stack));
    q->elem = e;
    q->next = s;
    q->index = s == NULL ? 0 : (s->index) + 1;

    return q;
}

stack stack_pop(stack s){
    assert(s != NULL);
    struct _s_stack *p;
    p = s;
    s = (s->next);
    free(p);

    return s;
}

unsigned int stack_size(stack s){
    return s == NULL ? 0 : (s->index) + 1;
}

stack_elem stack_top(stack s){
    assert(s != NULL);
    return s->elem;
}

bool stack_is_empty(stack s){
    return (s == NULL);
}

stack_elem *stack_to_array(stack s){
    stack_elem *a;
    struct _s_stack *p;
    unsigned int n = stack_size(s);
    a = (int*)calloc(n, sizeof(stack_elem));

    if (!stack_is_empty(s)){
        p = s;
        for(int i = stack_size(s)-1; 0<=i; --i) {
            a[i] = p->elem;
            p = p->next;
        }
    } else {
        a = NULL;
    }

    return a;
}

stack stack_destroy(stack s) {
  struct _s_stack *p;
  
  while(s != NULL) {
    p = s;
    s = s->next;
    free(p);
  }

  return s;
}
