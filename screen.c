#include "screen.h"

typedef struct {
	char pad1;
	char control;
	char pad2;
	char data;
} acia_t;

volatile acia_t *const acia = (acia_t *)0x8000;

#define STATUS_IRQ      (1 << 7)
#define STATUS_PE       (1 << 6)
#define STATUS_OVRN     (1 << 5)
#define STATUS_FE       (1 << 4)
#define STATUS_CTS      (1 << 3)
#define STATUS_DCD      (1 << 2)
#define STATUS_TDRE     (1 << 1)
#define STATUS_RDRF     (1 << 0)

void putstr(const char *str) {
	int i;
	for (i = 0; str[i] != 0; i++)
		putch(str[i]);
}

void putch(char ch) {
	while (!(acia->control & STATUS_TDRE)); //Wait for transmit register empty
	acia->data = ch; //Write character
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

