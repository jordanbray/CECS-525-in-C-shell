MEMORY {
	ROM (rx)  : ORIGIN = 0x0000, LENGTH = 16k
	RAM (!rx) : ORIGIN = 0x4000, LENGTH = 4k
}
SECTIONS {
	.reset : {
		iv.o (.text);
	} >ROM
	.text : {
		* (.text*);
		* (.rodata*);
		etext = .; /*End of test section*/
	} >ROM
	/* The C code needs to reference all initialized data at its RAM address,
	   but we want it to be writable.  This causes the .data section to
	   be physically located after the .text section in ROM, but referenced
	   at its RAM address.  Code must copy this data section to RAM at boot.
	 */
	.data : AT (etext) { * (.data); } >RAM
}
