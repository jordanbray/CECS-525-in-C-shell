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
struct tnode *tnode_insert(struct tnode *, const char *, void *);
struct tnode *tnode_swap(struct tnode *);
struct tnode *tnode_search(struct tnode *, const char *);
struct tnode *tnode_searchmin(struct tnode *);
struct tnode *tnode_searchmax(struct tnode *);
struct tnode *tnode_startswith(struct tnode *, const char *);
/* destroy, count tree nodes */
void tnode_destroy(struct tnode *);
int tnode_count(struct tnode *);

#endif

