#include <pthread.h>

struct _node_t {
	int val;
	void (*callback_print)(struct _node_t *self);
	struct _node_t *next;
};

typedef struct _node_t node_t;

typedef struct {
	node_t *start;
	pthread_mutex_t mutex;
} llist_t;

void init_node(node_t *node, int val);
void print_node(node_t *node);
void init_list(llist_t *list);
void destroy_list(llist_t *list);
void add_node(llist_t *list, int val);
void delete_node(llist_t *list, int val);
void print_list(llist_t *list);
void sort_list(llist_t *list);
void flush_list(llist_t *list);
