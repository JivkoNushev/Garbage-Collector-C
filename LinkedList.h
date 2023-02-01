#ifndef LINKEDLIST
#define LINKEDLIST

typedef enum DataTypeLinkedList{DATATYPE_NULL, SIMPLE_POINTER, DOUBLE_POINTER} DataTypeLinkedList;

typedef struct LinkedList
{
    DataTypeLinkedList type;
    void *data;
    struct LinkedList *next;

    struct LinkedList* (*push)(struct LinkedList *this, void *data, DataTypeLinkedList type);
    struct LinkedList* (*pop)(struct LinkedList *this);
    void (*free)(struct LinkedList *this);

} LinkedList;

LinkedList* init_LinkedList(void *data, DataTypeLinkedList type);
LinkedList* push_LinkedList(LinkedList *this, void *data, DataTypeLinkedList type);
LinkedList* pop_LinkedList(LinkedList *this);
void free_LinkedList(LinkedList *this);

#endif