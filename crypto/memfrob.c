/*
 * Trivial encryption implementation
 */

#include"memfrob.h"

void *memfrob(unsigned char *mem, int length) {
	int i;
	unsigned char *enc_mem = kmalloc(length);

	for (i=0;i<length;i++) {
		enc_mem[i] = mem[i] ^ 0x26;
	}

	return enc_mem;
}
