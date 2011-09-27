/*
 * Echo mode functionality
 */

#include"echo.h"
int echo(int argc, const char** argv) {
	int i;
	for (i=1;i<argc;i++) {
		putstr(argv[i]);
		putch(' ');
	}
	putch('\n');
}
