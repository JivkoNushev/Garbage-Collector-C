#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include "unique_ptr.h"
#include "gc.h"
// keep used addresses and pointers
// call the gc when allocating or pointing to memory

int main(int argc, char const *argv[])
{
    GarbageCollector();

    printf("GarbageCollector Constructed\n");

    unique_ptr ptr = UniquePtr(NULL, sizeof(int));

    printf("UniquePtr Constructed\n");

    ptr.pointing_at = NULL;

    unique_ptr ptr2 = UniquePtr(NULL, sizeof(int));

    printf("UniquePtr Constructed\n");

    deallocate();
    
    printf("GarbageCollector Deconstructed\n");

    return 0;
}
