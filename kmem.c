#include "kmem.h"

unsigned char *blocks;

void printblocks() {
    int i;
    for (i = 0; i < MEM_BITSET_BITS; i++)
        if (GETBIT(i)) putch('1');
        else putch('0');
    putch('\n');
}

void kfree(void *ptr) {
	ptr = ptr - 2;
	int start_index = (((int) ptr) - MEM_START)/MEM_BLOCK_SIZE;
    int num_blocks = *((short *)ptr);
    int i;
    for (i = start_index; i < (start_index + num_blocks); i++)
        CLRBIT(i);
    
	*((int *)ptr) = 0;
}

void *kmalloc(int size) {
	if (size == 0)
		return NULL;
	int needed_blocks = (size + 2 + MEM_BLOCK_SIZE - 1) / MEM_BLOCK_SIZE;
	// this is the same as ceil((size+2)/MEM_BLOCK_SIZE)
	// the + 4 is because I prefix the pointer with the length of itself, and then
	// just return the user the memory address + 2
	unsigned int i;
	int best_index = 0; // best block index from the search
	void *address = NULL;
	int best_length = 0x7fffffff; // best length from the search
	int blocks_inside_free_block = 0;
	for (i = 0; i < MEM_BITSET_BITS; i++) {
		if (GETBIT(i)) { // found a used block
			if (blocks_inside_free_block >= needed_blocks &&
				blocks_inside_free_block < best_length) {
				best_index = i - blocks_inside_free_block;
				best_length = blocks_inside_free_block;
			}
			blocks_inside_free_block = 0;
		} else { // found a free block
			blocks_inside_free_block++;
		}
	}
	// all blocks checked, and smallest available block that fits size in it
	// has been chosen
	if (best_length == 0x7fffffff) {
		putstr("No memory left!\n");
		return NULL; // no blocks available
	}
	address = ((void *) (MEM_START + best_index*MEM_BLOCK_SIZE));
	for (i = best_index; i < best_index + needed_blocks; i++)
		SETBIT(i);
	*((short *)address) = needed_blocks;
	address = ((void *) ((int)address) + 2);
	return address;
}

void *free_and_realloc(void *ptr, int size) {
	void *ret = kmalloc(size);
	short copy_size = ((short *) ((((int)ptr)-2) * MEM_BLOCK_SIZE));
	copy_size = copy_size > size ? size : copy_size;
	memcpy(ret, ptr, copy_size);
	kfree(ptr);
	return ret;
}

void *krealloc(void *ptr, int size) {
	return free_and_realloc(ptr, size);
	/* TODO: make this better... */
}

void kmeminit() {
	unsigned int needed_blocks = (MEM_BITSET_BYTES+MEM_BLOCK_SIZE-1)/MEM_BLOCK_SIZE;
	unsigned int i;
	blocks = (unsigned char *)MEM_START;
	for (i = 0; i < needed_blocks; i++)
		SETBIT(i);
	for (; i < MEM_BITSET_BITS; i++)
		CLRBIT(i);
	SETBIT(MEM_BITSET_BITS-1);
}
