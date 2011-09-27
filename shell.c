#include "shell.h"

struct tnode *root;

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
	char **argv, str[BUF_LEN], ch;
	int i, argc;
	root = NULL;
    initialize_commands();
	shell_func func;
	
	putstr("Welcome to the (unstable) C Kernel\n");
	
	while(1)
	{
		i = 0;
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
			argc = i;
			argv = parse_parameters(str, &argc);
			func = get_cmd(argv[0]);
			if (func == NULL)
			{
				putstr("Invalid Command: ");
				putstr(argv[0]);
				putch('\n');
			}
			else
			{
				func(argc, argv);
			}
			
			kfree(argv);
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
	if (cmd_node == NULL)
		return NULL;
	theFunc = cmd_node->value;
	return theFunc;
}

char **parse_parameters(char *params, int *length) {
    int space_count = 0;
    int i;
    for (i = 0; i < *length; i++)
        if (params[i] == ' ')
            space_count++;
    char **ret = kmalloc(space_count+1);
    ret[0] = params;
    int index = 1;
    for (i = 0; i < *length; i++) {
        if (params[i] == ' ') {
            params[i] = '\0';
            ret[index++] = &params[i];
        }
    }
    *length = space_count+1;
    return ret;
}

