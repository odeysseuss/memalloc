#include "bump.h"
#include <stdint.h>

// calculate aligned offset from current position
// ptr -> current pointer position
// alignment must be a power of two
static inline u8 *align_pointer(u8 *ptr, size_t alignment) {
    uintptr_t addr = (uintptr_t)ptr;
    uintptr_t aligned_pointer = (addr + (alignment - 1)) & ~(alignment - 1);
    return (u8 *)aligned_pointer;
}

void bumpInit(BumpAlloc *allocator, void *data, size_t size) {
    if (!allocator || !data || size == 0)
        return;

    allocator->start = (u8 *)data;
    allocator->next = allocator->start;
    allocator->capacity = size;
    allocator->alloc = 0;
}

void *bumpAlloc(BumpAlloc *allocator, size_t size, size_t alignment) {
    if (!allocator || size == 0 || alignment == 0)
        return NULL;

    u8 *align_next = align_pointer(allocator->next, alignment);
    if (align_next < allocator->next)
        return NULL; // alignment overflow

    size_t total_size = (align_next - allocator->next) + size;
    if (allocator->next + total_size > allocator->start + allocator->capacity)
        return NULL;

    void *res = align_next;
    allocator->next = align_next + size;
    allocator->alloc += size;

    return res;
}

void bumpReset(BumpAlloc *allocator) {
    if (!allocator)
        return;

    allocator->next = allocator->start;
    allocator->alloc = 0;
}
