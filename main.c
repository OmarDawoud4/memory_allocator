#include "heap_memory.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Allocating 100 bytes...\n");
    void *ptr1 = valloc(100);
    if (ptr1) {
        printf("Memory allocated at %p\n", ptr1);
        vfree(ptr1);
        printf("Memory freed at %p\n", ptr1);
    }

    printf("Allocating 200 bytes...\n");
    void *ptr2 = valloc(200);
    if (ptr2) {
        printf("Memory allocated at %p\n", ptr2);
        vfree(ptr2);
        printf("Memory freed at %p\n", ptr2);
    }

    void *ptr3 = valloc(50);
    void *ptr4 = valloc(25);
    void *ptr5 = valloc(75);
    vfree(ptr3);
    vfree(ptr4);
    vfree(ptr5);

    void *ptr_zero = valloc(0);
    if (!ptr_zero) {
        printf("No bytes to allocate \n");
    }

    return 0;
}
