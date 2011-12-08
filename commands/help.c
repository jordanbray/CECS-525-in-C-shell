/*
 * This function will go through the command tree,
 * and run the help function for the passed command or
 * enumerate all the possible commands in the shell if
 * no command is passed. 
 */

#include "help.h"
#include "shell.h"

int help(int argc, const char** argv) {
	shell_func func;
	
	//Check if they are trying to find help for a particular command
	if (argc > 1) {
		func = get_help(argv[1]);
		
		if (func == NULL) {
			putstr("Sorry no help exists for the command '");
			putstr(argv[1]);
			putstr("'\n");
		} else {
			func(argc, (const char **)argv);
		}
	} else {
		//List all possible commands
		putstr("Available commands:");
		putoptions(get_commands(""));
		putch('\n');
	}
	return 0;
}

int help_help(int argc, const char** argv) {
	putstr(
"Displays the help page for a particular command\n\
\tUse: help [cmd]\n"
	);
}
