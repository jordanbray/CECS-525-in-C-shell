/*
 * String functions, and some memory movement functions
 */

#include "string.h"

int strstartswith(const char *str, const char *start) {
	return memcmp(str, start, strlen(start));
}

int chars_matched(const char *s1, const char *s2) {
	int len = 0;
	for (; *s1 == *s2; len++, s1++, s2++);
	return len;
}
char *match_most_of(const char *s1, const char *s2) {
	int s1len = strlen(s1);
	int s2len = strlen(s2);
	if (s1len > s2len) {
		return match_beginning(s1, s2);
	} else {
		return match_beginning(s2, s1);
	}
}


char *match_beginning(const char *s1, const char *s2) {
	int s1len = strlen(s1);
	int s2len = strlen(s2);
	int len = s1len < s2len ? s1len : s2len;
	char *ret = kmalloc(len+1);
	int i;
	for (i = 0; i < len && s1[i] == s2[i]; i++) {
		ret[i] = s1[i];
	}
	ret[i] = 0;
	return ret;
}


int strlen(const char *s) {
	const char *old = s;
	while (*s) {
		s++;
	}
	return (s - old);
}

 char *strchr(const char *s, int c)
 {
	while (*s != '\0' && *s != (char)c)
	{
		s++;
	}
	return ((*s == c) ? (char *) s : NULL);
 }

 char *strstr(const char *haystack, const char *needle)
 {
	int needlelen;
	if (*needle == '\0')
	{
		return (char *) haystack;
	}
	needlelen = strlen(needle);
	for (; (haystack = strchr(haystack, *needle)) != NULL; haystack++)
	{
		if (strncmp(haystack, needle, needlelen) == 0)
		{
			return (char *) haystack;
		}
	}
	return NULL;
 }

char *strdup(const char *s) {
	int len = strlen(s);
	char *ret = kmalloc(len + 1);
	return memcpy(ret, (void *) s, len+1);
}

void *memcpy(void *dst, const void *src, int num) {
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

int memcmp(const void* s1, const void* s2,int n)
{
	const unsigned char *p1 = s1, *p2 = s2;
	while(n--) {
		if( *p1 != *p2 ) {
			return *p1 < *p2 ? -1 : 1;
		}
		else {
			*p1++,*p2++;
		}
	}
	return 0;
}

void *memmove(void *dst, const void *src, int size)
{
	char **to = dst;
	const char **from = (const char **) src;
	int i,diff;
	
	if(*from==*to)
		return dst;
	else if(*from>*to)
	{
		diff=*from-*to; 
		for(i=diff;i<=size+diff-1;i++)
		{
			(*to)[i-diff] = (*from)[(i-diff)];
		}
	}
	else
	{
		diff=*to-*from; 
		for(i=size+diff-1;i>=diff;i--)
		{
			(*to)[(i-diff)] = (*from)[(i-diff)]; 
		}
	}
	return dst;
}

void *memchr(void *ptr, int value, size_t num) {
	int i;

	for (i=0;i<num;i++) {
		if (ptr[i] == value)
			return ptr[i];
	}

	return NULL;
}

const void *memchr(const void *ptr, int value, size_t num) {
	int i;

	for (i=0;i<num;i++) {
		if (ptr[i] == value)
			return ptr[i];
	}

	return NULL;
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

int strncmp(const char *s1, const char *s2, int n)
 {
     unsigned char uc1, uc2;
     /* Nothing to compare?  Return zero.  */
     if (n == 0)
         return 0;
     /* Loop, comparing bytes.  */
     while (n-- > 0 && *s1 == *s2) {
         /* If we've run out of bytes or hit a null, return zero
            since we already know *s1 == *s2.  */
         if (n == 0 || *s1 == '\0')
             return 0;
         s1++;
         s2++;
     }
     uc1 = (*(unsigned char *) s1);
     uc2 = (*(unsigned char *) s2);
     return ((uc1 < uc2) ? -1 : (uc1 > uc2));
 }

char *strcpy(char *destination, const char *source) {
	int i, len = strlen(source);
	for (i=0;i<len;i++) {
		destination[i] = source[i];
	}
	destination[len] = 0;
	
	return destination;
}

char *strncpy(char *destination, const char *source, size_t num) {
	int i;
	for (i=0;i<num;i++) {
		destination[i] = source[i];
	}
	destination[num] = 0;

	return destination;
}

char *strcat(char *destination, const char *source) {
	int i = 0;

	while (destination[i] != 0)
		i++;

	while ((destination[i] = source[i]) != 0)
		i++;

	destination[i] = 0;

	return destination;
}

char *strncat(char *destination, const char *source, size_t num) {
	int i = 0;

	while (destination[i] != 0)
		i++;

	while (i < num && source[i] != 0) {
		destination[i] = source[i];
		i++;
	}

	destination[i] = 0;

	return destination;
}

int strtoint(const char *str)
{
	int i;
	int value = 0;
	
	for (i=0; i < strlen(str); i++)
	{
		value *= 10;
		value += (str[i] - 48);
	}
	
	return value;
}
