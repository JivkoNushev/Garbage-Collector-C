#ifndef WRAPPERS
#define WRAPPERS

#define DEBUG_MODE 0
#define DEBUG_START if(DEBUG_MODE){
#define DEBUG_END }

#define DEBUG_PRINT if(DEBUG_MODE)

void exit_msg(const char *msg);

void* err_allocate(void *ptr);

#endif
