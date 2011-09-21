	.equ	__asm_stack__,0x4400
	.section .text
	dc.l	__asm_stack__,main
	dc.l	excep_undef
	dc.l	excep_undef
	/* 4 */
	dc.l	excep_undef
	dc.l	excep_undef
	dc.l	excep_undef
	dc.l	excep_undef
	/* 8 */
	dc.l	excep_undef
	dc.l	excep_undef
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
