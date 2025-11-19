#ifndef STACK_H
#define STACK_H

#include <stddef.h>

typedef unsigned char u8;

typedef struct {
    u8 *buff; // pointer to the memory buffer
    size_t capacity; // total size of the buffer
    size_t offset; // current offset
    size_t alloc;    // Total allocated size
} StackAlloc;

StackAlloc *stackInit(size_t size);
void *stackAlloc(StackAlloc *allocator, size_t size, size_t alignment);
void stackFree(StackAlloc *allocator, void *ptr);
void stackDestroy(StackAlloc *allocator);

#endif
