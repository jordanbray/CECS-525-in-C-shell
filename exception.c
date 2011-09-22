#include "screen.h"

/* The interrupt attribute tells GCC to save any clobbered registers
 * and perform an RTE instead of RTS to return */

void __attribute__ ((interrupt)) excep_undef(void)
{
	putstr("Unhandled exception!\n");
}
