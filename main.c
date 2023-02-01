#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include "gc.h"
// keep used addresses and pointers
// call the gc when allocating or pointing to memory

// for enxt project : memlock - use it for abstraction in c oop ?

int main(int argc, char const *argv[])
{
    // initialize the garbage collector
    gc_init();

    printf("%ld\n", sysconf(_SC_PAGESIZE));

    int *pointer = (int*)gc_malloc(sizeof (int));
    puts("malloced");
    pointer = NULL;

    int *lol = (int*)gc_malloc(sizeof (int));

    // *address = 5;

    printf("Pointer is %d\n", *pointer);

    gc_deallocate();
    return 0;
}
