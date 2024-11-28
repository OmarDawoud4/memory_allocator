# Memory Allocator with `sbrk`

## Overview

This project demonstrates a custom implementation of a dynamic memory allocator using the `sbrk` system call. It manages memory allocation and deallocation with a **best-fit strategy**, a linked-list-based **free list**, and block splitting/coalescing mechanisms.

### Key Features
1. Uses **`sbrk`** to request memory from the operating system.
2. Implements a **best-fit strategy** to find the most suitable free block for allocation.
3. Splits larger blocks into smaller usable and free blocks to optimize space usage.
4. Coalesces adjacent free blocks during deallocation to avoid fragmentation.


---

## Memory Layout of a Linux Process

![Screenshot from 2024-11-28 20-23-29](https://github.com/user-attachments/assets/ce35b3cf-6bf4-430f-8ac2-5e1194a5677d)

- **Text:** Stores the program's executable instructions.
- **Data:** Contains global and static variables.
- **Heap:** Dynamic memory managed by `malloc`, `calloc`, and `free`. It grows upward as more memory is allocated.
- **Unallocated Memory:** Space between the program break (managed with `sbrk`) and the stack.
- **Stack:** Stores local variables and function call information. It grows downward.

---

## Free List Management

The free list tracks unused memory blocks that are available for future allocations. Each block contains metadata and pointers for a doubly linked list.

![Screenshot from 2024-11-28 20-24-28](https://github.com/user-attachments/assets/55248325-88a0-475d-9af3-cbe5c81fcee9)

- **Fields:**
  - `size`: Size of the memory block.
  - `prv`: Pointer to the previous block.
  - `nxt`: Pointer to the next block.

**Operations:**
- Add newly freed blocks back to the free list.
- Merge adjacent free blocks during coalescing.


## Memory Allocation Flowchart

This flowchart outlines the steps to allocate memory:

![Screenshot from 2024-11-28 20-25-27](https://github.com/user-attachments/assets/2757b233-4764-46cb-a747-f33fde60e554)


1. **Check the free list** for a suitable block:
   - If a block of the required size is found:
     - If it's larger than the requested size, split it into two blocks.
     - Use the required part and leave the remaining part in the free list.
   - If no suitable block is found, request more memory using `sbrk(size)`.
2. Return the allocated memory to the caller.
