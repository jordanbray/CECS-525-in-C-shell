#include "shell.h"

struct tnode *root;

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
	tnode *cmd = tnode_search(root, cmd);
	theFunc = cmd->value;
	return theFunc;
}
