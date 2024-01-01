#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// ############################################################################
// Vector
// ############################################################################
typedef struct {
    int length;
    int capacity;
    int* storage;
} Vec;

Vec* vec_create(void) {
    Vec* vector = (Vec*)malloc(sizeof(Vec));

    vector->length = 0;
    vector->capacity = 1;
    vector->storage = (int*)malloc(sizeof(int) * vector->capacity);

    return vector;
}

void vec_insert_at(Vec* vec, int at, int item) {
    if (vec->length == vec->capacity) {
        vec->capacity++;
        vec->storage = (int*)realloc(vec->storage, sizeof(int) * vec->capacity);
    }

    for (int i = vec->length; i > at; i--) {
        vec->storage[i] = vec->storage[i - 1];
    }

    vec->storage[at] = item;
    vec->length++;
}

void vec_print(Vec* vec) {
    printf("[");
    for (int i = 0; i < vec->length; i++) {
        printf("%d", vec->storage[i]);
        if (i < vec->length - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

void vec_free(Vec* vec) {
    free(vec->storage);
    free(vec);
}

// ############################################################################
// Linked List
// ############################################################################
typedef struct LinkedListNode {
    int item;
    struct LinkedListNode* next;
} LinkedListNode;

LinkedListNode* list_node_create(int item){
    LinkedListNode* node = (LinkedListNode*)malloc(sizeof(LinkedListNode));

    node->item = item;
    node->next = NULL;

    return node;
}

typedef struct {
    int length;
    LinkedListNode* start;
} LinkedList;

LinkedList* list_create(void){
    LinkedList* linked_list = (LinkedList*)malloc(sizeof(LinkedList));

    linked_list->length = 0;
    linked_list->start = NULL;

    return linked_list;
}

void list_insert_at(LinkedList* list, int at, int item){
    LinkedListNode* node = list_node_create(item);

    if(at == 0){
        node->next = list->start;
        list->start = node;
    }else{
        LinkedListNode* temp = list->start;

        for(int i = 1; i < at; i++){
            temp = temp->next;
        }

        node->next = temp->next;
        temp->next = node;
    }

    list->length++;
}

void list_print(LinkedList* list){
    LinkedListNode* temp = list->start;

    printf("[");
    while(temp != NULL){
        printf("%d", temp->item);
        temp = temp->next;
        if (temp != NULL) {
            printf(", ");
        }
    }
    printf("]\n");
}

void list_free(LinkedList* list){
    if (list == NULL){
        return;
    }

    LinkedListNode* temp = list->start;
    LinkedListNode* next = NULL;

    while(temp != NULL){
        next = temp->next;
        free(temp);
        temp = next;
    }

    free(list);
}

// ############################################################################
// Doubly Linked List
// ############################################################################
typedef struct DoublyLinkedListNode {
    int item;
    struct DoublyLinkedListNode* prev;
    struct DoublyLinkedListNode* next;
} DoublyLinkedListNode;

DoublyLinkedListNode* dlist_node_create(int item) {
    DoublyLinkedListNode* node = (DoublyLinkedListNode*)malloc(sizeof(DoublyLinkedListNode));

    node->item = item;
    node->prev = NULL;
    node->next = NULL;

    return node;
}

typedef struct {
    int length;
    DoublyLinkedListNode* start;
    DoublyLinkedListNode* end;
} DoublyLinkedList;

DoublyLinkedList* dlist_create(void) {
    DoublyLinkedList* linked_list = (DoublyLinkedList*)malloc(sizeof(DoublyLinkedList));

    linked_list->length = 0;
    linked_list->start = NULL;
    linked_list->end = NULL;

    return linked_list;
}

void dlist_insert_at(DoublyLinkedList* l, int at, int item) {
    DoublyLinkedListNode* node = dlist_node_create(item);

    // If list is empty
    if (l->length == 0){
        l->start = node;
        l->end = node;
    // If insert at beginning
    }else if (at == 0){
        node->next = l->start;
        l->start->prev = node;
        l->start = node;
    // If insert at end
    }else if (at == l->length){
        node->prev = l->end;
        l->end->next = node;
        l->end = node;
    // Insert at a position
    }else{
        // Check if position is closer to start
        if (at <= l->length / 2){
            DoublyLinkedListNode* temp = l->start;
            for (int i = 0; i < at - 1; i++) {
                temp = temp->next;
            }

            node->next = temp->next;
            node->prev = temp;
            temp->next->prev = node;
            temp->next = node;
        // Check if position is closer to end
        }else{
            DoublyLinkedListNode* temp = l->end;
            for (int i = l->length; i > at; i--){
                temp = temp->prev;
            }

            node->next = temp->next;
            node->prev = temp;
            temp->next->prev = node;
            temp->next = node;
        }
    }

    l->length++;  
}

void dlist_print(DoublyLinkedList* l) {
    printf("[");

    DoublyLinkedListNode* temp = l->start;

    while (temp != NULL) {
        printf("%d", temp->item);

        if (temp->next != NULL) {
            printf(", ");
        }

        temp = temp->next;
    }

    printf("]\n");
}

void dlist_free(DoublyLinkedList* l) {
    DoublyLinkedListNode* current = l->start;

    while (current != NULL) {
        DoublyLinkedListNode* temp = current;
        current = current->next;
        free(temp);
    }

    free(l);
}
