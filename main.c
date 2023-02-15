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

    printf("(%p) a: %d, b: %d, c: %d, d: %d, e: %d\n", m, m->a, m->b, m->c, m->d, m->e);

}

void doubleMyStruct(struct MyStruct *m) {

    m->a *= 2;
    m->b *= 2;
    m->c *= 2;
    m->d *= 2;
    m->e *= 2;

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

    printf("push \n");
    push(list, &(struct MyStruct){1,2,3,4,5});
    printMyStructArray(list);

    printf("top\n");
    top(list, &(struct MyStruct){2,3,4,5,6});
    printMyStructArray(list);

    printf("insert 1\n");
    insert(list, 1, &(struct MyStruct){3,4,5,6,7});
    printMyStructArray(list);

    printf("push \n");
    push(list, &(struct MyStruct){4,5,6,7,8});
    printMyStructArray(list);

    printf("insert 2\n");
    insert(list, 2, &(struct MyStruct){5,6,7,8,9});
    printMyStructArray(list);

    printf("pop 3\n");
    pop(list, 3);
    printMyStructArray(list);

    printf("push \n");
    push(list, &(struct MyStruct){6,7,8,9,10});
    printMyStructArray(list);

    printf("reverse\n");
    reverse(list);
    printMyStructArray(list);

    printf("push \n");
    push(list, &(struct MyStruct){7,8,9,10,11});
    printMyStructArray(list);

    forEach(list, printMyStruct);
    forEach(list, doubleMyStruct); 
    forEach(list, printMyStruct);

    releaseList(list);

    return SUCCESS;
}

