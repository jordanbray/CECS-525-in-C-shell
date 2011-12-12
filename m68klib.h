#ifndef __M68KLIB_H__
#define __M68KLIB_H__

#include <screen.h>

/**
 * Status Register
 * */
typedef struct sr_s {
	unsigned interrupt : 3;
	unsigned __future__0__ : 1;
	unsigned master : 1;
	unsigned supervisor : 1;
	unsigned __future__1__ : 1;
	unsigned trace : 1;
	unsigned carry : 1;
	unsigned overflow : 1;
	unsigned zero : 1;
	unsigned negative : 1;
	unsigned extended : 1;
	unsigned __future__2__ : 3;
} __attribute__((packed)) sr_t;

void __attribute__ ((interrupt)) excep_undef(void);
void __attribute__ ((interrupt)) excep_bus_error(void);
void __attribute__ ((interrupt)) excep_address_error(void);
void __attribute__ ((interrupt)) excep_illegal_instruction(void);
void __attribute__ ((interrupt)) excep_divide_by_zero(void);
void __attribute__ ((interrupt)) excep_chk_instruction(void);
void __attribute__ ((interrupt)) excep_trapv_instruction(void);
void __attribute__ ((interrupt)) excep_privilage_violation(void);
void __attribute__ ((interrupt)) excep_trace(void);

#endif

