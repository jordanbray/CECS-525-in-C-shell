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
	char ptr[BUF_LEN];
	
	putstr("Welcome to the (unstable) C Kernel\n");
	
	while(1)
	{
		putstr("> ");
		getcmd(ptr, BUF_LEN);
		if (strcmp(ptr, "stop") == 0)
		{
			putstr("Exiting...\n");
			return;
		}
		else if (strcmp(ptr, "memtest") == 0)
		{
			putstr("Performing Memory Test\n");
			memtest();
		}
		else if (strcmp(ptr, "errtest") == 0)
		{
			asm ("trap #0\n");
		}
		else if (strcmp(ptr, "help") == 0)
		{
			putstr("Welcome to the Kernel\n\tmemtest\tTest Malloc\n\terrtest\tTest error handling\n\tstop\tExit the shell\n\thelp\tDisplay the Help\n");
		}
		else
		{
			putstr("Echo: ");
			putstr(ptr);
			putch('\n');
		}
	}
}
