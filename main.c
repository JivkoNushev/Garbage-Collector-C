#include <stdio.h>
#include <stdlib.h>

#include "gc.h"
// keep used addresses and pointers
// call the gc when allocating or pointing to memory

int main(int argc, char const *argv[])
{
    // initialize the garbage collector
    gc_init();

    int *pointer = gc_malloc(sizeof (int));


    gc_deallocate();
    return 0;
}
