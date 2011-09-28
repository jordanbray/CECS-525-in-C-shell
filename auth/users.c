#include "users.h"

void add_users()
{
	register_user("root", "root");
	register_user("test", "password");
	
}

void register_user(const char *username, const char *password)
{
	if (addUser(username, password) != 0)
	{
		putstr("Error adding user!\n");
		while(1);
	}
}
