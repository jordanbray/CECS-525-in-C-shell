#include "tree.h"
/* insert a tnode into the binary tree */
struct tnode *tnode_insert(struct tnode *p, char *key, void *value) {
	struct tnode *tmp_one = NULL;
	struct tnode *tmp_two = NULL;

	if(p == NULL) {
		/* insert [new] tnode as root node */
		p = (struct tnode *)kmalloc(sizeof(struct tnode));
		p->key = key;
		p->value = value;
		p->left = p->right = NULL;
	} else {
		tmp_one = p;
		/* Traverse the tree to get a pointer to the specific tnode */
		/* The child of this tnode will be the [new] tnode */
		while(tmp_one != NULL) {
			tmp_two = tmp_one;
			if(strcmp(tmp_one->key, key) == 1)
				tmp_one = tmp_one->left;
			else
			    tmp_one = tmp_one->right;
		}

		if(strcmp(tmp_two->key, key) == 1) {
			/* insert [new] tnode as left child */
			tmp_two->left = (struct tnode *)kmalloc(sizeof(struct tnode));
			tmp_two = tmp_two->left;
			tmp_two->key = key;
			tmp_two->value = value;
			tmp_two->left = tmp_two->right = NULL;
		} else {
			/* insert [new] tnode as left child */
			tmp_two->right = (struct tnode *)kmalloc(sizeof(struct tnode)); 
			tmp_two = tmp_two->right;
			tmp_two->key = key;
			tmp_two->value = value;
			tmp_two->left = tmp_two->right = NULL;
		}
	}

	return(p);
}

/* returns the total number of tree nodes */
int tnode_count(struct tnode *p) {
	if(p == NULL)
		return 0;
	else {
		if(p->left == NULL && p->right == NULL)
			return 1;
		else
			return(1 + (tnode_count(p->left) + tnode_count(p->right)));
	}
}

/* locate a value in the btree */
struct tnode *tnode_search(struct tnode *p, char *key) {
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

		kfree(p);
	}
}

