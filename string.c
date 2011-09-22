#include "string.h"

void *memcpy(void *dst, void *src, int num) {
	char *cd = ((char *)dst);
	char *cs = ((char *)src);
	int i;
	for (i = 0; i < num; i++)
		cd[i] = cs[i];
	return dst;
}

