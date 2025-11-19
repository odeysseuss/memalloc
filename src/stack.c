#include "stack.h"
#include <stdint.h>
#include <stdlib.h>

typedef struct {
    size_t size;
} AllocSize;

// alignment must be a power of two
static inline u8 *align_pointer(u8 *ptr, size_t alignment) {
    uintptr_t addr = (uintptr_t)ptr;
    uintptr_t aligned_pointer = (addr + (alignment - 1)) & ~(alignment - 1);
    return (u8 *)aligned_pointer;
}

StackAlloc *stackInit(size_t size) {
    StackAlloc *allocator = malloc(sizeof(StackAlloc));
    if (!allocator)
        return NULL;

    allocator->buff = malloc(size);
    if (!allocator->buff) {
        free(allocator);
        return NULL;
    }

    allocator->capacity = size;
    allocator->offset = 0;
    allocator->alloc = 0;
    return allocator;
}

void *stackAlloc(StackAlloc *allocator, size_t size, size_t alignment) {
    if (!allocator || size == 0)
        return NULL;

    // calculate total space needed: header + alignment padding + data
    size_t header_size = sizeof(AllocSize);
    u8 *start = allocator->buff + allocator->offset;
    u8 *after_header = start + header_size;
    u8 *aligned = align_pointer(after_header, alignment);
    size_t padding = aligned - after_header;
    size_t total_size = header_size + padding + size;

    if (allocator->offset + total_size > allocator->capacity)
        return NULL;

    // store size in header
    AllocSize *header = (AllocSize *)start;
    header->size = size;

    allocator->offset += total_size;
    allocator->alloc += size;

    return aligned;
}

void stackFree(StackAlloc *allocator, void *ptr) {
    if (!allocator || !ptr)
        return;

    // get header
    u8 *data_ptr = (u8 *)ptr;
    AllocSize *header = (AllocSize *)(data_ptr - sizeof(AllocSize));
    size_t size = header->size;

    // calculate total allocation size (find start of this allocation)
    u8 *alloc_start = (u8 *)header;
    u8 *current_top = allocator->buff + allocator->offset;
    u8 *expected_data_end = data_ptr + size;

    // only free if this is the most recent allocation (LIFO)
    if (expected_data_end == current_top) {
        allocator->offset = alloc_start - allocator->buff;
        allocator->alloc -= size;
    }
}

void stackDestroy(StackAlloc *allocator) {
    if (allocator) {
        free(allocator->buff);
        free(allocator);
    }
}
