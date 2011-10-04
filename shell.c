/*
 * 68K Shell
 *
 * Features:
 * Tab completion
 * Easily add functions
 * More to come...
 */

#include "shell.h"

struct tnode *root;
char *curUser;

void print_command_tree() {
	tnode_print(root, 0);
}

struct linked_list *get_commands(char *command) {
	struct linked_list *commands = NULL;
	tnode_startswith(root, &commands, command);
	return commands;
}

void putoptions(struct linked_list *options)
{
	if (options == NULL)
	{
		return;
	}
	
	putstr("\n\t");
	putstr((char*)options->value);
	
	putoptions(options->next);
	kfree(options);
}

int add_next_character(char *command, struct linked_list *commands, int *length) {
	while (commands->next) {
		if (((char *)commands->value)[*length] != ((char *) commands->next->value)[*length])
			return 0; // stop
		commands = commands->next;
	}
	if (((char *)commands->value)[*length] == 0) {
		command[*length] = ' ';
		command[*length+1] = 0;
		*length += 1;
		return 0;
	}
	command[*length] = ((char *)commands->value)[*length];
	command[*length+1] = 0;
	*length += 1;
	return 1; // continue
}

void tab_complete(char *command, int *length) {
	struct linked_list *commands = get_commands(command);
	if (commands == NULL) return;
	while (add_next_character(command, commands, length));
	while (commands) {
		kfree(commands); // yes, I know this is ugly
		commands = commands->next; // but I'm doing it anyways
	}
}

void initialize_shell() {
	root = NULL;
	initialize_commands();
}

void shell(char* user) {
	char **argv, str[BUF_LEN], ch;
	int i, j, argc;
	shell_func func;

	curUser = user;
	
	while(1)
	{
		i = 0;
		putstr(curUser);
		putstr("> ");
		
		while (i < BUF_LEN-1)
		{
			str[i] = 0;
			
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
				if (strchr(str, ' ') == NULL)
				{
					j = i;
					tab_complete(str, &j);
					if (i == j)
					{
						putoptions(get_commands(str));
						putch('\n');
						putstr(curUser);
						putstr("> ");
						putstr(str);
					}
					else
					{
						for (; i < j; i++)
						{
							putch(str[i]);
						}
					}
				}
				
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
			break;
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
				func(argc, (const char **)argv);
			}
			
			kfree(argv);
		}
	}
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
			ret[index++] = &params[i+1];
		}
	}
	*length = space_count+1;
	return ret;
}

char *getCurUser() {
	return curUser;
}
