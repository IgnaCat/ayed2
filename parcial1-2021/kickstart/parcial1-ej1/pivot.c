#include <stdbool.h>
#include <stdio.h>

#include "pivot.h"
//gcc -Wall -Werror -Wextra -pedantic -std=c99 -c helpers.c sort.c main.c
//gcc -Wall -Werror -Wextra -pedantic -std=c99 helpers.o sort.o main.o -o mysort
//./mysort ../input/atp-players2022.in

// {PRE: 0 <= piv < length}
bool is_pivot(int array[], unsigned int length, unsigned int piv) {
    // -- Completar --
    bool b = true;
    for (unsigned int i=0; i<piv; i++){
        if (array[i] > array[piv]){
            b = false;
        }
    }
    for (unsigned int i=piv+1; i<length; i++){
        if (array[piv] >= array[i]){
            b = false;
        }
    };
    return b;
}

int main() {

int array[4] = {1, 2, 6, 5};
printf("[1, 2, 6, 5], 1: %d \n", is_pivot(array, 4, 1));

printf("[1, 2, 6, 5], 0: %d \n", is_pivot(array, 4, 0));

printf("[1, 2, 6, 5], 2: %d \n", is_pivot(array, 4, 2));

int array1[4] = {1, 1, 6, 5};
printf("[1, 1, 6, 5], 1: %d \n", is_pivot(array1, 4, 1));

int array2[4] = {1, 1, 1, 5};
printf("[1, 1, 1, 5], 1: %d \n", is_pivot(array2, 4, 1));

return 0;
}