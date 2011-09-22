#include "assembly.h"
#include "screen.h"
#include "kmem.h"

void *test_malloc(int bytes) {
	void *ptr = kmalloc(bytes);
	putstr("Memory address: ");
	puthexint((int)ptr);
	putch('\n');
	return ptr;
}

void test_free(void *ptr) {
	putstr("Freeing: ");
	puthexint((int)ptr);
	putch('\n');
	kfree(ptr);
}

void memtest() {
	void *p1 = test_malloc(124);
	void *p2 = test_malloc(124);
	test_free(p1);
	void *p3 = test_malloc(124);

}

void shell() {
	char ptr[64];
	
	putstr("Welcome to the (unstable) C Kernel\n");
	
	while(1)
	{
		putstr("> ");
		getstr(ptr, 64);
		if (strcmp(ptr, "STOP"))
		{
			putstr("Exiting...\n");
			return;
		}
		else if (strcmp(ptr, "MEMTEST"))
		{
			putstr("Performing Memory Test\n");
			memtest();
		}
		else if (strcmp(ptr, "ERRTEST"))
		{
			asm ("trap #0\n");
		}
		else
		{
			putstr("Echo: ");
			putstr(ptr);
			putch('\n');
		}
	}
}

void main() {
	__asm_initialize__();
	kmeminit();
	
	shell();
	
	while(1);
}
