/*
 * This function will go through the command tree, and
 * enumerate all the possible commands in the shell. 
 */

#include"help.h"
#include"shell.h"

int help(int argc, const char** argv) {
	//Check if they are trying to find help for a particular command
	if (argc > 1) {
		//Looking for help on a particular command, found in argv[1]
		putstr("This functionality is currently not implemented.\n");
		return 0;
	}

	//Looking for all the commands
	putstr("Available commands:");
	putoptions(get_commands(""));
	putch('\n');

	//TODO: Fix this!
	//Do some looping of some kind
	//Output each command

	//Done
	return 0;
}
