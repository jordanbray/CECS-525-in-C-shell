#ifndef __TREE_H__
#define __TREE_H__

#include "kmem.h"
#include "string.h"

struct tnode {
 char *key;
 void *value;
 struct tnode *left;
 struct tnode *right;
};

/* insert, swap, search value, search minimum and search maximum values */
struct tnode *tnode_insert(struct tnode *p, char *key, void *value);
struct tnode *tnode_swap(struct tnode *p);
struct tnode *tnode_search(struct tnode *p, char *key);
struct tnode *tnode_searchmin(struct tnode *p);
struct tnode *tnode_searchmax(struct tnode *p);
struct tnode *tnode_startswith(struct tnode *p, char *key);
/* destroy, count tree nodes */
void tnode_destroy(struct tnode *p);
int tnode_count(struct tnode *p);

#endif

