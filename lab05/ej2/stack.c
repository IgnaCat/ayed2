#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "stack.h"

struct _s_stack {
    stack_elem *elems;      // Arreglo de elementos
    unsigned int size;      // Cantidad de elementos en la pila
    unsigned int capacity;  // Capacidad actual del arreglo elems
};

stack stack_empty(){
    stack s = malloc(sizeof(struct _s_stack));
    s->size = 0;
    s->capacity = 0;
    s->elems = NULL;
    return s;
}

stack stack_push(stack s, stack_elem e){
    assert(s != NULL);
    assert(s->capacity >= s->size);
    size_t capacity;
    if (s->capacity == s->size) {
        capacity = s->capacity == 0 ? 1 : 2*s->capacity;
        s->elems = realloc(s->elems, capacity*sizeof(stack_elem));
        s->capacity = capacity;
    }
    s->elems[s->size] = e;
    (s->size)++;

    return s;
}

stack stack_pop(stack s){
    assert(s != NULL);
    --(s->size);
    return s;
}

unsigned int stack_size(stack s){
    assert(s != NULL);
    return s->size;
}

stack_elem stack_top(stack s){
    assert(s != NULL);
    assert(s->size > 0);
    assert(s->elems != NULL);
    return s->elems[(s->size)-1];
}

bool stack_is_empty(stack s){
    assert(s != NULL);
    return (s->size)== 0;
}

stack_elem *stack_to_array(stack s){
  assert(s != NULL);
  stack_elem *array = NULL;
  if(s->size) {
    array = calloc(s->size, sizeof(stack_elem));
    array = memcpy(array, s->elems, s->size*sizeof(stack_elem));
  }
  return array;
}

stack stack_destroy(stack s){
    assert(s != NULL);
    free(s->elems);
    free(s);
    return NULL;
}
