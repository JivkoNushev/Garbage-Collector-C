#ifndef GC
#define GC

#include <stdlib.h>

#include "unique_ptr.h"
#include "LinkedList.h"



typedef struct GarbageCollector_t
{
    LinkedList *used_pointers; 
    LinkedList *used_memory;

    void (*deallocate)();
    void (*add_pointer)(unique_ptr* ptr);
    void (*add_memory)(void* ptr);
    void (*free)();

} GarbageCollector_t;

static GarbageCollector_t *gc = NULL;

// constructor 
void GarbageCollector();

// destructor
void deallocate();

// TODO: refactor so that "gc" is at the beginning of the name

void add_pointer_gc(unique_ptr* ptr);
void add_memory_gc(void* ptr);
void free_gc();

#endif