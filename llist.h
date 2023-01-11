#ifndef LLIST_H
#define LLIST_H

#include <pthread.h>

#define LLIST_NULL_ARG -2
#define LLIST_PRINTF_ERR -3
#define LLIST_PTHREAD_ERR - 4

#define LLIST_DUP_VAL 1
#define LLIST_NOT_FOUND 2

struct _node_t {
	int val;
	int (*callback_print)(struct _node_t *self);
	struct _node_t *next;
};

typedef struct _node_t node_t;

typedef struct {
	node_t *start;
	pthread_mutex_t mutex;
} llist_t;

int init_node(node_t *node, int val);
int init_list(llist_t *list);
int destroy_list(llist_t *list);
int add_node(llist_t *list, int val);
int delete_node(llist_t *list, int val);
int print_list(llist_t *list);
int sort_list(llist_t *list);
int flush_list(llist_t *list);

#endif //LLIST_H
