#include <stdio.h>
#include <pthread.h>
#include "llist.h"

#define FS_TH_LEN 3

void *f_th1(void *args) {
	llist_t *list = (llist_t*)args;
	add_node(list, 2);
	add_node(list, 4);
	add_node(list, 10);
	delete_node(list, 2);
	sort_list(list);
	delete_node(list, 10);
	delete_node(list, 5);
	return NULL;
}
void *f_th2(void *args) {
	llist_t *list = (llist_t*)args;
	add_node(list, 11);
	add_node(list, 1);
	delete_node(list, 11);
	add_node(list, 8);
	print_list(list);
	return NULL;
}

void *f_th3(void *args) {
	llist_t *list = (llist_t*)args;
	add_node(list, 30);
	add_node(list, 25);
	add_node(list, 100);
	sort_list(list);
	print_list(list);
	delete_node(list, 100);
	return NULL;
}

int main() {
	printf("starting test\n");
	llist_t list;
	init_list(&list);
	void* (*foos[FS_TH_LEN])(void*) = {f_th1, f_th2, f_th3};
	pthread_t th_ids[FS_TH_LEN];
	printf("lunching threads\n");
	for (int i = 0; i < FS_TH_LEN; i++) {
		pthread_create(&th_ids[i], NULL, foos[i], &list);
	}
	for (int i = 0; i < FS_TH_LEN; i++) {
		pthread_join(th_ids[i], NULL);
	}
	printf("threads joined. finishing\n");
	return 0;
}
