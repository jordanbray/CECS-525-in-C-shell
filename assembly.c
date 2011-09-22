#include "assembly.h"

void __asm_initialize__() {
	asm("move.l #0x8001,%a0\n"
	"move.b #0x3,(%a0)\n"
	"move.b #0x3,1(%a0)\n"
	"move.b #0x19,(%a0)\n"
	"move.b #0x19,1(%a0)\n");
}

void __asm_getch__() {
	asm("movem.l %d1/%a1,-(%a7)");	//Save working registers
	asm("move.l #0x8001,%a1");		//Get address of ACIA in A1
	asm("CON_1: move.b (%a1),%d1");	//Read ACIA status 
	asm("btst #0,%d1");				//Test RDRF 
	asm("beq CON_1");				//Repeat until RDRF true 
	asm("move.b 2(%a1),%d0");		//Read input from ACIA 
	asm("movem.l (%a7)+,%a1/%d1");	//Restore working registers 
}
