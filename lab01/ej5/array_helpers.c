#include <assert.h>
#include "mybool.h"
#include <stdio.h>
#include <stdlib.h>

unsigned int array_from_file(int array[],
           unsigned int max_size,
           const char *filepath) {

    unsigned int length;

    FILE *fp;
    fp = fopen(filepath,"r");

    if (fp == NULL){
       printf("No such file \n");
       return 0;
    }
    fscanf(fp, "%u" , &length);
    printf("%u \n", length); 

    if(max_size < length){
        length = max_size;
    }

    for (unsigned int i = 0; i < length; i++){
        fscanf(fp, "%d", &array[i]);
    }
    
   fclose(fp);
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

mybool array_is_sorted(int a[], unsigned int length){
    if (length == 0){
        return true;
    }
    mybool res = true;
    for (unsigned int i=0; i < length-1; i++){
        if (a[i] > a[i+1]){
            res = false;
            i = length;
        }
    }
    return res;
}