#ifndef LINKEDLIST_H
#define LINKEDLIST_H

// LinkedList node structure
typedef struct Node {
    void* val;
    struct Node* next;
} Node;

// LinkedList structure
typedef struct LinkedList {
    size_t data_size;
    int num_elements;       //  number of elements in the list
    Node* head;             // head of linked list, or NULL if empty
} LinkedList;

// create an empty linked list
LinkedList* make_list(size_t data_size);

// append a node with specified value at the end of linked list
void list_append(LinkedList* list, void* val);

// delete the head of a linked list
void* list_pop(LinkedList* list);

// get a node with specified index within a linked list
void* list_get(LinkedList* list, int idx);

// destroy a linked list
void destroy_list(LinkedList* list);

#endif
