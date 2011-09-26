#include "string.h"

void *memcpy(void *dst, void *src, int num) {
	char *cd = ((char *)dst);
	char *cs = ((char *)src);
	int i;
	for (i = 0; i < num; i++)
		cd[i] = cs[i];
	return dst;
}

int strcmp(const char *s1, const char *s2)
{
    for(; *s1 == *s2; ++s1, ++s2)
    {
        if(*s1 == 0)
        {
            return 0;
		}
	}
    return *(unsigned char *)s1 < *(unsigned char *)s2 ? -1 : 1;
}
