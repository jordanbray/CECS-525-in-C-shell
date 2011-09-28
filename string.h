#ifndef __STRING_H__
#define __STRING_H__
#include "kmem.h"


// GCC may use any of the following at any time
int strlen(const char *);
char *strdup(const char *);
char *strchr(const char *, int);
char *strstr(const char *, const char *);
void *memcpy(void *, const void *, int);
void *memset(void *, int, int);
int memcmp(const void *, const void *, int);
void *memmove(void *, const void *, int);
int strcmp(const char *, const char *);
int strncmp(const char *, const char *, int);
char *strcpy(char *, const char *);
int strstartswith(const char *, const char *);
char *match_beginning(const char *, const char *);
int strtoint(const char *);

#define IS_PRINTABLE(ch) ((ch) >= ' ' && (ch) <= '~')

#endif

