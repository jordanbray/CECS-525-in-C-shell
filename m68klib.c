#include "m68klib.h"

void __attribute__ ((interrupt)) excep_undef(void) {
	putstr("Unhandled exception!\n");
	asm("move.l #0x4200,%sp"); //Reset stack pointer to avoid memory leaks
    main();
}

void __attribute__ ((interrupt)) excep_bus_error(void) {
	putstr("Bus Error!\n");
	asm("move.l #0x4200,%sp"); //Reset stack pointer to avoid memory leaks
    main();
}

void __attribute__ ((interrupt)) excep_address_error(void) {
	putstr("Address Error!\n");
	asm("move.l #0x4200,%sp"); //Reset stack pointer to avoid memory leaks
    main();
}

void __attribute__ ((interrupt)) excep_illegal_instruction(void) {
	putstr("Illegal Instruction!\n");
	asm("move.l #0x4200,%sp"); //Reset stack pointer to avoid memory leaks
    main();
}

void __attribute__ ((interrupt)) excep_divide_by_zero(void) {
	putstr("Divide By Zero!\n");
	asm("move.l #0x4200,%sp"); //Reset stack pointer to avoid memory leaks
    main();
}

void __attribute__ ((interrupt)) excep_chk_instruction(void) {
	putstr("CHK instruction!\n");
	asm("move.l #0x4200,%sp"); //Reset stack pointer to avoid memory leaks
    main();
}

void __attribute__ ((interrupt)) excep_trapv_instruction(void) {
	putstr("TRAPV exception!\n");
	asm("move.l #0x4200,%sp"); //Reset stack pointer to avoid memory leaks
    main();
}

void __attribute__ ((interrupt)) excep_privilage_violation(void) {
	putstr("Privilage Violation!\n");
	asm("move.l #0x4200,%sp"); //Reset stack pointer to avoid memory leaks
    main();
}

void __attribute__ ((interrupt)) excep_trace(void) {
	putstr("Trace!\n");
	asm("move.l #0x4200,%sp"); //Reset stack pointer to avoid memory leaks
    main();
}
