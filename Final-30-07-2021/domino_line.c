#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "domino_line.h"
#include "domino.h"

struct _s_line {
    domino tile;
    struct _s_line *next;
};

domino_line line_new(domino first) {
    domino_line line = NULL;
    line = malloc(sizeof(struct _s_line));
    line->tile = first;
    line->next = NULL;
    return line;
}

domino_line line_add(domino_line line, domino t) {
    assert(line != NULL);
    domino_line line_aux = line;
    domino_line add_line = NULL;
    add_line = malloc(sizeof(struct _s_line));
    add_line->tile = t;
    add_line->next = NULL;
    while (line_aux->next != NULL){
        line_aux = line_aux->next;
    }
    line_aux->next = add_line;
    return line;
}

unsigned int line_length(domino_line line) {
    assert(line != NULL);
    domino_line line_aux = line;
    unsigned int length = 0;
    while (line_aux != NULL){
        length++;
        line_aux = line_aux->next;
    }
    assert(length > 0);
    return length;
}

bool line_n_correct(domino_line line, unsigned int n) {
    assert( line != NULL && line_length(line) > n);
    domino_line line_aux = line;
    unsigned int i = 0;
    bool correct = false;
    if (n == 0){
        if (domino_matches(line_aux->tile, line_aux->next->tile)){
            correct = true;
        }
    } else if (n == line_length(line)-1){
        while (line_aux->next->next != NULL){
            i++;
            line_aux = line_aux->next;
        }
        if (domino_matches(line_aux->tile, line_aux->next->tile)){
            correct = true;
        }
    } else {
        while (line_aux != NULL && i != n-1){
            i++;
            line_aux = line_aux->next;
        }
        if (domino_matches(line_aux->tile, line_aux->next->tile) && 
            domino_matches(line_aux->next->tile, line_aux->next->next->tile)){
            correct = true;
        }
    } 
    
    return correct;
}

int line_total_points(domino_line line) {
    assert(line != NULL);
    domino_line line_aux = line;
    int sum=0;
    while (line_aux != NULL){
            sum = sum + domino_up(line_aux->tile) + domino_down(line_aux->tile);
            line_aux = line_aux->next;
    }

    return sum;
}

domino * line_to_array(domino_line line) {
    domino* a;
    domino_line line_aux = line;
    unsigned int n = line_length(line);
    a = calloc(n, sizeof(domino));
    int i = 0;
    while (line_aux != NULL){
        a[i] = line_aux->tile;
        line_aux = line_aux->next;
        i++;
    }

    return a;
}

void line_dump(domino_line line) {
    domino *array=line_to_array(line);
    for (unsigned int i=0u; i < line_length(line); i++) {
        domino_dump(array[i]);
    }
    free(array);
}

domino_line line_destroy(domino_line line) {
    assert(line != NULL);
    domino_line kill=NULL;
    while (line != NULL){
        kill = line;
        domino_destroy(line->tile); 
        line = line->next;
        free(kill);
        kill = NULL; 
    }
    return line;
}

