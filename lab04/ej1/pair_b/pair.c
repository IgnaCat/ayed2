#include <stdlib.h>
#include <stdio.h>
#include "pair.h"

pair_t pair_new(int x, int y){
    pair_t p;
    p = malloc(sizeof(struct s_pair_t));
    p->fst = x;
    p->snd = y;
    return p;
}

int pair_first(pair_t p){
    return p->fst;
}

int pair_second(pair_t p){
    return p->snd;
}

pair_t pair_swapped(pair_t p){
    pair_t pair;
    pair = malloc(sizeof(struct s_pair_t));
    pair->fst = p->snd;
    pair->snd = p->fst;
    return pair;
}

pair_t pair_destroy(pair_t p){
    free(p);
    return p;
}