#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 20

int main(void) {
    char user_input[MAX_LENGTH];
    char aux_user_input[MAX_LENGTH-1];

    printf("Ingrese su nombre y apellido: ");
    //scanf("%s", user_input);

    //printf("Te damos la bienvenida %s a este maravilloso programa!\n", user_input);

    fgets(user_input, MAX_LENGTH, stdin);
    unsigned int j = 0;
    for (unsigned int i=0; i<MAX_LENGTH-2; i++){
        if (user_input[i] != '\n'){
            aux_user_input[j] = user_input[i];
            j++;
        }
    }

    printf("Te damos la bienvenida %s a este maravilloso programa!\n", aux_user_input);


    return EXIT_SUCCESS;
}

