#include <stdio.h>
#include <stdlib.h>

size_t string_length(const char *str){
    size_t i = 0;
    while (str != NULL){
        if (str[i] != '\0'){
            i++;
        } else {
            break;
        }
    }
    
    return i;
}

char *string_filter(const char *str, char c){
    size_t i = 0, j=0;
    char str_aux[string_length(str)];
    char *str_filter;
    while (str != NULL){
        if (str[i] == '\0'){
            break;
        }
        if (str[i] != c){
            str_aux[j] = str[i];
            j++;
        }
        i++;
        
    }

    str_filter = malloc(j+1);
    for(unsigned int i=0; i<=string_length(str); i++) {
        str_filter[i] = str_aux[i];
    }
    return str_filter;
}