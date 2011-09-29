/*
 * Binary tree implementation for M68K
 */

#include "tree.h"



struct tnode *tnode_rol(struct tnode *p) {
	struct tnode *root = p->right;
	if (root->left == NULL) {
		root->left = p;
	} else {
		p->right = root->left;
		root->left =  p;
	}
	
	p->nodes = 1 + tnode_count(p->left) + tnode_count(p->right);
	root->nodes = 1 + tnode_count(root->left) + tnode_count(root->right);
	return root;
}


struct tnode *tnode_ror(struct tnode *p) {
	struct tnode *root = p->left;
	if (root->right == NULL) {
		root->right = p;
	} else {
		p->left = root->right;
		root->right = p;
	}
	p->nodes = 1 + tnode_count(p->left) + tnode_count(p->right);
	root->nodes = 1 + tnode_count(root->left) + tnode_count(root->right);
	return root;
}

void tnode_print(struct tnode *p, int num_spaces) {
	int i;
	if (p == NULL)
		return;
	for (i = 0; i < num_spaces; i++)
		putch(' ');
	putstr(p->key);
	putstr(" (");
	putshort(p->nodes);
	putstr(" nodes)\n");
	tnode_print(p->left, num_spaces + 1);
	tnode_print(p->right, num_spaces + 1);

}

/* floor of log base 2 of x */
unsigned int_log2(unsigned x) {
	int index = 31;
	while (!(x & (1 << index)) && index) index--;
	return index;
}

struct tnode *tnode_balance(struct tnode *p) {
	if (p == NULL)
		return NULL;
	int left = int_log2(tnode_count(p->left));
	int right = int_log2(tnode_count(p->right));
	if (left - right > 1) { // more on the left side
		left = int_log2(tnode_count(p->left->left));
		right = int_log2(tnode_count(p->left->right));
		if (left -  right > 1) {
			p = tnode_ror(p);
		} else if (right - left > 1) {
			p->left = tnode_rol(p->left);
			p = tnode_ror(p); 
		}

	} else if (right - left > 1) {
		left = tnode_count(p->left);
		right = tnode_count(p->right);
		if (right - left > 1) {
			p = tnode_rol(p);
		} else if (left - right > 1) {
			p->right = tnode_ror(p->right);
			p = tnode_rol(p);
		}
	}
	return p;
}

/* insert a tnode into the binary tree.  Overwrites previous contents. */
struct tnode *tnode_insert(struct tnode *p, const char *key, void *value) {
	if(p == NULL) {
		/* insert [new] tnode as root node */
		p = (struct tnode *)kmalloc(sizeof(struct tnode));
		p->key = strdup(key);
		p->value = value;
		p->left = p->right = NULL;
		p->nodes = 1;
		return p;
	}
	/* Traverse the tree to get a pointer to the specific tnode */
	/* The child of this tnode will be the [new] tnode */
	int compare = strcmp(p->key, key);
	if (compare == 1)
		p->left = tnode_insert(p->left, key, value);
	else if (compare == -1)
		p->right = tnode_insert(p->right, key, value);
	else {
		p->value = value; // overwrite...
	}
	p->nodes = tnode_count(p->left) + tnode_count(p->right) + 1;
	p = tnode_balance(p);
	return p;
}

/* returns the total number of tree nodes */
int tnode_count(struct tnode *p) {
	if(p == NULL)
		return 0;
	else {
		return p->nodes;
	}
}

/* locate a value in the btree */
struct tnode *tnode_search(struct tnode *p, const char *key) {
	struct tnode *temp;
	temp = p;
	while(temp != NULL) {
		int compare = strcmp(temp->key, key);

		if(!compare)
			return temp;
		else if(compare == 1)
			temp = temp->left;
		else
			temp = temp->right;
	}

	return NULL;
}

void tnode_startswith(struct tnode *p, struct linked_list **ll, const char *key) {
    struct tnode *temp = p;
	if (p == NULL)
		return;
    int compare = strstartswith(p->key, key);
	if (!compare) {
		tnode_startswith(p->left, ll, key);
		linked_list_push(ll, p->key);
		tnode_startswith(p->right, ll, key);
	} else if (compare == 1)
		tnode_startswith(p->left, ll, key);
	else
		tnode_startswith(p->right, ll, key);
}

/* locate a minimum value in the btree */
struct tnode *tnode_searchmin(struct tnode *p) {
	if(p == NULL)
		return NULL;
	else {
		if(p->left == NULL)
			return p;
		else
			return tnode_searchmin(p->left);
	}
}

/* locate a maximum value in the btree */
struct tnode *tnode_searchmax(struct tnode *p) {
	if(p != NULL)
		while(p->right != NULL)
			p = p->right;

	return p;
}

/* destroy the binary tree */
void tnode_destroy(struct tnode *p) {
	if(p != NULL) {
		tnode_destroy(p->left);
		tnode_destroy(p->right);
		kfree(p->key);
		kfree(p);
	}
}

