#ifndef BUMP_H
#define BUMP_H

#include <stddef.h>

// Manages pre allocated memory.
// Implemented methods borrows the memory and does not own it.
// Caller must pre allocate memory and free it themselves.
typedef struct {
    unsigned char *start; // Start of memory region
    unsigned char *next; // Next available memory
    size_t capacity; // Memory block capacity
    size_t alloc; // Total allocated size
} BumpAlloc;

// Initialize allocator with existing memory buffer
void bumpInit(BumpAlloc *allocator, void *data, size_t size);
// Allocate memory block.
// Alignment must be a power of two (use: alignof(type)).
void *bumpAlloc(BumpAlloc *allocator, size_t size, size_t alignment);
// Reset allocator to start
void bumpReset(BumpAlloc *allocator);

#endif
