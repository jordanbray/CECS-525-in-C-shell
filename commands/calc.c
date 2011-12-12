#include "calc.h"

short evaluate(short num1, char oper, short num2)
{
	int result = 0;
	switch(oper)
	{
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
	}
	return result;
}

int calc(int argc, const char **argv)
{
	if (argc == 4)
	{
		putshort(evaluate((short)strtoint(argv[1]), argv[2][0], (short)strtoint(argv[3])));
		putch('\n');
	}
}

int calc_help(int argc, const char **argv)
{
	putstr(
"A simple four function calculator. Can either be used directly through the command line or\
in interactive mode by only typing calc.\n\
\tUse: calc\n\
\tUse: calc [num1] [operator] [num2]\n"
	);
}
