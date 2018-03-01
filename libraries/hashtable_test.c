//
// hashtable_test.c
//
// Created by Arini Balakrishnan on 02/28/18
//
// Test the hashtable implementation with String keys and Values

#include "hashtable_gen.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

void free_val(void *value){
  free(value);
}

void free_key(void *key){
  free(key);
}

bool compare_keys(void *keyA, size_t keyA_size, void *keyB, size_t keyB_size) {
  size_t comp_size = (keyA_size > keyB_size) ? keyB_size: keyA_size;
  return (strncmp((const char*)keyA, (const char*)keyB, comp_size) == 0);
}

unsigned long hash_func(void *key, size_t key_size, int num_buckets) {
  unsigned long hash = 5381;
  char *strKey = (char *)key;
  int i = 0;
  for(i = 0; i < key_size; i++){
    hash = ((hash << 5) + hash) + (int)strKey[i]; /* (hash * 33 + c) */
  }
  hash = hash % num_buckets;
  return hash;
}

int main(){
  char key[256], value[1024];
  hashtable *ht = createHashTable(20, compare_keys, hash_func, free_key, free_val);
  int cnt = 0;
  int i = 0;
  printf("Enter the number of key/value pairs:");
  scanf("%d", &cnt);
  printf("Enter the key/value pairs:");
  for (i = 0; i < cnt; i++) {
    scanf("%s %s", key, value);
    insert(ht, (void *)key, strlen(key), (void *)value, strlen(value));
  }
  
  for (i = 0; i < cnt; i++){
    printf("Key:");
    scanf("%s", key);
    hashtable_entry *hte = get(ht, key, strlen(key));
    if (hte) {
      printf("Found value %s\n", hte->value);
    }
    else{
      printf("No entry found\n");
    }
  }

  destroyHashTable(ht);
}
