#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 1000

static void sort_phrase(unsigned int *indexes, char *letters, char *sorted, unsigned int length){
    for (unsigned int i=0u; i < length; i++) {
        for (unsigned int j=0u; j < length; j++) {
            if (indexes[j] == i){
                sorted[i] = letters[j];
            }
        }
    }
}

static void dump(char a[], unsigned int length) {
    for (unsigned int j=0u; j < length; j++) {      
        if (j == length-1){
            printf("%c \n", a[j]);
        } else {
            printf("%c", a[j]);
        }
    }
}

char *parse_filepath(int argc, char *argv[]) {
    char *result = NULL;

    if (argc < 2) {
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return result;
}

unsigned int data_from_file(const char *path, 
unsigned int indexes[], char letters[], unsigned int max_size){
    FILE *file = NULL;
    file = fopen(path, "r");
    if (file == NULL) {
        printf("File not exist.\n");
        exit(EXIT_FAILURE);
    }
    
    unsigned int i = 1;
    while(!feof(file)){
        fscanf(file, "%u  %*c %c %*c \n", &indexes[i], &letters[i]);
        i++;
    }
    if (i > max_size){
        i = max_size;
    }
    
    fclose(file);
    return i;

}

int main(int argc, char *argv[]) {
    char *filepath = NULL;
    filepath = parse_filepath(argc, argv);

    
    unsigned int indexes[MAX_SIZE];
    char letters[MAX_SIZE];
    
    unsigned int length=0; 
    //  .----------^
    //  :
    // Debe guardarse aqui la cantidad de elementos leidos del archivo
    
    length = data_from_file(filepath, indexes, letters, MAX_SIZE);
    char sorted[length];
    sort_phrase(indexes, letters, sorted, length);

    dump(sorted, length);

    return EXIT_SUCCESS;
}
