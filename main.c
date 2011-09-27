#include "screen.h"
#include "kmem.h"
#include "string.h"
#include "shell.h"
#include "tree.h"
#include "commands/commands.h"

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

void main() {
	initialize_acia();
    initialize_commands();
	kmeminit();
	
	shell();
	
	while(1);
}
