#include <stdio.h>
#include <stdlib.h>

#include "wrappers.h"
#include "gc.h"
#include "unique_ptr.h"

unique_ptr UniquePtr(void *ptr, size_t size)
{
    if(NULL == ptr)
    {
        free_gc();

        ptr = err_allocate(malloc(size));

        printf("Alocated with malloc\n");

        add_memory_gc(ptr);

        printf("Added memory to GC\n");
    }

    unique_ptr p = {ptr, size};
    add_pointer_gc(p);

    printf("Added pointer to GC\n");

    return p;
}
