/*
 * Echo mode functionality
 */

#include"echo.h"
#include<string.h>
#include<screen.h>
#include<shell.h>

int echoMode(int argc, const char** argv) {
	int i;
	for (i=1;i<argc;i++) {
		putstr(argv[i]);
	}
}
