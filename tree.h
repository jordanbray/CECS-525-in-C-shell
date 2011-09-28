#ifndef __TREE_H__
#define __TREE_H__

#include "kmem.h"
#include "string.h"
#include "linked_list.h"

struct tnode {
 char *key;
 void *value;
 int nodes;
 struct tnode *left;
 struct tnode *right;
};

#define DO_SINGLE_XOR(i1, i2) ((unsigned int)i1)^=((unsigned int)i2)
#define SWAP(i1, i2) DO_SINGLE_XOR(i1, i2); DO_SINGLE_XOR(i2, i1); DO_SINGLE_XOR(i1, i2)
/* insert, swap, search value, search minimum and search maximum values */
struct tnode *tnode_insert(struct tnode *p, const char *key, void *value);
struct tnode *tnode_swap(struct tnode *p);
struct tnode *tnode_search(struct tnode *p, const char *key);
struct tnode *tnode_searchmin(struct tnode *p);
struct tnode *tnode_searchmax(struct tnode *p);
void tnode_startswith(struct tnode *p, struct linked_list **ll, const char *key);

void tnode_print(struct tnode *p, int num_spaces);

/* destroy, count tree nodes */
void tnode_destroy(struct tnode *p);
int tnode_count(struct tnode *p);

#endif

