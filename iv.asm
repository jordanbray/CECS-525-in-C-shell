	.section .text
	dc.l	__asm_stack__,main
	.equ	__asm_stack__,0x4400
	.align 0x400 /* Consume full size of vector table */
