#include "echo.h"

/**
 * Echos text typed by the user
 * */
int echo(int argc, const char** argv) {
	int i;
	for (i=1;i<argc;i++) {
		putstr(argv[i]);
		putch(' ');
	}
	putch('\n');
}

int echo_help(int argc, const char** argv) {
	putstr(
"Echos text back to the terminal\n\
\tUse: echo [text]\n"
	);
}
