#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "assembly.h"
#include "string.h"

#define STATUS_IRQ      (1 << 7)
#define STATUS_PE       (1 << 6)
#define STATUS_OVRN     (1 << 5)
#define STATUS_FE       (1 << 4)
#define STATUS_CTS      (1 << 3)
#define STATUS_DCD      (1 << 2)
#define STATUS_TDRE     (1 << 1)
#define STATUS_RDRF     (1 << 0)

char getch();
void putch(char ch);
void getstr(char *str, int buffer);
void putstr(const char *str);
void puthexint(int i);

#endif
