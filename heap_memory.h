#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>  

struct block {
    size_t size;
    struct block *prv;
    struct block *nxt;
};
extern struct block *free_list_head;

void *valloc(size_t size);
void vfree(void *ptr);

#endif
