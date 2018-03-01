//
// hashtable_gen.c
//
// Created by Arini Balakrishnan on 2/28/18
//
//

#include "hashtable_gen.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

hashtable* createHashTable(int num_buckets,
			   bool (*compare_keys)(void*, size_t, void*, size_t),
			   unsigned long (*hash_func)(void*, size_t, int),
			   void (*free_key)(void*),
			   void (*free_val)(void*)){
    assert(num_buckets > 0);
    hashtable* ht = (hashtable*)malloc(sizeof(hashtable));
    assert(ht);
    ht->num_buckets = num_buckets;
    ht->count = 0;
    ht->compare_keys = compare_keys;
    ht->hash_func = hash_func;
    ht->free_key = free_key;
    ht->free_key = free_val;
    ht->buckets = (hashtable_entry**)malloc(sizeof(hashtable_entry*) * num_buckets);
    int i = 0;
    for (i = 0; i < ht->num_buckets; i++) {
      ht->buckets[i] = NULL;
    }
    
    return ht;
}

hashtable_entry* get(hashtable *ht, void *key, size_t key_size) {
    assert(ht);
    assert(key);
    
    unsigned long bucket_num = ht->hash_func(key, key_size, ht->num_buckets);
    hashtable_entry* retVal = NULL;
    hashtable_entry* bucket = NULL;
    bucket = ht->buckets[bucket_num];
    while(bucket != NULL) {
        if(ht->compare_keys(bucket->key, bucket->key_size, key, key_size)) {
            retVal = bucket;
        }
        bucket = bucket->next;
    }
    return retVal;
}
/**
 * Insert a new key/value pair into the hashtable. If the key already exists, this
 * function just replaces the value.
 **/
void insert(hashtable* ht, void *key, size_t key_size,
            void *value, size_t value_size) {
    assert(ht);
    assert(key);
    assert(value);
    
    hashtable_entry* newEntry = NULL;

    printf("Checking if the key already exists\n");
    //Check if the key already exists
    newEntry = get(ht, key, key_size);
    if (newEntry != NULL) {
        if (ht->free_val) {
            ht->free_val(newEntry->value);
        }
        newEntry->value = (void *)malloc(value_size);
        memcpy(newEntry->value, value, value_size);
    }
    else {
    // New element. Create one and add
        unsigned long bucket_num = ht->hash_func(key, key_size, ht->num_buckets);
        
        newEntry = (hashtable_entry*)malloc(sizeof(hashtable_entry));
	newEntry->key = (void *)malloc(key_size);
	newEntry->value = (void *)malloc(value_size);
        memcpy(newEntry->key, key, key_size);
        memcpy(newEntry->value, value, value_size);
        newEntry->next = ht->buckets[bucket_num];
        ht->buckets[bucket_num] = newEntry;
        ht->count++;
    }
    
    //Check if we are at or above the threshold for the hashtable entries.
    if (ht->count >= THRESHOLD * ht->num_buckets) {
        growHashTable(&ht, ht->num_buckets * 2);
    }
}

// Increase the size of the hashtable
void growHashTable(hashtable** ht, unsigned int new_size) {
    assert(*ht);
    hashtable *new_ht = (hashtable *)malloc(sizeof(hashtable));
    new_ht->num_buckets  = new_size;
    new_ht->hash_func = (*ht)->hash_func;
    new_ht->compare_keys = (*ht)->compare_keys;
    new_ht->free_val = (*ht)->free_val;
    new_ht->free_key = (*ht)->free_key;
    new_ht->count = 0;

    // Copy all the values from the old hashtable to the new bigger hashtable
    int i = 0;
    for (i = 0; i < (*ht)->num_buckets; i++) {
      hashtable_entry* bucket = (*ht)->buckets[i];
      while(bucket) {
	insert(new_ht, bucket->key, bucket->key_size, bucket->value, bucket->value_size);
	bucket = bucket->next;
      }
    }

    hashtable *tmp = (*ht);
    (*ht) = new_ht;
    destroyHashTable(tmp);
}

void destroyHashTable(hashtable *ht) {
  assert(ht);
  int i = 0;
  for (i = 0; i < ht->num_buckets; i++){
    hashtable_entry* curr = ht->buckets[i];
    hashtable_entry* next = NULL;
    while(curr) {
      if (ht->free_key){
	ht->free_key(curr->key);
      }
      if (ht->free_val){
	ht->free_val(curr->value);
      }
      next = curr->next;
      free(curr);
      curr = next;
    }
  }
  free(ht);
}

