#ifndef BUMP_H
#define BUMP_H

#include <stddef.h>

typedef unsigned char u8;

// Manages pre allocated memory.
// Implemented methods borrows the memory and does not own it.
// Caller must pre allocate memory and free it themselves.
typedef struct {
    u8 *start;       // Start of memory region
    u8 *next;        // Next available memory
    size_t capacity; // Memory block capacity
    size_t alloc;    // Total allocated size
} BumpAlloc;

// Initialize allocator with existing memory buffer
void bumpInit(BumpAlloc *allocator, void *data, size_t size);
// Allocate memory block.
// Alignment must be a power of two (use: alignof(type)).
void *bumpAlloc(BumpAlloc *allocator, size_t size, size_t alignment);
// Reset allocator to start
void bumpReset(BumpAlloc *allocator);

#endif
