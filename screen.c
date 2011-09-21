#include "screen.h"

void pstring(const char *str) {
	int i;
	for (i = 0; str[i] != 0; i++)
		putch(str[i]);
}

void putch(char ch) {
	asm ("move.b %0, %%d0\n" :"=r"(ch));
	__asm_putch__();
}

char getch() {
	char ch;
	__asm_getch__();
	asm("move.b %%d0, %0\n" :"=r"(ch));
	return ch;
}

