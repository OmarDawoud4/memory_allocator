#include "heap_memory.h"
#include <unistd.h>
#include <stdio.h>   

struct block *free_list_head = NULL;
void *vsbrk(size_t size) {
    void *block = sbrk(size);
    if (block == (void *)-1)
        return NULL;

    struct block *sbrked_block = (struct block *)block;
    sbrked_block->size = size;
    sbrked_block->prv = NULL;
    sbrked_block->nxt = NULL;

    return sbrked_block;
}

struct block *best_fit(size_t size) {
    struct block *best_block = NULL;
    struct block *curr = free_list_head;

    while (curr) {
        if (curr->size >= size) {
            if (!best_block || curr->size < best_block->size)
                best_block = curr;
        }
        curr = curr->nxt;
    }

    return best_block;
}

void *valloc(size_t size) {
    if (size == 0)
        return NULL;

    struct block *best_block = best_fit(size);

    if (!best_block) {
        best_block = (struct block *)vsbrk(size + sizeof(struct block));
        if (!best_block)
            return NULL;

        best_block->size = size;
        return (char *)best_block + sizeof(struct block);
    }

    if (!best_block->prv) {
        free_list_head = best_block->nxt;
    } else {
        best_block->prv->nxt = best_block->nxt;
    }

    if (best_block->nxt)
        best_block->nxt->prv = best_block->prv;

    if (best_block->size > size + sizeof(struct block)) {
        struct block *new_block = (struct block *)((char *)best_block + sizeof(struct block) + size);
        new_block->size = best_block->size - size - sizeof(struct block);
        new_block->prv = NULL;
        new_block->nxt = free_list_head;

        if (free_list_head)
            free_list_head->prv = new_block;

        free_list_head = new_block;

        best_block->size = size;
    }

    return (char *)best_block + sizeof(struct block);
}
