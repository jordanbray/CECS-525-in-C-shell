#include "calc.h"

int evaluate(int num1, char oper, int num2) {
	int result = 0;
	switch(oper) {
		case '+':
			result = num1 + num2;
			break;
		case '-':
			result = num1 - num2;
			break;
		case '*':
			result = num1 * num2;
			break;
		case '/':
			result = num1 / num2;
			break;
		case '%':
			result = num1 % num2;
			break;
	}
	return result;
}

int calc(int argc, const char **argv) {
	if (argc == 4) {
		putshort((short)evaluate(strtoint(argv[1]), argv[2][0], strtoint(argv[3])));
		putch('\n');
	} else {
		putstr("Invalid parameters see help for assistance\n");
	}
}

int calc_help(int argc, const char **argv) {
	putstr(
"A simple calculator, supports '+', '-', '*', '/', and '%'.\n\
\tUse: calc [num1] [operator] [num2]\n"
	);
}
