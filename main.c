#include <stdio.h>
#include <pthread.h>
#include "llist.h"
#include "util.h"

#define TH_NO 3

typedef struct {
	llist_t *list;
	pthread_barrier_t *barrier;
} thread_info;

void *f_th1(void *args) {
	thread_info *tinfo = args;
	llist_t *list = tinfo->list;
	pthread_barrier_t *barrier = tinfo->barrier;

	{
		int err = pthread_barrier_wait(barrier);
		if (err != 0 && err != PTHREAD_BARRIER_SERIAL_THREAD) {
			handle_error_en(err);
		}
	}

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
	thread_info *tinfo = args;
	llist_t *list = tinfo->list;
	pthread_barrier_t *barrier = tinfo->barrier;

	{
		int err = pthread_barrier_wait(barrier);
		if (err != 0 && err != PTHREAD_BARRIER_SERIAL_THREAD) {
			handle_error_en(err);
		}
	}

	add_node(list, 11);
	add_node(list, 1);
	delete_node(list, 11);
	add_node(list, 8);
	print_list(list);

	return NULL;
}

void *f_th3(void *args) {
	thread_info *tinfo = args;
	llist_t *list = tinfo->list;
	pthread_barrier_t *barrier = tinfo->barrier;

	{
		int err = pthread_barrier_wait(barrier);
		if (err != 0 && err != PTHREAD_BARRIER_SERIAL_THREAD) {
			handle_error_en(err);
		}
	}

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

	pthread_barrier_t barrier;
	{
		int err = pthread_barrier_init(&barrier, NULL, TH_NO);
		if (err != 0) {
			handle_error_en(err);
		}
	}

	thread_info tinfo;
	tinfo.list = &list;
	tinfo.barrier = &barrier;

	void* (*foos[TH_NO])(void*) = {f_th1, f_th2, f_th3};

	pthread_t th_ids[TH_NO];

	printf("lunching threads\n");
	for (int i = 0; i < TH_NO; i++) {
		int err = pthread_create(&th_ids[i], NULL, foos[i], &tinfo);
		if (err != 0) {
			handle_error_en(err);
		}
	}

	for (int i = 0; i < TH_NO; i++) {
		pthread_join(th_ids[i], NULL);
	}
	printf("threads joined. finishing\n");

	destroy_list(&list);

	return 0;
}
