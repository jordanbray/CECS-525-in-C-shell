#include "assembly.h"

void __asm_initialize__() {
	asm("move.l #0x8001,%a0");
	asm("move.b #0x3,(%a0)");
	asm("move.b #0x3,1(%a0)");
	asm("move.b #0x19,(%a0)");
	asm("move.b #0x19,1(%a0)");
}
