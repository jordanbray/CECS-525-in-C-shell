#ifndef __KMEM_H__
#define __KMEM_H__

#include "screen.h"

#define NULL ((void *)0)

#define MEM_START 0x4200
#define MEM_BLOCK_SIZE 32
#define MEM_SIZE 0xE00 // must be a multiple of MEM_BLOCK_SIZE*8
#define MEM_END (MEM_START + MEM_SIZE)
#define MEM_BITSET_BITS (MEM_SIZE/MEM_BLOCK_SIZE)
#define MEM_BITSET_BYTES (MEM_BITSET_BITS/8)
#define GETBIT(index) ((blocks[(index)/8]) & (1 << ((index) % 8)))
#define SETBIT(index) (blocks[(index)/8]=blocks[(index)/8]|(1 << ((index) % 8)))
#define CLRBIT(index) (blocks[(index)/8]&=0xff^(1<<((index) % 8)))

void kfree(void *);
void *kmalloc(int);
void *krealloc(void *, int);
void kmeminit();
void printblocks();

#endif

