#ifndef __SHELL_H__
#define __SHELL_H__

#include "screen.h"
#include "string.h"

#define BUF_LEN (64)

typedef void (*shell_func)(int, const char**);

void shell();
void add_cmd(const char *name, shell_func func);

#endif
