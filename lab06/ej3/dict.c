#include <assert.h>
#include <stdlib.h>
#include "dict.h"
#include "key_value.h"

struct _node_t {
    dict_t left;
    dict_t right;
    key_t key;
    value_t value;
};

key_t dict_max(dict_t d) {
    key_t max_e;
    assert(d != NULL);
    if (d->right == NULL){
        max_e = d->key;
    } else {
        max_e = dict_max(d->right);
    }  

    assert(dict_exists(d, max_e));
    return max_e;
}

key_t dict_min(dict_t d) {
    key_t min_e;
    assert(d != NULL);
    if (d->left == NULL){
        min_e = d->key;
    } else {
        min_e = dict_min(d->left);
    }  
    assert(dict_exists(d, min_e));
    return min_e;
}

static bool invrep(dict_t d) {
    return  (d == NULL) || 
            ((d->left == NULL || (key_less(dict_max(d->left), d->key) && invrep(d->left))) && 
             (d->right == NULL || (key_less(d->key, dict_min(d->right)) && invrep(d->right))));
}


dict_t dict_empty(void) {
    dict_t dict = NULL;
    assert(invrep(dict) && dict_length(dict) == 0);
    return dict;
}

dict_t dict_add(dict_t dict, key_t word, value_t def) {
    assert(invrep(dict));
    if (dict == NULL){
        struct _node_t *p = malloc(sizeof(struct _node_t));;
        p->key = word;
        p->value = def;
        p->left = NULL;
        p->right = NULL;
        dict = p;
    } else if (key_less(word,dict->key)){
        dict->left = dict_add(dict->left, word, def);
    } else if (key_less(dict->key, word)) {
        dict->right = dict_add(dict->right, word, def);
    }
    assert(invrep(dict) && dict_exists(dict, word));
    return dict;
}

value_t dict_search(dict_t dict, key_t word) {
    assert(invrep(dict));
    value_t def = NULL;
    while(dict != NULL && !key_eq(word, dict->key)) {
      if (key_less(word, dict->key)) {
        dict = dict->left;
      } else{
        dict = dict->right;
      }
    }
    if(dict != NULL){
      def = value_clone(dict->value);
    }
    assert((def != NULL) == dict_exists(dict, word));
    return def;
}

bool dict_exists(dict_t dict, key_t word) {
    bool exists=false;
    assert(invrep(dict));
    if (dict != NULL){
        if (dict->key == word){
            exists = true;
        } else {
            exists = dict_exists(dict->left,word) || dict_exists(dict->right,word);
        }
    }
    
    return exists;
}

unsigned int dict_length(dict_t dict) {
    unsigned int length=0;
    assert(invrep(dict));
    struct _node_t *p;
    p = dict;
    if (p != NULL){
        length = 1 + dict_length(p->left) + dict_length(p->right);
    }
    
    return length;
}

dict_t findMin(dict_t dict) {
    struct _node_t *p = dict;
    if (p == NULL) {
       return 0; // or undefined.
    }
    if (p->left != NULL) {
       return findMin(dict->left); // left tree is smaller
    }
    return p;
}

dict_t dict_remove(dict_t dict, key_t word) {
    assert(invrep(dict));
    if (dict != NULL){
        if (key_less(word, dict->key)) {  // node is in the left sub tree
            dict->left = dict_remove(dict->left, word);
        } else if (!key_less(word, dict->key) && !key_eq(word, dict->key)) { // node is in the right sub tree
            dict->right = dict_remove(dict->right, word);
        } else {
            if (dict->left == NULL && dict->right == NULL){ // has no children
                free(dict);
                dict = NULL;
            }
            else if (dict->left == NULL){ // child in right
                struct _node_t *temp=dict;
                dict = dict->right;
                free(temp);
            }
            else if (dict->right == NULL){ // child in left
                struct _node_t *temp=dict;
                dict = dict->left;
                free(temp);
            }
            else { // two children
                struct _node_t *temp = findMin(dict->right); // find minimal value of right sub tree
                dict->key = temp->key; // duplicate the node
                dict->right = dict_remove(dict->right, temp->key); // delete the duplicate node
            }
        }
    }
    assert(invrep(dict) && !dict_exists(dict, word));
    return dict;
}

dict_t dict_remove_all(dict_t dict) {
    assert(invrep(dict));
    if (dict != NULL) {
      dict_remove_all(dict->left);
      dict_remove_all(dict->right);
      key_destroy(dict->key);
      key_destroy(dict->value);
      free(dict);
      dict = NULL;
    }
    assert(invrep(dict) && dict_length(dict) == 0);
    return dict;
}

void dict_dump(dict_t dict, FILE *file) {
    assert(invrep(dict) && file != NULL);
    if (dict != NULL) {
        dict_dump(dict->left, file);
        key_dump(dict->key, file);
        fprintf(file, ": ");
        key_dump(dict->value, file);
        fprintf(file, "\n");
        dict_dump(dict->right, file);
    }
}

dict_t dict_destroy(dict_t dict) {
    assert(invrep(dict));
    return dict_remove_all(dict);
}

