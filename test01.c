#include <stdio.h>
#include <unistd.h> // for sleep
#include "llist.h"

void *test(void *args) {
	llist_t list;
	init_list(&list);

	printf("Single thread simple test.\n Output:\n");

	print_list(&list);

	add_node(&list, 5);
	print_list(&list);

	add_node(&list, 5);
	add_node(&list, 4);
	add_node(&list, 3);
	add_node(&list, 5);
	print_list(&list);

	sort_list(&list);
	print_list(&list);

	delete_node(&list, 10);
	delete_node(&list, 5);
	delete_node(&list, 5);
	delete_node(&list, 4);
	print_list(&list);

	add_node(&list, 5);
	add_node(&list, 4);
	add_node(&list, 3);
	print_list(&list);

	flush_list(&list);
	print_list(&list);

	add_node(&list, 2);
	add_node(&list, 3);
	add_node(&list, 4);
	print_list(&list);

	delete_node(&list, 2);
	delete_node(&list, 4);
	delete_node(&list, 3);
	print_list(&list);

	printf("Expected output:\n");
	printf("\n");
	printf("5;\n");
	printf("5;4;3;\n");
	printf("3;4;5;\n");
	printf("3;\n");
	printf("3;5;4;\n");
	printf("\n");
	printf("2;4;3;\n");
	printf("\n");

	destroy_list(&list);

	return NULL;
}

int main() {
	pthread_t th_id;
	pthread_create(&th_id, NULL, test, NULL);
	pthread_join(th_id, NULL);
	return 0;
}

