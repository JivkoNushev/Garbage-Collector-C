#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "unique_ptr.h"
#include "gc.h"
#include "wrappers.h"

int main(int argc, char const *argv[])
{
    GarbageCollector();

    DEBUG_PRINT printf("GarbageCollector Constructed\n");

    unique_ptr* ptr = UniquePtr(NULL, sizeof(int));

    DEBUG_PRINT printf("UniquePtr Constructed\n");

    ptr->pointing_at = NULL;

    unique_ptr* ptr2 = UniquePtr(NULL, sizeof(int));

    DEBUG_PRINT printf("UniquePtr Constructed\n");

    deallocate();
    
    DEBUG_PRINT printf("GarbageCollector Deconstructed\n");

    return 0;
}
