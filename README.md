How to use LinkedList

- Create a new List-pointer and assign it to initList-function
- releastList, releases all accuired memory back to OS
- push, set a new element at beginning of list
- top, set a new element at end of list
- insert, insert element at 0-indexed index
- pop, remove element at 0-indexed index
- reverse, reverses element order in list
- forEach, pass a function that operates on a single element and run for each element
- sort, sort the list based on function pointer result
- setElementAtIndex, update value at index

Internally used functions

- initNodebuffer, creates buffer storing the nodes
	- a nodes index in this array corresponds to index of its element in the element buffer
- firstEmpty, findes the first empty space in buffer and returns that node
- setElement, used to set passed element to node
- getNode, returns node at index in list
- swap, used for sort function to swap elements associated with nodes
