#include "math.h"

int __divsi3(int a, int b) {
	int result;
	__asm__(
		"move.w %2, %%d0\n\t"
		"move.w %1, %%d1\n\t"
		"divs %%d0, %%d1\n\t"
		"move.w %%d1, %0"
		: "=r" (result)
		: "r" (a), "r" (b)
		: "%d0", "%d1"
	);
	return result;
}

int __modsi3(int a, int b) {
	int result;
	__asm__(
		"move.w %2, %%d0\n\t"
		"move.w %1, %%d1\n\t"
		"divs %%d0, %%d1\n\t"
		"swap %%d1\n\t"
		"move.w %%d1, %0"
		: "=r" (result)
		: "r" (a), "r" (b)
		: "%d0", "%d1"
	);
	return result;
}

int __mulsi3(int a, int b) {
	int result;
	__asm__(
		"move.w %1, %%d0\n\t"
		"move.w %2, %%d1\n\t"
		"muls %%d0, %%d1\n\t"
		"move.l %%d1, %0"
		: "=r" (result)
		: "r" (a), "r" (b)
		: "%d0", "%d1"
	);
	return result;
}
