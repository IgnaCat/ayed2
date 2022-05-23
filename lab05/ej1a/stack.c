#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "stack.h"

struct _s_stack {
  stack_elem elem;
  struct _s_stack *next;
};


stack stack_empty(){
    stack l = NULL;
    return l;
}
 
stack stack_push(stack s, stack_elem e){
    struct _s_stack *p;
    p = malloc(sizeof(struct _s_stack));
    p->elem = e;
    p->next = s;

    return p;
}

stack stack_pop(stack s){
    assert(s != NULL);
    struct _s_stack *p;
    p = s;
    s = s->next;
    free(p);

    return s;
}

unsigned int stack_size(stack s){
    struct _s_stack *p;
    unsigned int n = 0;
    if (!stack_is_empty(s)){
        p = s;
        while (p->next != NULL){
            p = p->next;
            n++;
        }
    }

    return n;
}

stack_elem stack_top(stack s){
    return s->elem;
}

bool stack_is_empty(stack s){
    return (s == NULL);
}

stack_elem *stack_to_array(stack s){
    stack_elem *a;
    struct _s_stack *p;
    unsigned int n = stack_size(s)+1;
    a = (int*)calloc(n, sizeof(stack_elem));

    if (!stack_is_empty(s)){
        p = s;
        for(unsigned int i = 0; i < n; i++) {
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
