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

void main() {
	__asm_initialize__();
	kmeminit();
	putstr("Hello ");
	putstr(" World!!!\n");
	
	putstr("Performing Memory Test\n");
	memtest();

	putstr("Entering Echo Mode\n");

	char ptr[64];
	ptr[0] = 'H';
	ptr[1] = '\n';
	ptr[2] = '\x00';
	while(1)
	{
		getstr(ptr, 80);
		putstr("Echo: ");
		putstr(ptr);
		putch('\n');
	}
}
