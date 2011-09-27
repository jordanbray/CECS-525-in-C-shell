#ifndef __BASIC_H__
#define __BASIC_H__

/*
 * Basic user authentication
 */

#include<string.h>

#define AUTH_MAX_LOGINS (3)

struct shellUser {
	char *username;
	char *password;
	int invalidLogin;
};

struct userList {
	struct shellUser *userInfo;
	struct userList *nextUser;
};

void *initAuth();
int addUser(struct shellUser *newUser);
struct shellUser *findUser(char *username);
int checkLogin(char *username, char *password);
void *resetUser(char *username);

#endif
