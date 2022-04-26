#include <stdbool.h>
#include <stdio.h>

#include "odd.h"

bool is_odd_sorted(int array[], unsigned int length) {
    // -- Completar --
    bool b = true;
    for (unsigned int i=1; i<length-2; i++){
        if (array[i] > array[i+2]){
            b = false;
        }
        i++;
    }
    return b;
}

int main() {

int array[4] = {6, 1};
printf("[6, 1]: %d \n", is_odd_sorted(array, 2));

int array1[5] = {5, 1, 8, 2, 3};
printf("[5, 1, 8, 2, 3]: %d \n", is_odd_sorted(array1, 5));

int array2[5] = {5, 5, 8, 2, 3};
printf("[5, 5, 8, 2, 3]: %d \n", is_odd_sorted(array2, 5));

int array3[6] = {5, 1, 8, 2, 3, 4};
printf("[5, 1, 8, 2, 3, 4]: %d \n", is_odd_sorted(array3, 6));

int array4[6] = {5, 1, 8, 2, 3,-1};
printf("[5, 1, 8, 2, 3,-1]: %d \n", is_odd_sorted(array4, 6));

return 0;
}
