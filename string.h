#ifndef __STRING_H__
#define __STRING_H__

void *memcpy(void *dst, void *src, int num);

// GCC may use any of the following at any time
int strlen(const char *s);
char *strdup(const char *s);
void *memcpy(void *dst, void *src, int num);
void *memset(void *dst, int value, int length);
int memcmp(const void* s1, const void* s2, int n);
void *memmove(void *dest, const void *src, int n);
int strcmp(const char *s1, const char *s2);

#define IS_PRINTABLE(ch) ((ch) >= ' ' && (ch) <= '~')

#endif

