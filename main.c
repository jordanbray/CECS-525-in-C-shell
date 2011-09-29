/*
 * M68K C Kernel
 *
 * Written By:
 * Jordan Bray
 * Phillip "Op" Flarsheim
 * Jimmy Murphy
 *
 * Written for the M68K microprocessor that is used at the
 * University of Louisville for the CECS 525 Microcomputer
 * Design class.
 */

#include "screen.h"
#include "kmem.h"
#include "string.h"
#include "shell.h"
#include "tree.h"
#include "commands/commands.h"
#include "auth/authentication.h"

//Main kernel function
void main() {
	//Must initialize the ACIA
	initialize_acia();

	//Init kernel memory
	kmeminit();
	//Login
	initAuth();
	//Add users
	add_users();

	//Welcome message
	putstr("Welcome to the CECS525 (unstable) Educational kernel!\n");
	putstr("Created by: Jordan Bray, Phillip 'Op' Flarsheim and Jimmy Murphy\n\n");

	while (1) {
		//Login message
		putstr("Please login...\n");

		//Check login
		char *user = kmalloc((sizeof(char)*30)+1);
		char *pass = kmalloc((sizeof(char)*30)+1);
		do {
			putstr("\nUsername: ");
			getstr(user, 30);
			putstr("Password: ");
			getpass(pass, 30);
		} while (checkLogin(user, pass) != 1);
		
		//Begin the shell
		shell(user);
		
		kfree(user);
		kfree(pass);
	}
}
