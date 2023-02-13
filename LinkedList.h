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
 *Used internally to initiate a buffer for the nodes.
 *Index in this buffer is used to find its corresponding element.
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
 * Add an element at the position of the index passed.
*/
void insert(List *list, uint32_t index, void *element);

/**
 * Reverse the list.
*/
void reverse(List *list);
