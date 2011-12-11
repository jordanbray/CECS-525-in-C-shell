#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <kmem.h>

struct linked_list {
	void *value;
	struct linked_list *next;
};

void linked_list_push(struct linked_list **ll, void *value);
void *linked_list_pop(struct linked_list **ll);
void *linked_list_peek(struct linked_list **ll);

#endif

