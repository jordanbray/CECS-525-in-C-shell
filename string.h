#ifndef __STRING_H__
#define __STRING_H__

#include <kmem.h>

int strlen(const char *);
char *strdup(const char *);
char *strchr(const char *, int);
char *strstr(const char *, const char *);
void *memcpy(void *, const void *, int);
void *memset(void *, int, int);
int memcmp(const void *, const void *, int);
void *memmove(void *, const void *, int);
void *memchr(const void *, int, int);
int strcmp(const char *, const char *);
int strncmp(const char *, const char *, int);
char *strcpy(char *, const char *);
char *strncpy(char *, const char *, int);
char *strcat(char *, const char *);
char *strncat(char *, const char *, int);
int strstartswith(const char *, const char *);
char *match_beginning(const char *, const char *);
int strtoint(const char *);
int strcspn (const char *, const char *);
char *strpbrk (const char *, const char *);
char *strrchr (const char *, int);
int strspn (const char *, const char *);
char *strtok(char *, const char *);

int chars_matched(const char *s1, const char *s2);
#define IS_PRINTABLE(ch) ((ch) >= ' ' && (ch) <= '~')

#endif

