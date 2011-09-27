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

//Function to test our implementation of malloc
void *test_malloc(int bytes) {
	void *ptr = kmalloc(bytes);
	putstr("Malloc'd and got: ");
	puthexint((int)ptr);
	putch('\n');
	return ptr;
}

//Function to test our implementation of free
void test_free(void *ptr) {
	putstr("Freeing: ");
	puthexint((int)ptr);
	putch('\n');
	kfree(ptr);
}

void memtest() {
	void *p1 = test_malloc(124);
	void *p2 = test_malloc(124);
	void *p3 = test_malloc(124);
    test_free(p1);
    test_free(p2);
    test_free(p3);
}

void test_tree() {
    struct tnode *root = NULL;
    root = tnode_insert(root, "one", ((void*)1));
    root = tnode_insert(root, "two", ((void*)2));
    root = tnode_insert(root, "three", ((void*)3));
    root = tnode_insert(root, "four", ((void*)4));
    root = tnode_insert(root, "five", ((void*)5));
    root = tnode_insert(root, "negative 1", (void*)-1);
    struct tnode *node = tnode_search(root, "four");
    if (((int *)node->value) == ((int *)4))
        putstr("SUCCESS\n");
    else
        putstr("FAILURE\n");
    tnode_destroy(root);

}

//Main kernel function
void main() {
	//Must initialize the ACIA
	initialize_acia();

	//Init kernel memory
	kmeminit();
	
	//Login
	initAuth();
	//Add users
	struct shellUser *testUser = kmalloc(sizeof(struct shellUser));
	char *username = "test";
	char *password = "password";
	testUser->username = username;
	testUser->password = password;
	addUser(testUser);

	//Welcome message
	putstr("Welcome to the CECS525 C shell!\nPlease login...\n");

	//Check login
	char *user = kmalloc((sizeof(char)*30)+1);
	char *pass = kmalloc((sizeof(char)*30)+1);
	do {
		putstr("Username: ");
		getstr(user, 30);
		putstr("Password: ");
		getstr(pass, 30);
	} while (checkLogin(user, pass) != 1);
	
	//Begin the shell
	shell();
	
	//Basically lock the system up when you exit the shell
	while(1);
}
