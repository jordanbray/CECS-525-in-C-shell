void shell() {
	char ptr[BUF_LEN];
	
	putstr("Welcome to the (unstable) C Kernel\n");
	
	while(1)
	{
		putstr("> ");
		getcmd(ptr, SHELL_BUF_LEN);
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
