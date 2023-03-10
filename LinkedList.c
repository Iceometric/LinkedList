#include "LinkedList.h"

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

    memcpy(node->element, src, list->size);

}

void resetNode(List *list, struct Node *node) {

    memset(node->element, '\0', list->size);
    
    node->active = false;
    node->element = NULL;
    node->next = NULL;
    node->previous = NULL;

}


struct Node *getNode(List *list, uint32_t index) {

    if (index <= 0) { return NULL; }
    if (index > list->len - 1) { return NULL; }

    struct Node *current = list->start;
    for (int i = 0; i < index; i++) { current = current->next; }

    return current;

}

void *getElement(List *list, uint32_t index) {

    struct Node *node = getNode(list, index);
    return node->element;

}

void setElementAtIndex(List *list, uint32_t index, void *src) {

    struct Node *target = getNode(list, index);
    setElement(list, target, src);

}

void push(List *list, void *element) {

    struct Node *current = firstEmpty(list);
    setElement(list, current, element);
    current->active = true;
    current->previous = NULL;

    if (list->len == 0) {
        current->next = NULL;
    } else {
        current->next = list->start;
    }

    list->start = current;
    list->len++;

}


void top(List *list, void *element) {

    if (list->len <= 0) { push(list, element); return; }

    struct Node *current = list->start;
    while (current->next) { current = current->next; }
    
    struct Node *inserted = firstEmpty(list);
    setElement(list, inserted, element);
    inserted->active = true;
    inserted->next = NULL;
    inserted->previous = current;

    current->next = inserted;

    list->len++;

}

void pop(List *list, uint32_t index) {

    if (index < 0 || index > list->len - 1) { return; }

    struct Node *current, *previous, *next;
    current = list->start;

    for (int i = 0; i < index; i++) { current = current->next; }

    previous = current->previous;
    next = current->next;

    if (previous) { previous->next = next; }
    if (next) { next->previous = previous; }

    resetNode(list, current);

    list->len--;

}

void insert(List *list, uint32_t index, void *element) {

    if (index <= 0) { push(list, element); return; }
    if (index > list->len - 1) { top(list, element); return; }

    struct Node *previous, *current, *inserted;
    current = list->start;
    
    for (int i = 0; i < index; i++) { current = current->next; }

    previous = current->previous;

    inserted = firstEmpty(list);
    setElement(list, inserted, element);
    inserted->active = true;
    inserted->previous = previous;
    inserted->next = current;

    current->previous = inserted;

    previous->next = inserted; 

    list->len++;

}

void reverse(List *list) {

    struct Node *previous, *current, *next;

    current = list->start;

    while (current) {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }

    list->start = previous;

}

void forEach(List *list, void(*f)(void *)) {

    if (list->len <= 0) { return; }

    struct Node *node = list->start;
    for (int i = 0; i < list->len; i++) {
        f(node->element);
        node = node->next;
    }

}

void swap(List *list, void *a, void *b) {

    char temp[list->size];
    memcpy(temp, a, list->size);
    memcpy(a, b, list->size);
    memcpy(b, temp, list->size);

}

void sort(List *list, bool(*f)(void *, void *)) {
    
    if (list->len < 1) { return; }

    struct Node *current, *temp;
    temp = list->start;

    for (int i = 0; i < list->len; i++) {
        current = temp;
        for (int j = i; j < list->len; j++) {
            if(f(current->element, temp->element)) {
                swap(list, current->element, temp->element);
            }
            current = current->next;
        }
        temp = temp->next;
    }

}

void *toArray(List *list) {

    char *arr = malloc(list->size * list->len);
    struct Node *current = list->start;

    for (int i = 0; i < list->len; i++) {
        memcpy(arr + (i * list->size), current->element, list->size);
        current = current->next;
    }

    return arr;

}

List *toListFromArray(void *src, uint32_t len, size_t size) {

    List *list = initList(size, len * 2);
    list->len = len;

    memcpy(list->elements, src, size * len);

    size_t nodeSize = sizeof(struct Node);
    struct Node *current;
    for (int i = 0; i < len; i++) {

        current = list->start + (i * nodeSize);

        if (i == 0) {
            current->previous = NULL;
        } else {
            current->previous = current - nodeSize;
        }

        if (i == len - 1) {
            current->next = NULL;
        } else {
            current->next = current + nodeSize;
        }

        current->active = true;
        current->element = list->elements + (i * list->size);

        current = current->next;
        
    }

    return list;

}
