/*
 * This function will go through the command tree, and
 * enumerate all the possible commands in the shell. 
 */

#include"help.h"

int help(int argc, const char** argv) {
	//Check if they are trying to find help for a particular command
	if (argc > 1) {
		//Looking for help on a particular command, found in argv[1]
		putstr("This functionality is currently not implemented.\n");
		return 0;
	}

	//Looking for all the commands
}
