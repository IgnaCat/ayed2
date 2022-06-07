#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "abb.h"

struct _s_abb {
    abb_elem elem;
    struct _s_abb *left;
    struct _s_abb *right;
};

static bool elem_less(abb_elem a, abb_elem b) {
    return a < b;
}

static bool invrep(abb tree) {
    return  (tree == NULL) || 
            ((tree->left == NULL || (elem_less(abb_max(tree->left), tree->elem) && invrep(tree->left))) &&
            (tree->right == NULL || (elem_less(tree->elem, abb_min(tree->right)) && invrep(tree->right))));
}

abb abb_empty(void) {
    abb tree = NULL;
    assert(invrep(tree) && abb_is_empty(tree));
    return tree;
}

abb abb_add(abb tree, abb_elem e) {
    assert(invrep(tree));
    if (tree == NULL){
        struct _s_abb *p = malloc(sizeof(struct _s_abb));;
        p->elem = e;
        p->left = NULL;
        p->right = NULL;
        tree = p;
    } else if (elem_less(e,tree->elem)){
        tree->left = abb_add(tree->left, e);
    } else if (elem_less(tree->elem, e)) {
        tree->right = abb_add(tree->right, e);
    }
    assert(invrep(tree) && abb_exists(tree, e));
    return tree;
}

bool abb_is_empty(abb tree) {
    bool is_empty=(tree == NULL);
    assert(invrep(tree));
    return is_empty;
}

bool abb_exists(abb tree, abb_elem e) {
    bool exists=false;
    assert(invrep(tree));
    struct _s_abb *p=tree;
    if (p != NULL){
        if (p->elem == e){
            exists = true;
        } else {
            exists = abb_exists(p->left,e) || abb_exists(p->right,e);
        }
    }
    
    return exists;
}

unsigned int abb_length(abb tree) {
    unsigned int length=0;
    assert(invrep(tree));
    struct _s_abb *p;
    p = tree;
    if (p != NULL){
        length = 1 + abb_length(p->left) + abb_length(p->right);
    }
    
    assert(invrep(tree) && (abb_is_empty(tree) || length > 0));
    return length;
}

abb findMin(abb tree) {
    struct _s_abb *p = tree;
    if (p == NULL) {
       return 0; // or undefined.
    }
    if (p->left != NULL) {
       return findMin(tree->left); // left tree is smaller
    }
    return p;
}

abb abb_remove(abb tree, abb_elem e) {
    assert(invrep(tree));
    if (tree != NULL){
        if (e < tree->elem) {  // node is in the left sub tree
            tree->left = abb_remove(tree->left, e);
        } else if (e > tree->elem) { // node is in the right sub tree
            tree->right = abb_remove(tree->right, e);
        } else {
            if (tree->left == NULL && tree->right == NULL){ // has no children
                free(tree);
                tree = NULL;
            }
            else if (tree->left == NULL){ // child in right
                struct _s_abb *temp=tree;
                tree = tree->right;
                free(temp);
            }
            else if (tree->right == NULL){ // child in left
                struct _s_abb *temp=tree;
                tree = tree->left;
                free(temp);
            }
            else { // two children
                struct _s_abb *temp = findMin(tree->right); // find minimal value of right sub tree
                tree->elem = temp->elem; // duplicate the node
                tree->right = abb_remove(tree->right, temp->elem); // delete the duplicate node
            }
        }
    }
    assert(invrep(tree) && !abb_exists(tree, e));
    return tree;
}


abb_elem abb_root(abb tree) {
    abb_elem root;
    assert(invrep(tree) && !abb_is_empty(tree));
    root = tree->elem;  
    assert(abb_exists(tree, root));
    return root;
}

abb_elem abb_max(abb tree) {
    abb_elem max_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    if (tree->right == NULL){
        max_e = tree->elem;
    } else {
        max_e = abb_max(tree->right);
    }  

    assert(invrep(tree) && abb_exists(tree, max_e));
    return max_e;
}

abb_elem abb_min(abb tree) {
    abb_elem min_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    if (tree->left == NULL){
        min_e = tree->elem;
    } else {
        min_e = abb_min(tree->left);
    }  
    assert(invrep(tree) && abb_exists(tree, min_e));
    return min_e;
}

void abb_dump(abb tree) {
    assert(invrep(tree));
    if (tree != NULL) {
        abb_dump(tree->left);
        printf("%d ", tree->elem);
        abb_dump(tree->right);
    }
}

abb abb_destroy(abb tree) {
    assert(invrep(tree));
    if (tree != NULL){
        abb_destroy(tree->left);
        abb_destroy(tree->right);
        free(tree);
        tree = NULL;
    }
    assert(tree == NULL);
    return tree;
}

