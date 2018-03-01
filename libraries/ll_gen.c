//
//  ll_gen.c
//  
//
//  Created by Arini Balakrishnan on 1/23/18.
//
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "ll_gen.h"

ll* create_newlist(bool (*compare_func)(void*, void*), bool free_element){
    ll* new_list = (ll*)malloc(sizeof(ll));
    printf("Creating a new list\n");
    new_list->head = NULL;
    new_list->tail = NULL;
    new_list->compare_func = compare_func;
    new_list->free_element = free_element;
    return new_list;
}

void destroy_list(ll *list){
    assert(list);
    assert(list->head);
    assert(list->tail);
    llnode* curr = list->head;
    while (curr) {
        llnode *next = curr->next;
        if (list->free_element){
            free(curr->element);
        }
        free(curr);
        curr = next;
    }
    free(list);
}
void append_element(ll* list, void *element, size_t element_size) {
    assert(list);
    assert(element);
    llnode* newnode = (llnode*)malloc(sizeof(llnode));
    assert(newnode);
    newnode->element = (void *)malloc(element_size);
    memcpy(newnode->element, element, element_size);
    newnode->next = NULL;
    if (list->tail == NULL) {
        list->tail = newnode;
        list->head = newnode;
    }
    else {
        list->tail->next = newnode;
        list->tail = newnode;
    }
}

void prepend_element(ll *list, void *element, size_t element_size) {
    assert(list);
    assert(element);
    llnode* newnode = (llnode*)malloc(sizeof(llnode));
    assert(newnode);
    newnode->element = (void *)malloc(element_size);
    memcpy(newnode->element, element, element_size);
    newnode->next = NULL;
    if (list->head == NULL) {
        list->tail = newnode;
        list->head = newnode;
    }
    else {
        newnode->next = list->head;
        list->head = newnode;
    }
}

void delete_element(ll *list, void *element) {
    assert(list);
    assert(list->head);
    assert(list->tail);
    llnode* prev = NULL;
    llnode* curr = list->head;
    llnode* next = curr->next;
    while (curr) {
        if (list->compare_func(curr->element, element)){
            if(prev == NULL) {
                list->head = next;
            }
            else {
                prev->next = curr->next;
                if (curr == list->tail) {
                    list->tail = prev;
                }
            }
            free(curr);
            break;
        }
        prev = curr;
        curr = next;
        next = curr->next;
    }
}

llnode* find_element(ll *list, void *element) {
    assert(list);
    assert(list->head);
    assert(list->tail);
    assert(element);
    
    llnode* curr = list->head;
    llnode* result = NULL;
    
    while(curr) {
        if (list->compare_func(curr->element, element)){
            result = curr->element;
            break;
        }
        curr = curr->next;
    }
    return result;
}
