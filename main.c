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

int sum(struct MyStruct *m) {

    return m->a + m->b + m->c + m-> d + m-> e;

}

void doubleMyStruct(struct MyStruct *m) {

    m->a *= 2;
    m->b *= 2;
    m->c *= 2;
    m->d *= 2;
    m->e *= 2;

}

int main() {

    List *list = initList(sizeof(struct MyStruct), 100);

    printf("push \n");
    push(list, &(struct MyStruct){1,2,3,4,5});
    forEach(list, (void *)printMyStruct);

    printf("top\n");
    top(list, &(struct MyStruct){2,3,4,5,6});
    forEach(list, (void *)printMyStruct);

    printf("insert 1\n");
    insert(list, 1, &(struct MyStruct){3,4,5,6,7});
    forEach(list, (void *)printMyStruct);

    printf("push \n");
    push(list, &(struct MyStruct){4,5,6,7,8});
    forEach(list, (void *)printMyStruct);

    printf("insert 2\n");
    insert(list, 2, &(struct MyStruct){5,6,7,8,9});
    forEach(list, (void *)printMyStruct);

    printf("pop 3\n");
    pop(list, 3);
    forEach(list, (void *)printMyStruct);

    printf("push \n");
    push(list, &(struct MyStruct){6,7,8,9,10});
    forEach(list, (void *)printMyStruct);

    printf("reverse\n");
    reverse(list);
    forEach(list, (void *)printMyStruct);

    printf("push \n");
    push(list, &(struct MyStruct){7,8,9,10,11});
    forEach(list, (void *)printMyStruct);

    printf("double\n");
    forEach(list, (void *)doubleMyStruct); 
    forEach(list, (void *)printMyStruct);

    releaseList(list);

    return SUCCESS;
}

