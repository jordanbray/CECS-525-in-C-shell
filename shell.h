#ifndef __SHELL_H__
#define __SHELL_H__

#include "screen.h"
#include "string.h"
#include "tree.h"

#define BUF_LEN (32)

typedef void (*shell_func)(int, const char**);

void shell();
void add_cmd(const char *cmd, shell_func func);
shell_func get_cmd(const char *cmd);
void tab_complete(char *cmd);
char **list_commands(char *cmd);
#endif
