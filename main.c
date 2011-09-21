#include "assembly.h"
#include "screen.h"

void main() {
	__asm_initialize__();
	pstring("Hello ");
	pstring(" World!!!\n");
	while(1);
}

