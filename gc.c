#include <stdio.h>
#include <stdlib.h>

#include <sys/mman.h>

#include "gc.h"

void gc_init()
{
    gc = (GarbageCollector_t*) mmap(NULL, sizeof(GarbageCollector_t), PROT_NONE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if(NULL == gc)
    {
        perror("mmap gc");
    }
    
    gc->used_pointers = init_LinkedList(NULL, DATATYPE_NULL); // double pointer
    gc->used_addresses = init_LinkedList(NULL, DATATYPE_NULL); // simple pointer
    
    gc->malloc = gc_malloc;
    gc->deallocate = gc_deallocate;
    gc->free = gc_free;
}

void *gc_malloc(size_t size)
{
    if(NULL == gc)
    {
        printf("inited garbage collector\n");
        gc_init();
    }
    
    gc->free();

    void *p = mmap(NULL, size, PROT_NONE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if((void *) -1 == p)
    {
        gc->deallocate();
        perror("mmap");
    }

    puts("1");
    gc->used_addresses->push(gc->used_addresses, p, SIMPLE_POINTER);
    puts("2");
    gc->used_pointers->push(gc->used_pointers, (void*)&p, DOUBLE_POINTER);
puts("3");
    return p;
}

void gc_deallocate()
{
    if(NULL != gc || NULL != gc->used_addresses)
    {
        gc->used_addresses->free(gc->used_addresses);
        free(gc->used_addresses);
        free(gc->used_pointers);
        free(gc);
    }
}

void gc_free()
{
    if(NULL == gc || NULL == gc->used_addresses)
        return;

    int pointed = 0;

    for(LinkedList *it_addr = gc->used_addresses; NULL != it_addr; it_addr = it_addr->next)
    {
        for(LinkedList *it_p = gc->used_pointers; NULL != it_p; it_p = it_p->next)
        {
            if(*(void**)it_p->data == it_addr->data)
            {
                pointed = 1;
                break;
            }
        }

        if(0 == pointed)
        {
            free(it_addr->data);
            pointed = 0;
        }
    }
}