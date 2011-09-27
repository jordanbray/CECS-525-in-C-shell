#ifndef __BASIC_H__
#define __BASIC_H__

/*
 * Basic user authentication
 */

#include<string.h>

struct shellUser {
	char *username;
	char *password;
	int invalidLogin;
};

#endif
