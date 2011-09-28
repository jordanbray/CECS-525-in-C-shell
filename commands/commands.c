/*
 * Helper file to initialize all the commands for the shell.
 *
 * To add a command, simply follow the example as implemented below.
 */

#include "commands.h"

void initialize_commands() {
	add_cmd("echo", echo);
	add_cmd("help", help);
	add_cmd("test", test);

	//Add your commands here
}
