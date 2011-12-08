#include "memstatus.h"

int memstatus(int argc, const char **argv) {
	printblocks();
}

int memstatus_help(int argc, const char **argv) {
	putstr(
"Displays the status of dynamically allocated memory on the m68k.\n\
'1' means the block is currently in use.\n\
'0' means the block is free.\n"
	);
}
