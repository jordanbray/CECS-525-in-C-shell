#ifndef __SHELL_H__
#define __SHELL_H__

#include <screen.h>
#include <string.h>
#include <tree.h>
#include <kmem.h>

#define BUF_LEN (64)

typedef int (*shell_func)(int, const char**);
typedef struct _shell_cmd shell_cmd;

struct _shell_cmd {
	shell_func run;
	shell_func help;
};

void shell(char *);
void add_cmd(const char *, shell_func, shell_func);
shell_func get_cmd(const char *);
shell_func get_help(const char *);
void tab_complete(char *, int *);
char **list_commands(char *);
char **parse_parameters(char *, int *);

#endif
