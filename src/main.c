#include "bump.h"
#include <stdalign.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    size_t mem_size = 256;
    void *memory_pool = malloc(mem_size);
    BumpAlloc allocator;
    bumpInit(&allocator, memory_pool, mem_size);

    // create a few strings in the memory region
    char *series = bumpAlloc(&allocator, sizeof(char) * 50, alignof(char));
    char *name = bumpAlloc(&allocator, sizeof(char) * 50, alignof(char));
    char *dragon = bumpAlloc(&allocator, sizeof(char) * 50, alignof(char));
    char *title = bumpAlloc(&allocator, sizeof(char) * 50, alignof(char));

    // use the strings with not so safe methods
    strcpy(series, "House of the Dragons");
    strcpy(name, "Daemon Targaryen");
    strcpy(dragon, "Caraxes (The blood wyrm)");
    sprintf(title, "%s: The Rogue Prince", name);

    printf("Total memory used: %zu bytes\n", allocator.alloc);
    printf("Total memory wasted: %zu bytes\n", (mem_size - allocator.alloc));
    printf("Series: %s\n", series);
    printf("Name  : %s\n", name);
    printf("Dragon: %s\n", dragon);
    printf("Title : %s\n", title);

    bumpReset(&allocator);
    free(memory_pool);

    return 0;
}
