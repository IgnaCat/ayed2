
#include <stdio.h>    /* printf(), scanf() */
#include <stdbool.h>  /* tipo bool         */

#include <assert.h>   /* assert() */

#define ARRAY_SIZE 10

// gcc -o name -Wall -Wextra -Werror -ansi -pedantic -std=c99 name

struct max_min_result {
    int max_value;
    int min_value;
    unsigned int max_position;
    unsigned int min_position;
};

struct max_min_result compute_max_min(int array[], unsigned int length)
{   
    assert(length > 0);
    array = array;
    struct max_min_result result = { array[0], array[0], 0, 0 };

    for (unsigned int i=0; i<length-1; i++){                
        if (result.max_value < array[i+1]){
            result.max_value = array[i+1];
            result.max_position = i+1;
        }
        if (result.min_value > array[i+1]){
            result.min_value = array[i+1];
            result.min_position = i+1;
        }       
    }

    return result;
}

int main(void)
{
    int array[ARRAY_SIZE] = { 4, -1, 5, 8, 9, 0, 3, 6, 0, 0 };

    int elem;
    for (int i = 0; i < 10; i++){
        printf("Ingrese la posicion %d del arreglo ", i);
        scanf("%d", &elem);
        array[i] = elem;
    }

    struct max_min_result result = compute_max_min(array, ARRAY_SIZE);
    printf("Máximo: %d\n", result.max_value);
    printf("Posición del máximo: %u\n", result.max_position);
    printf("Mínimo: %d\n", result.min_value);
    printf("Posición del mínimo: %u\n", result.min_position);
    return 0;
}