#ifndef GC
#define GC

#include <stdlib.h>

#include "LinkedList.h"

typedef struct GarbageCollector_t
{
    LinkedList *used_pointers; // double pointer
    LinkedList *used_addresses; // simple pointer

    void* (*malloc)(size_t size);
    void (*deallocate)();
    void (*free)();
} GarbageCollector_t;

static GarbageCollector_t *gc = NULL;

void gc_init();

void *gc_malloc(size_t size);
void gc_deallocate();
void gc_free();

#endif