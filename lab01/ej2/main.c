/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Maximum allowed length of the array */
#define MAX_SIZE 100000

unsigned int array_from_input(int array[],
           unsigned int max_size) {

    unsigned int length;
    printf("Ingresar el length \n");
    scanf("%u", &length);

    if(max_size < length){
        length = max_size;
    }

    for (unsigned int i=0; i < length; i++){
        printf("Ingresar la posicion %u del arreglo \n", i);
        scanf("%d", &array[i]);
    }

    return(length);
}

void array_dump(int a[], unsigned int length) {
    printf("[");
    for (unsigned int i = 0; i < length; i++){
        if (i == length-1){
            printf("%d", a[i]);
        }
        else{
            printf("%d,", a[i]);
        }      
    }
    printf("] \n");
}


int main() {  
    int array[MAX_SIZE];

    unsigned int length = array_from_input(array, MAX_SIZE);  
    array_dump(array, length);
    
    return EXIT_SUCCESS;
}
