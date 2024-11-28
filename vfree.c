    #include "heap_memory.h"
    #include <stdio.h>


    void add_to_free_list(struct block *block) {
        block->prv = NULL;
        block->nxt = free_list_head;

        if (free_list_head) {
            free_list_head->prv = block;
        }

        free_list_head = block;
    }

    void coalesce_with_next(struct block *block) {
        if (block->nxt && (char *)block + block->size + sizeof(struct block) == (char *)block->nxt) {
            block->size += block->nxt->size + sizeof(struct block);
            block->nxt = block->nxt->nxt;

            if (block->nxt)
                block->nxt->prv = block;
        }
    }

    void coalesce_with_prev(struct block *block) {
        if (block->prv && (char *)block == (char *)block->prv + block->prv->size + sizeof(struct block)) {
            block->prv->size += block->size + sizeof(struct block);
            block->prv->nxt = block->nxt;

            if (block->nxt)
                block->nxt->prv = block->prv;
        }
    }

    void vfree(void *ptr) {
        if (!ptr)
            return;

        struct block *block = (struct block *)((char *)ptr - sizeof(struct block));

        add_to_free_list(block);

        coalesce_with_prev(block);
        coalesce_with_next(block);
    }
