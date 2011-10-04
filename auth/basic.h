#ifndef __BASIC_H__
#define __BASIC_H__

/*
 * Basic user authentication
 */

#include <string.h>
#include <kmem.h>
#include <crypto/crypto.h>

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
int addUser(const char *, const char *);
struct shellUser *findUser(const char *);
int checkLogin(const char *, const char *);
void *resetUser(const char *);
int changePAssword(const char *, const char *);

#endif
