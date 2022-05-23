#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main(){
    stack s1 = stack_empty();
    stack_elem e = 7;
    stack_push(s1, e);
    s1 = stack_pop(s1);
    int *a = stack_to_array(s1);
    printf("%ls \n",a);

    int array[10] = {1,2,3,4};
    stack s2 = stack_empty();
    for (unsigned int i=0; i<4; i++){
      s2 = stack_push(s2, array[i]);
    }
    stack_elem *a1 = stack_to_array(s2);
    printf("%d \n",a1[0]);


    return (EXIT_SUCCESS);
}