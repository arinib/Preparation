//
// hashtable_gen.h
//
//
// Created by Arini Balakrishnan on 2/28/18
//
//

#ifndef ___hashtable_gen__
#define ___hashtable_gen__

#include <stdio.h>
#include <stdbool.h>

#define THRESHOLD 0.75

typedef struct hashtable_entry {
  void *key;
  size_t key_size;
  void *value;
  size_t value_size;
  struct hashtable_entry* next;
}hashtable_entry;

typedef struct hashtable {
  int num_buckets;
  hashtable_entry** buckets;
  int count;
  bool (*compare_keys)(void*, size_t, void*, size_t);
  unsigned long (*hash_func)(void*, size_t, int);
  void (*free_key)(void*);
  void (*free_val)(void*);
}hashtable;

hashtable* createHashTable(int num_buckets,
			   bool (*compare_keys)(void*, size_t, void*, size_t),
			   unsigned long (*hash_func)(void*, size_t, int),
			   void (*free_key)(void*),
			   void (*free_val)(void*));
void insert(hashtable* ht, void *key, size_t key_size,
	    void *value, size_t value_size);
hashtable_entry* get(hashtable *ht, void *key, size_t key_size);
void growHashTable(hashtable **ht, unsigned int new_size);
void destroyHashTable(hashtable *ht);
#endif /* defined(____ll_gen__) */
