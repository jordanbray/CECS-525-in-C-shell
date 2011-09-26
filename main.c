#include "screen.h"
#include "kmem.h"
#include "string.h"
#include "tree.h"

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

void test_tree() {
    struct tnode *root = NULL;
    root = tnode_insert(root, "one", ((void*)1));
    root = tnode_insert(root, "two", ((void*)2));
    root = tnode_insert(root, "three", ((void*)3));
    root = tnode_insert(root, "four", ((void*)4));
    root = tnode_insert(root, "five", ((void*)5));
    root = tnode_insert(root, "negative 1", (void*)-1);
    struct tnode *node = tnode_search(root, "four");
    if (((int *)node->value) == ((int *)4))
        putstr("SUCCESS\n");
    else
        putstr("FAILURE\n");
    tnode_destroy(root);

}

void shell() {
	char ptr[64];
	
	putstr("Welcome to the (unstable) C Kernel\n");
	
	while(1)
	{
		putstr("> ");
		getstr(ptr, 64);
		if (strcmp(ptr, "stop") == 0)
		{
			putstr("Exiting...\n");
			return;
		}
		else if (strcmp(ptr, "memtest") == 0)
		{
			putstr("Performing Memory Test\n");
			memtest();
		}
		else if (strcmp(ptr, "errtest") == 0)
		{
			asm ("trap #0\n");
		}
		else if (strcmp(ptr, "help") == 0)
		{
			putstr("Welcome to the Kernel\n\tmemtest\tTest Malloc\n\terrtest\tTest error handling\n\tstop\tExit the shell\n\thelp\tDisplay the Help\n");
		}
		else if (!strcmp(ptr, "tree"))
        {
            test_tree();
        }
		{
			putstr("Echo: ");
			putstr(ptr);
			putch('\n');
		}
	}
}

void main() {
	initialize_acia();
	kmeminit();
	
	shell();
	
	while(1);
}
