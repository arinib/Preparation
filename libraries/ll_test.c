//
//  ll_test.c
//  
//
//  Created by Arini Balakrishnan on 1/24/18.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "ll_gen.h"


typedef struct teststruct {
    int id;
    char *name;
}teststruct;

typedef struct hashtable_entry {
  void *key;
  void *element;
}hashtable_entry;

bool compare_structs(void* elementA, void* elementB){
    teststruct *elemA = (teststruct *)elementA;
    teststruct *elemB = (teststruct *)elementB;
    
    if (elemA->id == elemB->id) {
        return true;
    }
    else {
        return false;
    }
    return false;
}

bool compare_int(void *intA, void* intB){
    int *a = (int *) intA;
    int *b = (int *) intB;
    if (*a == *b) {
        return true;
    }
    else {
        return false;
    }
    return false;
}


void print_structlist(ll *list) {
    assert(list);
    assert(list->head);
    assert(list->tail);
    
    llnode* curr = list->head;
    while (curr) {
        teststruct *elem = (teststruct *)curr->element;
        printf("id: %d, name: %s\n", elem->id, elem->name);
        curr = curr->next;
    }
    return;
}


void print_intlist(ll *list){
    assert(list);
    assert(list->head);
    assert(list->tail);
    llnode* curr = list->head;
    while(curr) {
        printf("%d\n", *(int*)(curr->element));
        curr = curr->next;
    }
    return;
}

int main() {
    int i = 0;
    int count = 0;
    
    // Test with a list of structures
    ll* new_list = create_newlist(compare_structs, true);
    printf("Enter the number of entries:");
    scanf("%d", &count);
    
    printf("Enter the names:\n");
    for (i = 0; i < count; i++){
      teststruct test;
      test.name = (char *)malloc(sizeof(char) * 256);
      scanf("%s", test.name);
      test.id = i + 1;
      prepend_element(new_list, (void *)&test, sizeof(teststruct));
    }
    print_structlist(new_list);
    destroy_list(new_list);
    
    // Test with a list of integers
    ll* int_list = create_newlist(compare_int, false);
    printf("Enter the number of entries:");
    scanf("%d", &count);
    
    int elem;
    printf("Enter the numbers:\n");
    for (i = 0; i < count; i++){
        scanf("%d", &elem);
        append_element(int_list, &elem, sizeof(int));
    }
    print_intlist(int_list);
    destroy_list(int_list);
    return 0;
}
