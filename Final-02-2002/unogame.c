#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "unogame.h"
#include "card.h"

#define NO_PLAYER -1

struct s_ugame {
    card_t card;
    player_t player;
    struct s_ugame *next;   
};

unogame_t
uno_newgame(card_t card) {
    unogame_t uno=NULL;
    uno = malloc(sizeof(struct s_ugame));
    uno->card = card;
    uno->player = NO_PLAYER;
    uno->next = NULL;
    return uno;
}

card_t
uno_topcard(unogame_t uno) {
    assert(uno != NULL);
    return uno->card;
}

unogame_t
uno_addcard(unogame_t uno, card_t c) {
    unogame_t aux;
    aux = malloc(sizeof(struct s_ugame));
    aux->next = uno;
    aux->card = c;
    aux->player = uno_nextplayer(uno);

    return aux;
}

unsigned int
uno_count(unogame_t uno) {
    unsigned int size=0;
    unogame_t uno_aux=uno;
    while (uno_aux != NULL){
        uno_aux = uno_aux->next;
        size++;
    }
    return size;
}

bool
uno_validpile(unogame_t uno) {
    bool valid = true;
    unogame_t uno_aux=uno;
    while (uno_aux->next != NULL){
        if (!card_compatible(uno_aux->card, uno_aux->next->card)){
            valid = valid && false;
        }
        uno_aux = uno_aux->next;
    }
    if (card_get_type(uno_aux->card) == change_color){
        valid = false;
    }

    return valid;
}

color_t
uno_currentcolor(unogame_t uno) {
    return card_get_color(uno->card);
}

player_t
uno_nextplayer(unogame_t uno) {
    player_t player=uno->player;
    if (card_get_type(uno->card) == skip){
        if (uno->player == NO_PLAYER || uno->player == NUM_PLAYERS-1){
            player = 1;
        } else if (uno->player == NUM_PLAYERS-2){
            player = 0;
        } else {
            player = player + 2;
        }
    } else {
      if (uno->player == NO_PLAYER || uno->player == NUM_PLAYERS-1){
        player = 0;
      } else {
        player++;
      }
    }
    return player;
}



card_t *
uno_pile_to_array(unogame_t uno) {
    card_t* a;
    unsigned int n = uno_count(uno);
    a = calloc(n, sizeof(card_t));

    if (uno != NULL){
        for(int i = uno_count(uno)-1; 0<=i; --i) {
            a[i] = uno->card;
            uno = uno->next;
        }
    } else {
        a = NULL;
    }

    return a;
}

unogame_t
uno_destroy(unogame_t uno) {
  unogame_t kill;
  unogame_t uno_aux=uno;
  
  while(uno_aux != NULL) {
    kill = uno_aux;
    uno_aux = uno_aux->next;
    card_destroy(kill->card);
    free(kill);
    kill = NULL;
  }
  return uno;
}

