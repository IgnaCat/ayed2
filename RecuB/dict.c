#include <assert.h>
#include <stdlib.h>
#include "dict.h"
#include "string.h"

struct _dict_t {
  unsigned int size;
  struct _node_t *words;
  struct _node_t *definitions;
};

struct _node_t {
  string elem;
  struct _node_t *next;
};

static bool invrep(dict_t d) {
  return (d==NULL || d!=NULL) ;
}

// returns the position of the word on the list of nodes (0 being the first node)
// returns -1 if the word is not on the dict
static int find_index_of_key(dict_t dict, string word) {
  int index = 0;
  while (dict != NULL && !string_eq(word, dict->words->elem)){
    dict->words = dict->words->next;
    index++;
  }

  return index;
}

dict_t dict_empty(void) {
    dict_t dict = NULL;
    dict = malloc(sizeof(struct _dict_t));
    dict->size = 0;
    dict->words = NULL;
    dict->definitions = NULL;
    assert(invrep(dict) && dict_length(dict) == 0);
    return dict;
}

static node_t create_node(string elem) {
    node_t new_node = NULL;
    new_node = malloc(sizeof(struct _node_t));
    new_node->elem = elem;
    new_node->next = NULL;
    return new_node;
}

static node_t destroy_node(node_t node) {
    assert(node != NULL);
    free(node);
    node = NULL;
    return node;

}

dict_t dict_add(dict_t dict, string word, string def) {
    assert(invrep(dict));
    node_t new_node_word = create_node(word);
    node_t new_node_def = create_node(def);
      node_t left_word = NULL;
      node_t right_word = dict->words;
      node_t left_def = NULL;
      node_t right_def = dict->definitions;
      while (right_word != NULL && string_less(new_node_word->elem, right_word->elem)){
        left_word = right_word;
        left_def = right_def;
        right_word = right_word->next;
        right_def = right_def->next;
      }
      if (left_word == NULL){
        dict->words = new_node_word;
        dict->definitions = new_node_def;
        new_node_word->next = right_word;
        new_node_def->next = right_def;
      } else {
        left_word->next = new_node_word;
        left_def->next = new_node_def;
        new_node_word->next = right_word;
        new_node_def->next = right_def;
      }
      dict->size++;
    assert(invrep(dict) && string_eq(def, dict_search(dict, word)));
    return dict;
}

string dict_search(dict_t dict, string word) {
  assert(invrep(dict));
  string def = NULL;
  while (dict != NULL && !string_eq(word, dict->words->elem)){
    dict->words = dict->words->next;
    dict->definitions = dict->definitions;
  }
  if(dict != NULL){
    def = string_clone(dict->definitions->elem);
  }
  assert((def != NULL) == dict_exists(dict, word));
  return def;
}

bool dict_exists(dict_t dict, string word) {
  bool exists=false;
  assert(invrep(dict));
  while (dict != NULL && !string_eq(word, dict->words->elem)){
    if (string_eq(word, dict->words->elem)){
      exists = true;
    }
    dict->words = dict->words->next;
  }
  assert(invrep(dict));
  return exists;
}

unsigned int dict_length(dict_t dict) {
  assert(invrep(dict));
  return dict->size;
}

// removes the "index" element of the "list" list of nodes
static node_t remove_on_index(node_t list, unsigned int index) {
    node_t kill = NULL;
    unsigned int index_node = 0;
    while (list != NULL && index+1 != index_node ){
      list = list->next;
      index_node++;
    }
    kill = list;
    list = list->next;
    free(kill);
    kill = NULL;

    return kill;
}

dict_t dict_remove(dict_t dict, string word) {
  assert(invrep(dict));
  int index = find_index_of_key(dict, word);
  if (index != -1) {
    dict->words = remove_on_index(dict->words, index);
    dict->definitions = remove_on_index(dict->definitions, index);
    dict->size--;
  }
  assert(invrep(dict));
  return dict;
}

dict_t dict_remove_all(dict_t dict) {
  assert(invrep(dict));
    while (dict->words != NULL) {
      node_t kill_word = dict->words;
      node_t kill_def = dict->definitions;
      string_destroy(dict->words->elem);
      string_destroy(dict->definitions->elem);
      dict->words = dict->words->next;
      dict->definitions = dict->definitions->next;
      kill_word = destroy_node(kill_word);
      kill_def = destroy_node(kill_def);
    }
    assert(invrep(dict) && dict_length(dict) == 0);
    return dict;
}

void dict_dump(dict_t dict, FILE *file) {
    /* tip: use fprintf(file, "%s : %s\n", string_ref(word), string_ref(def)); to save to file  */

    assert(invrep(dict) && file != NULL);
    while (dict->words != NULL) {
        string_dump(dict->words->elem, file);
        fprintf(file, ": ");
        string_dump(dict->definitions->elem, file);
        fprintf(file, "\n");
        dict->words = dict->words->next;
        dict->definitions = dict->definitions;
    }

}

dict_t dict_destroy(dict_t dict) {
  dict = dict_remove_all(dict);
  free(dict);
  dict = NULL;
  return dict;
}
