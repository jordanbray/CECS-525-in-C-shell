/*
 * Trivial encryption implementation
 */

#include"memfrob.h"

void *memfrob(void *mem, int length) {
	int i;
	unsigned char *memory = (unsigned char*)mem;

	for (i=0;i<length;i++) {
		memory[i] ^= 0xee;
	}

	return memory;
}
