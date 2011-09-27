/*
 * Basic user authentication for M68K
 */

#include"basic.h"

struct userNode *rootUser;

void *initAuth() {
	rootUser = NULL;
}

int addUser(char* username, char* password) {
	if (username == NULL || password == NULL)
		return -1;

	//Create new user
	struct shellUser *newUser = kmalloc(sizeof(struct shellUser));

	//Encrypt the user's password for storage
	char *encpass = password;
	encpass = memfrob(encpass, strlen(encpass));

	//Add info to struct
	newUser->username = username;
	newUser->password = encpass;

	//Set invalid login to 0
	newUser->invalidLogin = 0;

	//Check if we have any users
	if (rootUser == NULL) {
		//No users
		rootUser = kmalloc(sizeof(struct userNode));
		rootUser->userInfo = newUser;
		rootUser->nextUser = NULL;
	}
	else {
		//Find last user
		struct userNode *end = rootUser;
		while (end->nextUser != NULL) {
			//Check to make user username doesn't exist already
			if (strcmp(end->userInfo->username, newUser->username) == 0)
				return -1;
			end = end->nextUser;
		}

		//Add user
		struct userNode *newNode = kmalloc(sizeof(struct userNode));
		newNode->userInfo = newUser;
		newNode->nextUser = NULL;
		end->nextUser = newNode;
	}

	return 0;
}

struct shellUser *findUser(char* username) {
	if (rootUser == NULL)
		return NULL;

	struct userNode *curUser = rootUser;
	do {
		if (strcmp(curUser->userInfo->username, username) == 0)
			return curUser->userInfo;

		curUser = curUser->nextUser;
	} while(curUser != NULL);
}

int checkLogin(char *username, char *password) {
	struct shellUser *theUser = findUser(username);
	if (findUser == NULL)
		return -1;

	//Encrypt user inputted password to check against stored pass
	password = memfrob(password, strlen(password));

	//Debug
	putstr("\nChecking user login...\nInput password: ");
	putstr(password);
	putstr("\nUser's password: ");
	putstr(theUser->password);
	putstr("\n");

	if (theUser->invalidLogin > AUTH_MAX_LOGINS)
		return 0;

	if (strcmp(theUser->password, password) == 0) {
		resetUser(username);
		return 1;
	}
	else {
		theUser->invalidLogin++;
		return 0;
	}
}

void *resetUser(char *username) {
	struct shellUser *theUser = findUser(username);

	if (theUser == NULL)
		return;

	theUser->invalidLogin = 0;
}
