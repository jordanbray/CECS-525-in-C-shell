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
	int i = 0;
	while(s1[i] == s2[i])
	{
		if (s1[i] == 0)
		{
			return 1;
		}
	}
	
	return 0;
}
