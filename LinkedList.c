#include <stdio.h>
#include <stdlib.h>

#include <sys/mman.h>

#include "LinkedList.h"
#include "gc.h"
#include "wrappers.h"

LinkedList* init_LinkedList(void *data, DataTypeLinkedList type)
{
    LinkedList* list = (LinkedList*)malloc(sizeof (LinkedList));
    if(NULL == list)
    {
        deallocate();
        perror("malloc");
    }

    list->type = type;
    list->data = data;
    list->next = NULL;
    list->prev = NULL;
    
    list->push = push_LinkedList;
    list->pop = pop_LinkedList;
    list->free = free_LinkedList;

    return list;
}

void free_LinkedList(LinkedList *this)
{
    if(NULL != this->next)
    {
        free_LinkedList(this->next);
        this->next = NULL;
    }

    switch (this->type)
    {
    case SIMPLE_POINTER:
        free(this->data);
        break;

    case DOUBLE_POINTER:
        free(*(void**)this->data);
        break;

    // not freeable
    case DATATYPE_NULL:
        break;

    default:
        exit_msg("Invalid datatype in LinkedList free");
        break;
    }

    free(this);
}

LinkedList* push_LinkedList(LinkedList *this, void *data, DataTypeLinkedList type)
{
    DEBUG_PRINT printf("Trying to push to LinkedList\n");

    if(NULL == this)
    {
        this = init_LinkedList(NULL, DATATYPE_NULL);
    }

    if(NULL == data)
    {
        return this;
    }

    if(NULL == this->data)
    {
        this->data = data;
        this->type = type;
        return this;
    }

    LinkedList *it = this;
    for(; NULL != it->next; it = it->next) {}

    it->next = init_LinkedList(data, type);
    it->next->prev = it;

    return this;
}

LinkedList* pop_LinkedList(LinkedList *this)
{
    if(NULL == this)
    {
        return NULL;
    }

    LinkedList *it = this;

    if(NULL == it->next)
    {
        it->free(it);
        return NULL;
    }

    for(; NULL != it->next->next; it = it->next) {}

    it->free(it->next);
    it->next = NULL;

    return this;
}