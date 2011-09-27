#ifndef __MEMFROB_H__
#define __MEMFROB_H__

/*
 * Trivial encryption based on GNU C's memfrob command
 */

#include<kmem.h>

void *memfrob(void *mem, int length);

#endif
