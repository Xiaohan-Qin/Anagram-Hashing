#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "HashMap.h"


/* 	Internal funcion to calculate hash for keys.
	It's based on the DJB algorithm from Daniel J. Bernstein.
	The key must be ended by '\0' character.*/
static unsigned int ht_calc_hash(char *key) {
    unsigned int h = 5381;
    while (*(key++))
        h = ((h << 5) + h) + (*key);
    return h;
}


// create hashtable with specified capacity
hashtable_t *ht_create(size_t capacity) {
    hashtable_t *hashtable = calloc(1, sizeof(hashtable_t));
    hashtable->capacity = capacity;
    hashtable->e_num = 0;
    hashtable->table = calloc(capacity, sizeof(hash_elem_t *));
    size_t i;
    for (i = 0; i < hashtable->capacity; i++) {
        hashtable->table[i] = NULL;
    }
    return hashtable;
}


// put a key value pair into hashtable
void ht_put(hashtable_t *hasht, char *key, void *data) {
    size_t idx = ht_calc_hash(key) % hasht->capacity;
    if (hasht->table[idx] == NULL) {
        hasht->table[idx] = calloc(1, sizeof(hash_elem_t));
        hasht->e_num++;
        hasht->table[idx]->key = NULL;
        hasht->table[idx]->val = NULL;
    }
    if (hasht->table[idx]->key == NULL) {
        hasht->table[idx]->key = calloc(strlen(key), sizeof(char));
        strcpy(hasht->table[idx]->key, key);
        hasht->table[idx]->val = data;
    } else {
        hash_elem_t *tmp = hasht->table[idx];
        while (tmp->next != NULL && strcmp(tmp->key, key) != 0) {
            tmp = tmp->next;
        }
        if (strcmp(tmp->key, key) == 0) {
            tmp->val = data;
        } else {
            hash_elem_t *new_elem = calloc(1, sizeof(hash_elem_t));
            hasht->e_num++;
            new_elem->key = calloc(strlen(key), sizeof(char));
            strcpy(new_elem->key, key);
            new_elem->val = data;
            tmp->next = new_elem;
        }
    }
}


// get the values of a given key from hashtable
void *ht_get(hashtable_t *hasht, char *key) {
    if (hasht == NULL || key == NULL) {
        return NULL;
    }
    size_t idx = ht_calc_hash(key) % hasht->capacity;
    hash_elem_t *tmp = hasht->table[idx];
    if (tmp == NULL) {
        return NULL;
    }
    while (tmp->next != NULL && strcmp(tmp->key, key) != 0) {
        tmp = tmp->next;
    }
    if (strcmp(tmp->key,key) ==0) {
        return tmp->val;
    }
    return NULL;
}


// destroy a hashtable
void ht_destroy(hashtable_t* hasht) {
    int i;
    for (i = 0; i < hasht->capacity; i++) {
	if (hasht->table[i] != NULL) {
	    free(hasht->table[i]->key);
	    destroy_list(hasht->table[i]->val);
	}
    }
    free(hasht);
}
