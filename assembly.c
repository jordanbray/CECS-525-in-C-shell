#include "assembly.h"

void __asm_initialize__() {
	asm("move.l #0x8001,%a0\n"
	"move.b #0x3,(%a0)\n"
	"move.b #0x3,1(%a0)\n"
	"move.b #0x19,(%a0)\n"
	"move.b #0x19,1(%a0)\n");
}

void __asm_putch__() {
	asm("movem.l %a0-%a1/%d1-%d2,-(%a7)");
	asm("move.l #0x8001,%a0");
	asm("L1: move.b (%a0),%d1");
	asm("btst #0,%d1");
	asm("beq.s L3");
	asm("L2: move.b (%a0),%d2");
	asm("btst #0,%d2");
	asm("beq L2");
	asm("L3: btst #1,%d1");
	asm("beq L1");
	asm("move.b %d0,2(%a0)");
	asm("movem.l (%a7)+,%a0-%a1/%d1-%d2");
}

void __asm_getch__() {
	/* TODO: write */
}
