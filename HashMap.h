#ifndef HASHMAP_H
#define HASHMAP_H

#include "LinkedList.h"

// Hashtable element structure
typedef struct hash_elem_t {
    struct hash_elem_t* next;
    char* key;
    LinkedList* val;
} hash_elem_t;

// Hashtabe structure
typedef struct {
    size_t capacity;     	 // Hashtable capacity (in terms of hashed keys)
    size_t e_num;	         // Number of element currently stored in the hashtable
    hash_elem_t** table;	 // The table containaing elements
} hashtable_t;

// create hashtable with specified capacity
hashtable_t* ht_create(size_t capacity);

// put a key value pair into hashtable
void ht_put(hashtable_t* hasht, char* key, void* data);

// get the values of a given key from hashtable
void *ht_get(hashtable_t *hasht, char *key);

// destroy a hashtable
void ht_destroy(hashtable_t* hasht);

#endif
