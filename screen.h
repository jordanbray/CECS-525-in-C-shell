#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "assembly.h"

char getch();
void putch(char ch);
void getstr(char *str, int buffer);
void putstr(const char *str);
void puthexint(int i);

#endif
