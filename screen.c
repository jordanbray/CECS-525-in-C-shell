/*
 * This file handles the input/output to the screen
 */

#include "screen.h"

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
	char ch;
	while (!(acia->control & STATUS_RDRF)); //Wait for transmit register empty
	return acia->data; //Read character
	return ch;
}

/**
 * Utility Functions
 * */

void putshort(short input) {
	char buff[5];
	int i = 0;
	int isNeg = (input < 0);
	
	if (isNeg)
	{
		putch('-');
		input *= -1;
	}
	
	do
	{
		buff[i] = (input % 10) + 48;
		input /= 10;
		i++;
	}
	while (input > 0);
	
	for (; i >=0; i--)
	{
		putch(buff[i]);
	}
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
			hex[7-i] += 'a' - 10;
	}
	putstr("0x");
	for (i = 0; hex[i] == '0' && i < 7; i++);
	for (;i < 8; i++)putch(hex[i]);
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
