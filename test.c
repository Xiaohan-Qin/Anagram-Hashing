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


// String structure
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


// driver program for tests
int main() {
    // test linked list with integers
    LinkedList *my_list = make_list(sizeof(int));
    list_append(my_list, (void *) &(int) {1});
    list_append(my_list, (void *) &(int) {2});
    list_append(my_list, (void *) &(int) {3});
    int i, j;
    for (i = 0; i < my_list->num_elements; i++) {
        printf("Get the %d Item: %d\n", i, *(int *) list_get(my_list, i));
    }
    while (my_list->num_elements > 0) {
        int *res = (int *) list_pop(my_list);
        printf("%d\n", *res);
        free(res);
    }
    destroy_list(my_list);

    // test linked list with strings
    MyString *a = calloc(1, sizeof(MyString));
    a->str = "AAAAAAAAAAAA";
    MyString *b = calloc(1, sizeof(MyString));
    b->str = "BBBBBBBBBBBBBBBBBBBBBBBBBBBB";
    MyString *c = calloc(1, sizeof(MyString));
    c->str = "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC";
    LinkedList *char_list = make_list(sizeof(MyString));
    list_append(char_list, (void *) a);
    list_append(char_list, (void *) b);
    list_append(char_list, (void *) c);
    free(a);
    free(b);
    free(c);
    for (i = 0; i < char_list->num_elements; i++) {
        printf("Get the %d Item: %s\n", i, ((MyString *) list_get(char_list, i))->str);
    }
    while (char_list->num_elements > 0) {
        MyString *res = (MyString *) list_pop(char_list);
        printf("%s\n", res->str);
        free(res);
    }
    destroy_list(char_list);

    // test hashtable
    hashtable_t *myht = ht_create(8);
    LinkedList *test1 = make_list(999);
    list_append(test1, (void *) "some string value");
    ht_put(myht, "test1", test1);
    LinkedList *test2 = make_list(999);
    ht_put(myht, "test2", test2);
    LinkedList *test3 = make_list(999);
    ht_put(myht, "test3", test3);
    LinkedList *tmp = ht_get(myht, "test1");
    printf("Test HashTable: %s\n", (char *) list_get(tmp, 0));
    printf("\n");

    // test anagram-hashing
    hashtable_t *ht = ht_create(7);
    char *wordArr[] = {"cat", "dog", "tac", "god", "act", "aac", "caa", "aca", "gdo", "ss", "fun", "nuf"};
    int arrLen = sizeof(wordArr) / sizeof(wordArr[0]);
    for (i = 0; i < arrLen; i++) {
        char *key = sort(wordArr[i]);
        LinkedList *list = (LinkedList *) ht_get(ht, key);
        if (list == NULL) {
            list = make_list(999);
        }
        list_append(list, (void *) wordArr[i]);
        ht_put(ht, key, list);
    }
    for (i = 0; i < arrLen; i++) {
        char *key = sort(wordArr[i]);
        LinkedList *list = (LinkedList *) ht_get(ht, key);
        if (list != NULL) {
            printf("Anagrams of %s: ", wordArr[i]);
            for (j = 0; j < list->num_elements; j++) {
                printf("%s ", (char *) list_get(list, j));
            }
        }
        printf("\n");
    }
    ht_destroy(ht);
    return 0;
}
