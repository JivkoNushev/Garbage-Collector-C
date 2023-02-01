#include <stdio.h>
#include <stdlib.h>

#include <sys/mman.h>

#include "gc.h"

void gc_init()
{
    // gc = (GarbageCollector_t*) mmap(NULL, sizeof(GarbageCollector_t),  PROT_READ | PROT_WRITE | PROT_EXEC, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    // if((void *) -1 == gc)
    // {
    //     perror("mmap gc");
    // }

    gc = (GarbageCollector_t*) malloc(sizeof(GarbageCollector_t));
    if(NULL == gc)
    {
        perror("malloc gc");
    }


    gc->used_pointers = init_LinkedList(NULL, DATATYPE_NULL); // double pointer
    gc->used_addresses = init_LinkedList(NULL, DATATYPE_NULL); // simple pointer
    
    gc->malloc = gc_malloc;
    gc->deallocate = gc_deallocate;
    gc->free = gc_free;
}

void *gc_malloc(size_t size)
{
    if(0 == size)
    {
        return NULL;
    }

    if(NULL == gc)
    {
        printf("inited garbage collector\n");
        gc_init();
    }
    

    // void *p = mmap(NULL, size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    // if((void *) -1 == p)
    // {
    //     gc->deallocate();
    //     perror("mmap");
    // }

    void *p = malloc(size);
    if(NULL == p)
    {
        gc->deallocate();
        perror("malloc");
    }

    if(NULL == gc->used_addresses)
    {
        gc->used_addresses = init_LinkedList(NULL, DATATYPE_NULL); // simple pointer
    }

    if(NULL == gc->used_pointers)
    {
        gc->used_pointers = init_LinkedList(NULL, DATATYPE_NULL); // double pointer
    }

    printf("address: %p\n", gc->used_addresses);
    printf("poitner: %p\n", &p);

    gc->used_addresses->push(gc->used_addresses, p, SIMPLE_POINTER);
    gc->used_pointers->push(gc->used_pointers, (void*)&p, DOUBLE_POINTER);
    
    gc->free();
 
    return p;
}

void gc_deallocate()
{
    if(NULL != gc && NULL != gc->used_addresses && DATATYPE_NULL != gc->used_addresses->type)
    {
        gc->used_addresses->free(gc->used_addresses);
        
        free(gc->used_pointers);
        free(gc);
    }
}

void gc_free()
{

    if(NULL == gc || DATATYPE_NULL == gc->used_addresses->type)
        return;

    int pointed = 0;

    LinkedList *it_addrs_prev = gc->used_addresses;
    for(LinkedList *it_addr = gc->used_addresses; NULL != it_addr; it_addrs_prev = it_addr, it_addr = it_addr->next)
    {
        for(LinkedList *it_p = gc->used_pointers; NULL != it_p; it_p = it_p->next)
        {
            puts("in");
            printf("f address: %p\n", it_addr->data);
            printf("f pointer: %p\n", *(void**)it_p->data);


            if(*(void**)it_p->data == it_addr->data)
            {
                pointed = 1;
                break;
            }
        }

        if(0 == pointed)
        {
            printf("Freeing\n");
            it_addrs_prev->next = it_addr->next;
            free(it_addr->data);
            free(it_addr);
            pointed = 0;
        }
    }
}