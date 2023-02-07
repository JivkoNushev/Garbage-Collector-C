#ifndef UNIQUE_PTR
#define UNIQUE_PTR

typedef struct unique_ptr
{
    void *pointing_at;
    size_t size;

} unique_ptr;

unique_ptr* UniquePtr(void *ptr, size_t size);

#endif