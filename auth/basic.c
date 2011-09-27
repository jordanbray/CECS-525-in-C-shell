/*
 * Basic user authentication for M68K
 */

#include"basic.h"

struct userList *rootUser;

void *initAuth() {
	rootUser = NULL;
}

int addUser(struct shellUser *newUser) {
	if (newUser == NULL || newUser->username == NULL || newUser->password == NULL)
		return -1;

	//Set invalid login to 0 just in case
	newUser->invalidLogin = 0;

	//Check if we have any users
	if (rootUser == NULL) {
		//No users
		rootUser = newUser;
	}
	else {
		//Find last user
		struct userList *end = rootUser;
		while (end->nextUser != NULL) {
			//Check to make user username doesn't exist already
			if (strcmp(end->userInfo->username, newUser->username) == 0)
				return -1;
			end = end->nextUser;
		}

		//Add user
		end->nextUser = newUser;
	}

	return 0;
}

struct shellUser *findUser(char* username) {
	if (rootUser == NULL)
		return NULL;

	struct userList *curUser = rootUser;
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

	if (theUser->invalidLogin > AUTH_MAX_LOGINS)
		return 0;

	if (strcmp(theUser->password, password) == 0)
		return 1;
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
