#include "linked_list.h"

void linked_list_push(struct linked_list **ll, void *value) {
	if (*ll == NULL) {
		*ll = kmalloc(sizeof(struct linked_list));
		(*ll)->value = value;
		(*ll)->next = NULL;
	} else {
		struct linked_list *new_root = NULL;
		linked_list_push(&new_root, value);
		new_root->next = *ll;
		*ll = new_root;
	}
}

void *linked_list_pop(struct linked_list **ll) {
	if (*ll == NULL)
		return NULL;
	void *ret = (*ll)->value;
	struct linked_list *next = (*ll)->next;
	kfree(ll);
	*ll = next;
}

void *linked_list_peek(struct linked_list **ll) {
	return (*ll)->value;
}

