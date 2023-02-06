#include <stdio.h>
#include <stdlib.h>

#include "wrappers.h"
#include "gc.h"

void GarbageCollector()
{
    gc = (GarbageCollector_t*) err_allocate(malloc(sizeof (GarbageCollector_t))); 

    gc->used_memory = init_LinkedList(NULL, DATATYPE_NULL);
    gc->used_pointers = init_LinkedList(NULL, DATATYPE_NULL);

    gc->deallocate = deallocate;

    gc->add_pointer = add_pointer_gc;
    gc->add_memory = add_memory_gc;
    gc->free = free_gc;
}

void deallocate()
{
    gc->used_memory->free(gc->used_memory);
    gc->used_pointers->free(gc->used_pointers);

    free(gc);
}

void add_pointer_gc(unique_ptr ptr)
{
    gc->used_pointers->push(gc->used_pointers, (void*)(unique_ptr*)ptr, UNIQUE_POINTER);        
}

void add_memory_gc(void* ptr)
{
    printf("Trying to add memory to GC\n");

    gc->used_memory->push(gc->used_memory, ptr, SIMPLE_POINTER);   
}

void free_gc()
{
    for (LinkedList *it_mem = gc->used_memory; NULL != it_mem; it_mem = it_mem->next)
    {
        int used = 0;
        for(LinkedList *it_p = gc->used_pointers; NULL != it_p; it_p = it_p->next)
        {
            printf("Seg here?\n");
            printf("\t\t%p\n\t\t%p\n", ((unique_ptr)it_p->data).pointing_at, it_mem->data);

            if((*(unique_ptr*)(it_p->data)).pointing_at == it_mem->data)
            {
                used = 1;
                break;
            }
        }

        if(!used)
        {
            // gc->used_memory = gc->used_memory->remove(gc->used_memory, it_mem->data);
            printf("\t\t\t\tFreeing unused memory\n");

            if(NULL == it_mem->prev)
            {
                gc->used_memory = it_mem->next;
            }
            else
            {
                it_mem->prev->next = it_mem->next;
            }

            it_mem->next = NULL;
            it_mem->free(it_mem);
        }
    }
}

