#include "shell.h"

struct tnode *root;

void shell() {
	char cmd[BUF_LEN];
	int i=0;
	char ch;
	shell_func func;
	
	putstr("Welcome to the (unstable) C Kernel\n");
	
	while(1)
	{
		putstr("> ");
		
		while (i < buffer-2)
		{
			cmd[i] = 0;
			
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
				cmd[i] = ch;
				putch(ch);
				i++;
			}
		}		
		
		if (strcmp(ptr, "exit") == 0)
		{
			putstr("Exiting...\n");
			return;
		}
		else
		{
			func = get_cmd(str);
			if (func == NULL)
			{
				putstr("Invalid Command");
			}
		}
		
		putch('\n');
	}
}
