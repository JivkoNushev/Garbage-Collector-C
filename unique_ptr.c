#include <stdio.h>
#include <stdlib.h>

#include "wrappers.h"
#include "gc.h"
#include "unique_ptr.h"

unique_ptr* UniquePtr(void *ptr, size_t size)
{
    if(NULL == ptr)
    {
        free_gc();

        ptr = err_allocate(malloc(size));

        DEBUG_PRINT printf("Alocated with malloc\n");

        add_memory_gc(ptr);

        DEBUG_PRINT printf("Added memory to GC\n");
    }

    unique_ptr *p = (unique_ptr *)err_allocate(malloc(sizeof(unique_ptr)));
    p->pointing_at = ptr;
    p->size = size;

    add_pointer_gc(p);

    DEBUG_PRINT printf("Added pointer to GC\n");

    return p;
}
