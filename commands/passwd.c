/*
 * This function will go through the command tree, and
 * enumerate all the possible commands in the shell. 
 */

#include"passwd.h"

int passwd(int argc, const char** argv) {
	if (argc > 1) {
		putstr("This command does not accept multiple arguments");
		return 0;
	}

	char *user = getCurUser();

	putstr("Changing password for ");
	putstr(user);
	putch('\n');

	//Get current password
	putstr("Enter current password: ");
	char *userPass = kmalloc((sizeof(char)*30)+1);
	getpass(userPass, 30);

	//Ensure current password is correct
	if (checkLogin(user, userPass) != 1) {
		putstr("Error: Current password incorrect.\n");
		kfree(userPass);
		return -1;
	}

	//Get new password
	//TODO: Finish this

	//Done
	return 0;
}
