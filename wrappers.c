#include <stdio.h>

#include <err.h>

#include "wrappers.h"
#include "gc.h"

void exit_msg(const char *msg)
{
    deallocate();
    printf("%s\n", msg);
    err(EXIT_FAILURE, NULL);
}

void* err_allocate(void *ptr)
{
    if(NULL == ptr)
    {
        deallocate();
        perror("malloc");
    }

    return ptr;
}