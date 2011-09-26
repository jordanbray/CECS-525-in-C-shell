#include "string.h"

int strlen(const char *s) {
	const char *old = s;
	while (*s) {
		s++;
	}
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

int memcmp(const void* s1, const void* s2,int n)
{
	const unsigned char *p1 = s1, *p2 = s2;
	while(n--) {
		if( *p1 != *p2 ) {
			return *p1 - *p2;
		}
		else {
			*p1++,*p2++;
		}
	}
	return 0;
}

void *mymove(void *dst, const void *src, int size)
{
    char **to = dst;
    const char **from = src;
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
