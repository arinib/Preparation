//
//  ll_gen.h
//  
//
//  Created by Arini Balakrishnan on 1/23/18.
//
//

#ifndef ____ll_gen__
#define ____ll_gen__

#include <stdio.h>
#include <stdbool.h>

typedef struct llnode {
    void* element;
    struct llnode* next;
}llnode;


typedef struct ll {
    llnode* head;
    llnode* tail;
    int elementSize;
    bool (*compare_func)(void*, void*);
    bool free_element;
}ll;

ll* create_newlist(bool (*compare_func)(void*, void*), bool free_element);
void destroy_list(ll* list);
void append_element(ll* list, void *element, size_t element_size);
void prepend_element(ll *list, void *element, size_t element_size);
void delete_element(ll *list, void *element);
llnode* find_element(ll *list, void *element);

#endif /* defined(____ll_gen__) */
