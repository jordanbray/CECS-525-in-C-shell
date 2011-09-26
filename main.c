#include "screen.h"
#include "kmem.h"
#include "string.h"
#include "shell.h"

void *test_malloc(int bytes) {
	void *ptr = kmalloc(bytes);
	putstr("Malloc'd and got: ");
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
	void *p3 = test_malloc(124);
    test_free(p1);
    test_free(p2);
    test_free(p3);
}



void main() {
	initialize_acia();
	kmeminit();
	
	shell();
	
	while(1);
}
