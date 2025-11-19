#include "stack.h"
#include <stdalign.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    size_t mem_size = 128;
    StackAlloc *allocator = stackInit(mem_size);

    // create a few strings in the memory region
    printf("Buff pointer: %p\n", (void*)allocator->buff);
    char *series = stackAlloc(allocator, sizeof(char) * 50, alignof(char));
    char *name = stackAlloc(allocator, sizeof(char) * 50, alignof(char));
    strcpy(series, "Breaking Bad");
    strcpy(name, "Walter White");
    printf("Series: %s\n", series);
    printf("Name  : %s\n", name);
    // free in LIFO
    stackFree(allocator, name);
    stackFree(allocator, series);

    printf("Buff pointer: %p\n", (void*)allocator->buff);
    char *alias = stackAlloc(allocator, sizeof(char) * 50, alignof(char));
    strcpy(alias, "Heisenberg");
    printf("Alias: %s\n", alias);
    stackFree(allocator, alias);

    stackDestroy(allocator);

    return 0;
}
