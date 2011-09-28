#ifndef __MD5_H__
#define __MD5_H__

/*
 * MD5 encryption implementation
 */

typedef union uwb {
	unsigned w;
	unsigned char b[4];
} WBunion;

typedef unsigned Digest[4];

void *md5(const char *, int);

#endif
