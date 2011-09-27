#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "string.h"

#define STATUS_IRQ      (1 << 7)
#define STATUS_PE       (1 << 6)
#define STATUS_OVRN     (1 << 5)
#define STATUS_FE       (1 << 4)
#define STATUS_CTS      (1 << 3)
#define STATUS_DCD      (1 << 2)
#define STATUS_TDRE     (1 << 1)
#define STATUS_RDRF     (1 << 0)

void initialize_acia();

void puthexint(int);
void putint(double);
void putstr(const char *);
void putch(char);

void getstr(char *, int);
void getpass(char *, int);
char getch();

#endif
