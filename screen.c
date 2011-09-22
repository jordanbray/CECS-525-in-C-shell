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

void puthexint(int input) {
	char hex[] = "00000000";
	int i;
	for (i = 0; i < 8; i++) {
		hex[7-i] = (char) (input & 0xf);
		input >>= 4;
		if (hex[7-i] <= 9)
			hex[7-i] += '0';
		else
			hex[7-i] += 'a';
	}
	putstr("0x");
	for (i = 0; hex[i] == '0' && i < 7; i++);
	for (; i < 8; i++) putch(hex[i]);
}
