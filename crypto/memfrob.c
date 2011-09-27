/*
 * Trivial encryption implementation
 */

#include"memfrob.h"

void *memfrob(void *mem, int length) {
	int i;
	void *enc_mem = kmalloc(length+1);

	for (i=0;i<length;i++) {
		enc_mem[i] = mem[i] ^ 0x26;
	}

	return enc_mem;
}
