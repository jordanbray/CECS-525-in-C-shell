#ifndef __BASIC_H__
#define __BASIC_H__

/*
 * Basic user authentication
 */

#include<string.h>
#include<kmem.h>

//Remember: this is 0 indexed
#define AUTH_MAX_LOGINS (2)

struct shellUser {
	char *username;
	char *password;
	int invalidLogin;
};

struct userNode {
	struct shellUser *userInfo;
	struct userNode *nextUser;
};

void *initAuth();
int addUser(char* username, char* password);
struct shellUser *findUser(char *username);
int checkLogin(char *username, char *password);
void *resetUser(char *username);

#endif
