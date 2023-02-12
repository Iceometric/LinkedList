#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define SUCCESS 0

void reached(int x) { printf("Reached: %d\n", x); }


struct Node {

    struct Node *next;
    struct Node *previous;
    void *element;
    bool active; 

};

typedef struct List {

    struct Node *nodes;
    struct Node *start;
    void *elements;
    size_t size;
    uint32_t capacity;
    uint32_t len;

} List;

struct Node *initNodeBuffer(uint32_t capacity) {

    return (struct Node*)calloc(capacity, sizeof(struct Node));

}

List *initList(size_t elementSize, uint32_t capacity) {

    List *list = malloc(sizeof(List));
    list->nodes = initNodeBuffer(capacity);
    list->start = list->nodes;
    list->elements = calloc(capacity, elementSize * capacity);
    list->size = elementSize;
    list->capacity = capacity;
    list->len = 0;

    return list;
}

int releaseList(List *list) {
    
    free(list->nodes);
    free(list->elements);
    free(list);

    return SUCCESS;

}

struct Node *firstEmpty(List *list) {

    if (list->len <= 0) { 
        list->nodes->element = list->elements;
        return list->nodes; 
    }

    struct Node *current;
    for (int i = 0; i < list->capacity; i++) {
        current = &list->nodes[i];
        if (!current->active) {
            current->element = list->elements + (i * list->size);
            break;
        }
    }

    return current;

}

void setElement(List *list, struct Node *node, void *src) {

    char *p = src;
    for (size_t i = 0; i < list->size; i++) {
        memcpy(node->element +  (i * list->size), p, list->size);
    }

}

void push(List *list, void *element) {

    struct Node *current = firstEmpty(list);

    setElement(list, current, element);
    current->active = true;

    if (list->len == 0) {
        current->next = NULL;
    } else {
        current->next = list->start;
    }
    list->start = current;
    list->len++;

}


void top(List *list, void *element) {

    struct Node *inserted = firstEmpty(list);
    setElement(list, inserted, element);
    inserted->active = true;
    inserted->next = NULL;

    struct Node *current = list->start;
    while (current->next) { current = current->next; }
    
    current->next = inserted;

    list->len++;

}

void pop(List *list, uint32_t index) {

    if (index <= 0 || index > list->len) { return; }
    struct Node *current, *previous;

    current = list->start;
    int i = 0;
    while (i++ < index) { 
        previous = current;
        current = current->next; 
    }

    list->len--;
    previous->next = current->next;
    current->active = false;
    current->next = NULL;

}

void insert(List *list, uint32_t index, void *element) {

    if (index <= 0) { push(list, element); return; }
    if (index > list->len) { top(list, element); return; }

    struct Node *previous, *current, *inserted;
    current = list->start;
    
    int i = 0;
    while (i++ < index) { 
        previous = current;
        current = current->next; 
    }

    inserted = firstEmpty(list);
    setElement(list, inserted, element);
    inserted->active = true;
    inserted->next = current;

    if (previous) { previous->next = inserted; }

    list->len++;

}
