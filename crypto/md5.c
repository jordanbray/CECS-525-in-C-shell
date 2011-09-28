/*
 * M68K MD5 implementation
 *
 * Code borrowed from http://rosettacode.org/wiki/MD5#C
 */

#include"md5.h"

unsigned f0( unsigned abcd[] ){
	return ( abcd[1] & abcd[2]) | (~abcd[1] & abcd[3]);
}
 
unsigned f1( unsigned abcd[] ){
	return ( abcd[3] & abcd[1]) | (~abcd[3] & abcd[2]);
}
 
unsigned f2( unsigned abcd[] ){
	return  abcd[1] ^ abcd[2] ^ abcd[3];
}
 
unsigned f3( unsigned abcd[] ){
	return abcd[2] ^ (abcd[1] |~ abcd[3]);
}
 
typedef unsigned (*DgstFctn)(unsigned a[]);

unsigned rol( unsigned v, short amt )
{
	unsigned  msk1 = (1<<amt) -1;
	return ((v>>(32-amt)) & msk1) | ((v<<amt) & ~msk1);
}

void *md5(const char *mem, int length) {
	static Digest h0 = { 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476 };
	static DgstFctn ff[] = { &f0, &f1, &f2, &f3 };
	static short M[] = { 1, 5, 3, 7 };
	static short O[] = { 0, 1, 5, 0 };
	static short rot0[] = { 7,12,17,22};
	static short rot1[] = { 5, 9,14,20};
	static short rot2[] = { 4,11,16,23};
	static short rot3[] = { 6,10,15,21};
	static short *rots[] = {rot0, rot1, rot2, rot3 };
	static unsigned kspace[64];
	static unsigned *k;

	static Digest h;
	Digest abcd;
	DgstFctn fctn;
	short m, o, g;
	unsigned f;
	short *rotn;
	union {
	unsigned w[16];
	char     b[64];
	}mm;
	int os = 0;
	int grp, grps, q, p;
	unsigned char *msg2;
}
