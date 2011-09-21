#include "assembly.h"
#include "screen.h"

void main() {
	char str[10];
	
	__asm_initialize__();
	putstr("Hello ");
	putstr(" World!!!\n");
	
	getstr(str, 10);
	
	putstr("Entering Echo Mode\n");
	while(1)
	{
		putch(getch());
	}
}
