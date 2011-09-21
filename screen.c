#include "screen.h"

void putstr(const char *str) {
	int i;
	for (i = 0; str[i] != 0; i++)
		putch(str[i]);
}

void putch(char ch) {
	asm ("move.b %0, %%d0\n" :"=r"(ch));
	__asm_putch__();
}

void getstr(char *str, int buffer) {
	int i;
	char ch;
	
	for (i=0; i < buffer-1; i++)
	{
		ch = getch();
		if (ch == 13) //if enter key is hit stop
		{
			break;
		}
		str[i] = ch;
		putch(ch);
	}
	str[i+1] = 0;
	putch('\n');
}

char getch() {
	char ch;
	__asm_getch__();
	asm("move.b %%d0, %0\n" :"=r"(ch));
	return ch;
}

