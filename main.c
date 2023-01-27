#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define SUCCESS 0
#define BUF_SIZE 1000

struct Node {

    struct Node *next;
    int32_t value;
    bool active; 

};

typedef struct List {

    struct Node *start;
    struct Node *buf;
    uint32_t size;

} List;

struct Node *initNodeBuffer() {

    return (struct Node*)calloc(BUF_SIZE, sizeof(struct Node));

}

List *initList() {

    List *list = malloc(sizeof(List));
    list->buf = initNodeBuffer();
    list->start = list->buf;
    list->size = 0;

    return list;
}

struct Node *firstEmpty(List *list) {
    if (list->size <= 0) { return list->buf; }

    struct Node *current;
    for (int i = 0; i < BUF_SIZE; i++) {
        current = &list->buf[i];
        if (!current->active)
            break;
    }

    return current;
}

void top(List *list, int32_t value) {
    struct Node *current = list->start;
    while (current->next) { current = current->next; }

    list->size++;
    current->value = value;
    current->active = true;
    current->next = firstEmpty(list);
}

void push(List *list, int32_t value) {
    struct Node *current = firstEmpty(list);

    list->size++;
    current->value = value;
    current->active = true;
    current->next = list->start;

    list->start = current;
}

void pop(List *list, uint32_t index) {
    if (index <= 0 || index > list->size) { return; }
    struct Node *current, *previous;

    current = list->start;
    int i = 0;
    while (i++ < index) { 
        previous = current;
        current = current->next; 
    }

    list->size--;
    previous->next = current->next;
    current->active = false;
    current->next = NULL;
}

void insert(List *list, uint32_t index, int32_t value) {
    if (index <= 0) { push(list, value); return; }
    if (index > list->size) { top(list, value); return; }

    struct Node *previous, *current, *inserted;
    current = list->start;
    
    int i = 0;
    while (i++ < index) { 
        previous = current;
        current = current->next; 
    }

    inserted = firstEmpty(list);
    inserted->value = value;
    inserted->active = true;
    inserted->next = current;

    if (previous) { previous->next = inserted; }

    list->size++;
}

void printValues(List *list) {
    if (list->size <= 0) { return; }

    struct Node *current = list->start;
    for (int i = 0; i < list->size; i++) {
        printf("(%p) %d: %d\n", current, i, current->value);
        current = current->next;
    }
    printf("\n");
}



int main() {

    List *list = initList();

    for (int i = 0; i < 10; i++) {
        top(list, i * 3);
    }

    printValues(list);

    pop(list, 5);

    printValues(list);

    top(list, 123);

    printValues(list);

    top(list, 123);

    printValues(list);

    top(list, 123);

    printValues(list);

    pop(list, 5);

    printValues(list);

    insert(list, 5, 43);

    printValues(list);

    insert(list, 1, 44);

    printValues(list);

    insert(list, 0, 45);

    printValues(list);

    return SUCCESS;
}


