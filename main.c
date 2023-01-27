#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define SUCCESS 0
#define BUF_SIZE 1000

struct Node {

    struct Node *next;
    bool active; 
    int32_t value;

};

typedef struct ListHead {

    struct Node *start;
    struct Node *buf;
    uint32_t size;

} ListHead;

struct Node *initNodeBuffer() {

    return (struct Node*)calloc(BUF_SIZE, sizeof(struct Node));

}

ListHead *initList() {

    ListHead *lh = malloc(sizeof(ListHead));
    lh->buf = initNodeBuffer();
    lh->start = lh->buf;
    lh->size = 0;

    return lh;
}

struct Node *firstEmpty(ListHead *lh) {
    if (lh->size <= 0) { return lh->buf; }

    struct Node *current;
    for (int i = 0; i < BUF_SIZE; i++) {
        current = &lh->buf[i];
        if (!current->active)
            break;
    }

    return current;
}

void add(ListHead *lh, int32_t value) {
    struct Node *current = lh->start;
    while (current->next) { current = current->next; }

    lh->size++;
    current->value = value;
    current->active = true;
    current->next = firstEmpty(lh);
}

void push(ListHead *lh, int32_t value) {
    struct Node *current = firstEmpty(lh);

    lh->size++;
    current->value = value;
    current->active = true;
    current->next = lh->start;

    lh->start = current;
}

void pop(ListHead *lh, uint32_t index) {
    if (index <= 0 || index > lh->size) { return; }
    struct Node *current, *previous;

    current = lh->start;
    int i = 0;
    while (i++ < index) { 
        previous = current;
        current = current->next; 
    }

    lh->size--;
    previous->next = current->next;
    current->active = false;
    current->next = NULL;
}

void insert(ListHead *lh, uint32_t index, int32_t value) {
    if (index <= 0) { push(lh, value); return; }
    if (index > lh->size) { add(lh, value); return; }

    struct Node *previous, *current, *inserted;
    current = lh->start;
    
    int i = 0;
    while (i++ < index) { 
        previous = current;
        current = current->next; 
    }

    printf("\n");

    inserted = firstEmpty(lh);
    inserted->value = value;
    inserted->active = true;
    inserted->next = current;

    if (previous) { previous->next = inserted; }

    lh->size++;
}

void printValues(ListHead *lh) {
    if (lh->size <= 0) { return; }

    struct Node *current = lh->start;
    for (int i = 0; i < lh->size; i++) {
        printf("(%p) %d: %d\n", current, i, current->value);
        current = current->next;
    }
    printf("\n");
}



int main() {

    ListHead *list = initList();

    for (int i = 0; i < 10; i++) {
        add(list, i * 3);
    }

    printValues(list);

    pop(list, 5);

    printValues(list);

    add(list, 123);

    printValues(list);

    add(list, 123);

    printValues(list);

    add(list, 123);

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


