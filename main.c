#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "HashMap.h"


LinkedList* make_list(size_t data_size);
void list_append(LinkedList* list, void* val);
void* list_pop(LinkedList* list);
void* list_get(LinkedList* list, int idx);
void destroy_list(LinkedList* list);
hashtable_t* ht_create(size_t capacity);
void ht_put(hashtable_t* hasht, char* key, void* data);
void *ht_get(hashtable_t *hasht, char *key);


// string structure
typedef struct MyString {
    char *str;
} MyString;


// sort a string literal with alphabetic order
char *sort(char *word) {
    int i, j;
    char temp;
    char *buf = calloc(strlen(word), sizeof(char));
    strcpy(buf, word);
    for (i = 0; i < strlen(buf) - 1; i++) {
        for (j = i + 1; j < strlen(buf); j++) {
            if (buf[i] > buf[j]) {
                temp = buf[i];
                buf[i] = buf[j];
                buf[j] = temp;
            }
        }
    }
    return buf;
}


/* driver program for anagram hashing
   reads though a txt file and outputs anagrams */
int main() {
#define SIZE 128   // maximum size of a single string in file

    // read file and stroe key value pairs in hashtable
    // where the sorted string is key, the original strings (anagrams) are value
    FILE* ptr;
    char ch[SIZE];
    char ch_original[SIZE];
    char* ch_ordered;
    ptr = fopen("words.txt", "r");
    if (NULL == ptr) {
        printf("file can't be opened \n");
    }
    hashtable_t *ht = ht_create(1000);
    while (fgets(ch, SIZE, ptr) != NULL) {
        ch[strcspn(ch, "\n")] = 0;
        strcpy(ch_original, ch);      // original string, i.e. value
        ch_ordered = sort(ch);        // sorted string, i.e. key
        LinkedList *list = (LinkedList *) ht_get(ht, ch_ordered);
        if (list == NULL) {
            list = make_list(999);
        }
        list_append(list, (void *) ch_original);
        ht_put(ht, ch_ordered, list);
    }
    fclose(ptr);

    // interate hashtable and output all anagrams
    int i, j;
    for (i = 0; i < ht->capacity; i++) {
        if (ht->table[i] == NULL) {
            continue;
        }
        hash_elem_t* cur_head = ht->table[i];
        LinkedList *key_list = make_list(999);
        while (cur_head != NULL) {
            list_append(key_list, (void*)cur_head->key);
            cur_head = cur_head->next;
        }
        while (key_list->num_elements > 0) {
            char *key = list_pop(key_list);
            LinkedList *list = (LinkedList *) ht_get(ht, key);
            if (list != NULL) {
                printf("Anagrams of %s: ", key);
                for (j = 0; j < list->num_elements; j++) {
                    printf("%s, ", (char *) list_get(list, j));
                }
                printf("\n");
            }
        }
        destroy_list(key_list);
    }
    ht_destroy(ht);
    return 0;
}
