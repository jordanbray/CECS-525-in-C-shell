.data
	.org	0x0
	dc.l	__asm_stack__,main
	.equ	__asm_stack__,0x4200
	.section .text
	dc.l	__asm_stack__,main
	dc.l	excep_bus_error
	dc.l	excep_address_error
	/* 4 */
	dc.l	excep_illegal_instruction
	dc.l	excep_divide_by_zero
	dc.l	excep_chk_instruction
	dc.l	excep_trapv_instruction
	/* 8 */
	dc.l	excep_privilage_violation
	dc.l	excep_trace
	.org (24*4)
	dc.l	excep_undef /* Spurious */
	dc.l	excep_undef /* IRQ 1 */
	dc.l	excep_undef /* IRQ 2 */
	dc.l	excep_undef /* IRQ 3 */
	dc.l	excep_undef /* IRQ 4 */
	dc.l	excep_undef /* IRQ 5 */
	dc.l	excep_undef /* IRQ 6 */
	dc.l	excep_undef /* IRQ 7 */

	/* Traps */
	dc.l	excep_undef, excep_undef, excep_undef, excep_undef
	dc.l	excep_undef, excep_undef, excep_undef, excep_undef
	dc.l	excep_undef, excep_undef, excep_undef, excep_undef
	dc.l	excep_undef, excep_undef, excep_undef, excep_undef

	/* There are more vectors down here, but we dont need them and can use
	   the extra space for code storage */
