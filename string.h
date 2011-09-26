#ifndef __STRING_H__
#define __STRING_H__

void *memcpy(void *dst, void *src, int num);

// GCC may use any of the following at any time
void *memset(void *dst, int value, int length); // TODO: write
int memcmp(void *a, void *b, int length); // TODO: write
int memmove(void *a, void *b, int length); // TODO: write


int strcmp(const char *s1, const char *s2);

#endif

