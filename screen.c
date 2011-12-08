/*
 * This file handles the input/output to the screen
 */

#include "screen.h"

#define STATUS_IRQ      (1 << 7)
#define STATUS_PE       (1 << 6)
#define STATUS_OVRN     (1 << 5)
#define STATUS_FE       (1 << 4)
#define STATUS_CTS      (1 << 3)
#define STATUS_DCD      (1 << 2)
#define STATUS_TDRE     (1 << 1)
#define STATUS_RDRF     (1 << 0)

/**
 * ACIA serial controler
 * */
 
typedef struct {
	char pad1;
	char control;
	char pad2;
	char data;
} acia_t;

volatile acia_t *const acia = (acia_t *)0x8000;

void initialize_acia() {
	acia->control = 0x3;
	acia->control = 0x19;
}

void std_putch(char ch) {
	while (!(acia->control & STATUS_TDRE)); //Wait for transmit register empty
	acia->data = ch; //Write character
}

char std_getch() {
	while (!(acia->control & STATUS_RDRF)); //Wait for transmit register empty
	return acia->data; //Read character
}

/**
 * Utility Functions
 * */

void putshort(short input) {
	char buf[5];
	int i = 0;
	
	if (input < 0)
	{
		putch('-');
		input *= -1;
	}
	
	do
	{
		buf[i] = (input % 10) + 48;
		input /= 10;
		i++;
	}
	while (input > 0);
	
	for (; i >= 0; i--)
	{
		putch(buf[i]);
	}
}

void puthex(const void *inptr, int length)
{
	unsigned char *ptr = (unsigned char*)inptr;
	char buf;
	int i;
	
	putstr("0x");
	
	for (i=0; i < length; i++)
	{
		buf = (char)((ptr[i] >> 4) & 0x0F);
		if (buf > 9)
		{
			putch(buf - 10 + 97);
		}
		else
		{
			putch(buf + 48);
		}
		
		buf = (char)(ptr[i] & 0x0F);
		if (buf > 9)
		{
			putch(buf - 10 + 97);
		}
		else
		{
			putch(buf + 48);
		}
	}
}

void putstr(const char *str) {
	int i;
	for (i = 0; str[i] != 0; i++) {
		putch(str[i]);
    }
}

void putch(char ch) {
    if (ch == '\n') {
        std_putch('\r');
        std_putch('\n');
    } else if (ch == '\b') {
        std_putch('\b');
        std_putch(' ');
        std_putch('\b');
    } else if (IS_PRINTABLE(ch) || ch == '\t') {
        std_putch(ch);
    }
}

void getstr(char *str, int buffer) {
	int i=0;
	char ch;
	
	while (i < buffer-1)
	{
		str[i] = 0;
		
		ch = getch();
		if (ch == '\r') //if enter key is hit stop
		{
			break;
		}
		else if (ch == '\b' || ch == 127)
		{
			if (i > 0)
			{
				putch('\b');
				i--;
			}
		}
		else if (IS_PRINTABLE(ch))
		{
			str[i] = ch;
			putch(ch);
			i++;
		}
	}
	
	str[i] = 0;
	putch('\n');
}

void getpass(char *str, int buffer) {
	int i=0;
	char ch;

	while (i < buffer-1) {
		str[i] = 0;

		ch = getch();
		if (ch == '\r')
			break;
		else if (ch == '\b' || ch == 127) {
			if (i>0) {
				putch('\b');
				i--;
			}
		}
		else if (IS_PRINTABLE(ch)) {
			str[i] = ch;
			putch('*');
			i++;
		}
	}

	str[i] = 0;
	putch('\n');
}

char getch() {
	return std_getch();
}
