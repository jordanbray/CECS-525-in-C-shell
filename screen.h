#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "string.h"

void initialize_acia();

void puthex(const void *, int);
void putshort(short);
void putstr(const char *);
void putch(char);

void getstr(char *, int);
void getpass(char *, int);
char getch();

#endif
