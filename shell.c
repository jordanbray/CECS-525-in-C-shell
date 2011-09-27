#include "shell.h"

struct tnode *root;

void getcmd(char *str, int buffer) {
	int i =0;
	char ch;
	
	while (i < buffer-2)
	{
		str[i] = 0;
		
		ch = getch();
		if (ch == '\r') //if enter key is hit stop
		{
			break;
		}
		else if (ch == '\b' || ch == 127)
		{
			putch('\b');
			i--;
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



void tab_complete(char *command, int *length) {
    struct tnode *node = tnode_startswith(root, command);
    struct tnode *min = tnode_searchmin(node);
    struct tnode *max = tnode_searchmax(node);
    char *all = match_beginning(min->key, max->key);
    int i;
    int len = strlen(all);
    for (i = *length; i < *length + len; i++) {
        command[i] = all[i-*length];
    }
    command[i] = 0;
    *length = *length + len;
    kfree(all);
}

void shell() {
	char str[BUF_LEN], ch;
	int i;
	root = NULL;
	shell_func func;
	
	putstr("Welcome to the (unstable) C Kernel\n");
	
	while(1)
	{
		i=0;
		putstr("> ");
		
		while (i < BUF_LEN-1)
		{			
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
			else if (ch == '\t')
			{
				tab_complete(str, &i);
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
		
		if (strcmp(str, "exit") == 0)
		{
			putstr("Exiting...\n");
			return;
		}
		else
		{
			func = get_cmd(str);
			if (func == NULL)
			{
				putstr("Invalid Command: ");
				putstr(str);
				putch('\n');
			}
		}
	}
	
	tnode_destroy(root);
}

void add_cmd(const char *cmd, shell_func func) {
	root = tnode_insert(root, cmd, func);
}

shell_func get_cmd(const char *cmd) {
	shell_func theFunc;
	struct tnode *cmd_node = tnode_search(root, cmd);
	theFunc = cmd_node->value;
	return theFunc;
}
