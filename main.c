#include <stdio.h>
#include "LinkedList.c"

struct MyStruct {

    int a;
    int b;
    int c;
    int d;
    int e;

};

void printMyStruct(struct MyStruct *m) {

    printf("a: %d, b: %d, c: %d, d: %d, e: %d\n", m->a, m->b, m->c, m->d, m->e);

}

void printValuesi(List *list) {

    if (list->len <= 0) { return; }

    struct Node *current = list->start;
    for (int i = 0; i < list->len; i++) {
        printf("(%p) %d: %d\n", current, i, *(int *)current->element);
        current = current->next;
    }
    printf("\n");

}

void printMyStructArray(List *list) {

    if (list->len <= 0) { return; }

    struct Node *current = list->start;
    for (int i = 0; i < list->len; i++) {
        printf("%d: ",i);
        printMyStruct((struct MyStruct*)current->element);
        current = current->next;
    }
    printf("\n");

}

int main() {

    List *list = initList(sizeof(struct MyStruct), 100);

    int asd = 123;
    push(list, &(struct MyStruct){1,2,3,4,5});
    printMyStructArray(list);
    top(list, &(struct MyStruct){2,3,4,5,6});
    printMyStructArray(list);
    insert(list, 1, &(struct MyStruct){3,4,5,6,7});
    printMyStructArray(list);
    push(list, &(struct MyStruct){4,5,6,7,8});
    printMyStructArray(list);
    insert(list, 2, &(struct MyStruct){5,4,5,6,7});
    printMyStructArray(list);
    pop(list, 3);
    printMyStructArray(list);
    reverse(list);
    printMyStructArray(list);

    return SUCCESS;
}


