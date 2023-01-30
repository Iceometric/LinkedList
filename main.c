#include "LinkedList.c"

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


