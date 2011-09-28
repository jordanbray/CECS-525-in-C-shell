#include"spow.h"

short int spow(short int base, const short int pow) {
	if (pow == 0)
		return 1;
	else if (pow == 1)
		return base;
	else {
		int i;
		for (i=0;i<pow;i++) {
			base *= base;
		}

		return base;
	}
}
