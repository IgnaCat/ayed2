#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "string.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("mesi \n");
        exit(EXIT_FAILURE);
    }
    // printf("%s \n", argv[1]);
    // printf("%s \n", argv[2]);

    char *str1 = argv[1];
    char *str2 = argv[2];

    string string1 = string_create(str1);
    string string2 = string_create(str2);

    printf("%s", string_eq(string1, string2) ? "Iguales \n" : "No son iguales \n");
    printf("%s", string_less(string1, string2) ? "Str1 menor \n" : "Str2 menor \n");

    string_destroy(string1);
    string_destroy(string2);

    return (EXIT_SUCCESS);
}