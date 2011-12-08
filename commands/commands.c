/*
 * Helper file to initialize all the commands for the shell.
 *
 * To add a command, simply follow the example as implemented below.
 */

#include "commands.h"

void initialize_commands() {
	add_cmd("echo", echo, echo_help);
	add_cmd("help", help, help_help);
	//add_cmd("test", test, NULL);
	add_cmd("memstatus", memstatus, memstatus_help);
	//Add your commands here
}
