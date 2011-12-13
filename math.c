#include "math.h"

int __divsi3(int a, int b) {
	return 0;
}

int __modsi3(int a, int b) {
	return 0;
}

int __mulsi3(int a, int b) {
	int result;
	/*__asm__(
		"move.l %1, %%d0\n\t"
		"move.l %2, %%d1\n\t"
		"muls.l %%d0, %%d1\n\t"
		"move.l %%d1, %0"
		: "=r" (result)
		: "r" (a), "r" (b)
		: "%d1", "%d2"
	);*/
	return result;
}
