#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define SUCCESS 0

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

/**
 * Used internally to initiate a buffer for the nodes.
 * Index in this buffer is used to find its corresponding element.
*/
struct Node *initNodeBuffer(uint32_t capacity);

/**
 * Initiate the list allocating a buffer of nodes,
 * and a buffer for the elements of which it contains.
*/
List *initList(size_t elementSize, uint32_t capacity);

/**
 * Releases all allocated buffers and the list iteself.
*/
int releaseList(List *list);

/**
 * Iterates through the buffer of nodes to find the first empty.
*/
struct Node *firstEmpty(List *list);

/**
 * Used internally to assign an element to the element buffer.
 * Elements index is always equal to the index of the node.
*/
void setElement(List *list, struct Node *node, void *src);

/**
 * Get a node at the index in list.
*/
struct Node *getNode(List *list, uint32_t index);

/**
 * Get an element at the index in list.
*/
void *getElement(List *list, uint32_t index);

/**
 * Set an element at the index in list.
*/
void setElementAtIndex(List *list, uint32_t index, void *src);

/**
 * Add an element as the first element of the list.
*/
void push(List *list, void *element);

/**
 * Add an element as the last element of the list.
*/
void top(List *list, void *element);

/**
 * Remove element at the indexed passed. 0-indexed.
*/
void pop(List *list, uint32_t index);

/**
 * Add an element at the position of the index passed, 0-indexed.
*/
void insert(List *list, uint32_t index, void *element);

/**
 * Reverse the list.
*/
void reverse(List *list);

/**
 * Runs passed function for each element in list.
 * Current implementation only modifies stored element.
*/
void forEach(List *list, void(*f)(void *));

/**
 *Used internally to swap elements.
*/
void swap(List *list, void *a, void *b);

/**
 * Takes a function pointer as argument to a function taking
 * two elements and returns a boolean and sort the elements.
*/
void sort(List *list, bool(*f)(void *, void *));

/**
 * Returns an array of stored elements. Will not release list.
 * Array is allocated and must be released.
*/
void *toArray(List *list);


/**
 * Build a list from an array of elements. Will not release array.
 * List is allocated and must be released.
*/
List *toListFromArray(void *src, uint32_t len, size_t size);

#endif // LINKED_LIST_H_
