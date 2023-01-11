#include "llist.h"
#include "utils.h"
#include <stdio.h>
#include <errno.h>

//struct _node_t {
//	int val;
//	int (*callback_print)(struct _node_t *self);
//	struct _node_t *next;
//};
//typedef struct _node_t node_t;

//typedef struct {
//	node_t *start;
//	pthread_mutex_t mutex;
//} llist_t;

static int print_node(node_t *node);

int init_node(node_t *node, int val) {
	if (node == NULL) {
		return LLIST_NULL_ARG;
	}

	node->val = val;
	node->callback_print = &print_node;
	node->next = NULL;

	return 0;
}

static int print_node(node_t *node) {
	if (node == NULL) {
		return LLIST_NULL_ARG;
	}

	int rc = printf("%3d;", node->val);
	if (rc < 0) {
		return LLIST_PRINTF_ERR;
	}

	return 0;
}

int init_list(llist_t *list) {
	if (list == NULL) {
		return LLIST_NULL_ARG;
	}

	list->start = NULL;
	int rc = pthread_mutex_init(&list->mutex, NULL);
	if (rc != 0) {
		errno = rc;
		return LLIST_PTHREAD_ERR;
	}

	return 0;
}

int destroy_list(llist_t *list) {
	if (list == NULL) {
		return LLIST_NULL_ARG;
	}

	{
		int rc = flush_list(list);
		if (rc != 0) {
			return rc;
		}
	}
	{
		int rc = pthread_mutex_destroy(&list->mutex);
		if (rc != 0) {
			errno = rc;
			return LLIST_PTHREAD_ERR;
		}
	}
	return 0;
}

int add_node(llist_t *list, int val) {
	if (list == NULL) {
		return LLIST_NULL_ARG;
	}

	{
		int rc = pthread_mutex_lock(&list->mutex);
		if (rc != 0) {
			errno = rc;
			return LLIST_PTHREAD_ERR;
		}
	}

	{
		int rc = printf("adding node %d\n", val);
		if (rc < 0) {
			return LLIST_PRINTF_ERR;
		}
	}
	node_t **pcur = &list->start;
	node_t *cur = list->start;
	while (cur) {
		if (cur->val == val) {
			{
				int rc = pthread_mutex_unlock(&list->mutex);
				if (rc != 0) {
					errno = rc;
					return LLIST_PTHREAD_ERR;
				}
			}
			return LLIST_DUP_VAL;
		}
		pcur = &cur->next;
		cur = cur->next;
	}
	*pcur = (node_t*) malloc(sizeof(node_t));
	{
		int rc = init_node(*pcur, val);
		if (rc != 0) {
			return rc;
		}
	}

	{
		int rc = pthread_mutex_unlock(&list->mutex);
		if (rc) {
			errno = rc;
			return LLIST_PTHREAD_ERR;
		}
	}

	return 0;
}

int delete_node(llist_t *list, int val) {
	if (list == NULL) {
		return LLIST_NULL_ARG;
	}

	{
		int rc = pthread_mutex_lock(&list->mutex);
		if (rc != 0) {
			errno = rc;
			return LLIST_PTHREAD_ERR;
		}
	}

	{
		int rc = printf("deleting node %d\n", val);
		if (rc < 0) {
			return LLIST_PRINTF_ERR;
		}
	}
	node_t **pcur = &list->start;
	node_t *cur = list->start;
	while (cur) {
		if (cur->val == val) {
			*pcur = cur->next;
			free(cur);
			{
				int rc = pthread_mutex_unlock(&list->mutex);
				if (rc != 0) {
					errno = rc;
					return LLIST_PTHREAD_ERR;
				}
			}
			return 0;
		}
		pcur = &cur->next;
		cur = cur->next;
	}

	{
		int rc = pthread_mutex_unlock(&list->mutex);
		if (rc != 0) {
			errno = rc;
			return LLIST_PTHREAD_ERR;
		}
	}

	return LLIST_NOT_FOUND;
}

int print_list(llist_t *list) {
	if (list == NULL) {
		return LLIST_NULL_ARG;
	}

	{
		int rc = pthread_mutex_lock(&list->mutex);
		if (rc != 0) {
			errno = rc;
			return LLIST_PTHREAD_ERR;
		}
	}

	{
		int rc = printf("printing the list\n");
		if (rc < 0) {
			return LLIST_PRINTF_ERR;
		}
	}
	node_t *cur = list->start;
	while (cur) {
		{
			int rc = cur->callback_print(cur);
			if (rc != 0) {
				return rc;
			}
		}
		cur = cur->next;
	}
	{
		int rc = printf("\n");
		if (rc < 0) {
			return LLIST_PRINTF_ERR;
		}
	}

	{
		int rc = pthread_mutex_unlock(&list->mutex);
		if (rc != 0) {
			errno = rc;
			return LLIST_PTHREAD_ERR;
		}
	}
	return 0;
}

int sort_list(llist_t *list) {
	if (list == NULL) {
		return LLIST_NULL_ARG;
	}

	{
		int rc = pthread_mutex_lock(&list->mutex);
		if (rc != 0) {
			errno = rc;
			return LLIST_PTHREAD_ERR;
		}
	}

	{
		int rc = printf("sorting the list\n");
		if (rc < 0) {
			return LLIST_PRINTF_ERR;
		}
	}

	if (!list->start) {
		return 0;
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
		int rc = pthread_mutex_unlock(&list->mutex);
		if (rc != 0) {
			errno = rc;
			return LLIST_PTHREAD_ERR;
		}
	}
	return 0;
}

int flush_list(llist_t *list) {
	if (list == NULL) {
		return LLIST_NULL_ARG;
	}

	{
		int rc = pthread_mutex_lock(&list->mutex);
		if (rc != 0) {
			errno = rc;
			return LLIST_PTHREAD_ERR;
		}
	}
	{
		int rc = printf("flushing the list\n");
		if (rc < 0) {
			return LLIST_PRINTF_ERR;
		}
	}
	node_t *cur = list->start;
	node_t *next;
	while (cur) {
		next = cur->next;
		free(cur);
		cur = next;
	}
	list->start = NULL;

	{
		int rc = pthread_mutex_unlock(&list->mutex);
		if (rc != 0) {
			errno = rc;
			return LLIST_PTHREAD_ERR;
		}
	}
	return 0;
}
