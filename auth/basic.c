/*
 * Basic user authentication for M68K
 */

#include"basic.h"

struct userNode *rootUser;

void *initAuth() {
	rootUser = NULL;
}

int addUser(const char* username, const char* password) {
	if (username == NULL || password == NULL)
		return -1;

	//Create new user
	struct shellUser *newUser = kmalloc(sizeof(struct shellUser));

	//Encrypt the user's password for storage
	char *encpass = strdup(password);
	encpass = memfrob(encpass, strlen(encpass));

	//Add info to struct
	newUser->username = strdup(username);
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

struct shellUser *findUser(const char* username) {
	if (rootUser == NULL)
		return NULL;

	struct userNode *curUser = rootUser;
	do {
		if (strcmp(curUser->userInfo->username, username) == 0)
			return curUser->userInfo;

		curUser = curUser->nextUser;
	} while(curUser != NULL);
	return NULL;
}

int checkLogin(const char *username, const char *passwd) {
	struct shellUser *theUser = findUser(username);
	if (findUser == NULL)
		return -1;

	if (theUser->invalidLogin > AUTH_MAX_LOGINS)
		return 0;

	//Encrypt user inputted password to check against stored pass
	int passlen = strlen(passwd);
	char *password = memfrob(strdup(passwd), passlen);
	if (strcmp(theUser->password, password) == 0) {
		resetUser(username);
		kfree(password);
		return 1;
	}
	else {
		theUser->invalidLogin++;
		kfree(password);
		return 0;
	}
}

void *resetUser(const char *username) {
	struct shellUser *theUser = findUser(username);

	if (theUser == NULL)
		return;

	theUser->invalidLogin = 0;
}
