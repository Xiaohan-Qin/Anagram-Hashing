#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "LinkedList.h"


// create an empty linked list
LinkedList* make_list(size_t data_size) {
    LinkedList* list = calloc(1, sizeof(LinkedList));
    list->data_size = data_size;
    Node* head = calloc(1, sizeof(Node));
    list->head = head;
    return list;
}


// append a node with specified value at the end of linked list
void list_append(LinkedList* list, void* val) {
    Node* tmp = list->head;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    Node* new_node = calloc(1, sizeof(Node));
    new_node->val = calloc(1,list->data_size);
    memcpy(new_node->val, val, list->data_size);
    tmp->next = new_node;
    list->num_elements++;
}


// delete the head of a linked list
void* list_pop(LinkedList* list) {
    if (list != NULL) {
        void* val = calloc(1,list->data_size);
        memcpy(val, list->head->next->val, list->data_size);
        Node* pre_destroy = list->head->next;
        list->head->next = list->head->next->next;
        free(pre_destroy->val);
        free(pre_destroy);
        list->num_elements--;
        return val;
    }
    return NULL;
}


// get a node with specified index within a linked list
void* list_get(LinkedList* list, int idx) {
    Node* tmp = list->head;
    int tmp_idx = idx;
    while (tmp != NULL && tmp_idx >= 0) {
        tmp = tmp->next;
        tmp_idx--;
    }
    return tmp->val;
}


// destroy a linked list
void destroy_list(LinkedList* list) {
    Node* tmp = list->head;
    while (tmp != NULL) {
        Node* pre = tmp;
        free(tmp->val);
        tmp = tmp->next;
        free(pre);
    }
    free(list);
}
