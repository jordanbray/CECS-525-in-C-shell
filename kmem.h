#ifndef __KMEM_H__
#define __KMEM_H__

#include "screen.h"

#define NULL ((void *)0)

#define MEM_START 0x5000
#define MEM_BLOCK_SIZE 128
#define MEM_SIZE 0x6000 // must be a multiple of MEM_BLOCK_SIZE*8
#define MEM_END (MEM_START + MEM_SIZE)
#define MEM_BITSET_BITS (MEM_SIZE/MEM_BLOCK_SIZE)
#define MEM_BITSET_BYTES (MEM_BITSET_BITS/8)

void kfree(void *ptr);
void *kmalloc(int size);
void *krealloc(void *ptr, int size);
void kmeminit();

#endif

