#include "string.h"

int strlen(const char *s) {
	const char *old = s;
	while (*s)
		s++;
	return (s - old);
}

char *strdup(const char *s) {
	int len = strlen(s);
	char *ret = kmalloc(len + 1);
	return memcpy(ret, s, len+1);
}

void *memcpy(void *dst, void *src, int num) {
	char *dp = dst;
	const char *sp = src;
	while (num--) {
		*dp++ = *sp++;
	}
	return dst;
}

void *memset(void *dst, int value, int length) {
	unsigned char *p=dst;
	while(length--) {
		*p++ = (unsigned char)value;
	}

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
