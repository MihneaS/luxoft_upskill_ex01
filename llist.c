#include "llist.h"
#include "util.h"
#include <stdio.h>

//struct _node_t {
//	int val;
//	void (*callback_print)(struct _node_t *self);
//	struct _node_t *next;
//};
//typedef struct _node_t node_t;

//typedef struct {
//	node_t *start;
//	pthread_mutex_t mutex;
//} llist_t;

void init_node(node_t *node, int val) {
	node->val = val;
	node->callback_print = &print_node;
	node->next = NULL;
}

void print_node(node_t *node) {
	printf("%3d;", node->val);
}

void init_list(llist_t *list) {
	list->start = NULL;
	pthread_mutex_init(&list->mutex, NULL);
}

void destroy_list(llist_t *list) {
	flush_list(list);
	pthread_mutex_destroy(&list->mutex);
}

void add_node(llist_t *list, int val) {
	{
		int err = pthread_mutex_lock(&list->mutex);
		if (err) {
			handle_error_en(err);
		}
	}

	printf("adding node %d\n", val);
	node_t **pcur = &list->start;
	node_t *cur = list->start;
	while (cur) {
		if (cur->val == val) {
			{
				int err = pthread_mutex_unlock(&list->mutex);
				if (err) {
					handle_error_en(err);
				}
			}
			return;
		}
		pcur = &cur->next;
		cur = cur->next;
	}
	*pcur = (node_t*) malloc(sizeof(node_t));
	init_node(*pcur, val);

	{
		int err = pthread_mutex_unlock(&list->mutex);
		if (err) {
			handle_error_en(err);
		}
	}
}

void delete_node(llist_t *list, int val) {
	{
		int err = pthread_mutex_lock(&list->mutex);
		if (err) {
			handle_error_en(err);
		}
	}

	printf("deleting node %d\n", val);
	node_t **pcur = &list->start;
	node_t *cur = list->start;
	while (cur) {
		if (cur->val == val) {
			*pcur = cur->next;
			free(cur);
			{
				int err = pthread_mutex_unlock(&list->mutex);
				if (err) {
					handle_error_en(err);
				}
			}
			return;
		}
		pcur = &cur->next;
		cur = cur->next;
	}

	{
		int err = pthread_mutex_unlock(&list->mutex);
		if (err) {
			handle_error_en(err);
		}
	}
}

void print_list(llist_t *list) {
	{
		int err = pthread_mutex_lock(&list->mutex);
		if (err) {
			handle_error_en(err);
		}
	}

	printf("printing the list\n");
	node_t *cur = list->start;
	while (cur) {
		cur->callback_print(cur);
		cur = cur->next;
	}
	printf("\n");

	{
		int err = pthread_mutex_unlock(&list->mutex);
		if (err) {
			handle_error_en(err);
		}
	}
}

void sort_list(llist_t *list) {
	{
		int err = pthread_mutex_lock(&list->mutex);
		if (err) {
			handle_error_en(err);
		}
	}

	printf("sorting the list\n");
	if (!list->start) {
		return;
	}

	node_t *cur1 = list->start;
	node_t **pcur1 = &list->start;
	while (cur1->next) {
		node_t *cur2 = cur1->next;
		node_t **pcur2 = &cur1->next;
		do {
			if (cur1->val > cur2->val) {
				node_t *tmp_node;

				*pcur1 = cur2;
				*pcur2 = cur1;
				tmp_node = cur1->next;
				cur1->next = cur2->next;
				cur2->next = tmp_node;

				tmp_node = cur1;
				cur1 = cur2;
				cur2 = tmp_node;
			}
			pcur2 = &cur2->next;
			cur2 = cur2->next;
		} while (cur2);
		pcur1 = &cur1->next;
		cur1 = cur1->next;
	}

	{
		int err = pthread_mutex_unlock(&list->mutex);
		if (err) {
			handle_error_en(err);
		}
	}
}

void flush_list(llist_t *list) {
	{
		int err = pthread_mutex_lock(&list->mutex);
		if (err) {
			handle_error_en(err);
		}
	}

	printf("flushing the list\n");
	node_t *cur = list->start;
	node_t *next;
	while (cur) {
		next = cur->next;
		free(cur);
		cur = next;
	}
	list->start = NULL;

	{
		int err = pthread_mutex_unlock(&list->mutex);
		if (err) {
			handle_error_en(err);
		}
	}
}
