#include <stdio.h>
#include "llist.h"

void *test() {
	llist_t list;
	init_list(&list);

	printf("Single thread simple test.\nOutput:\n");

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

	printf(
			"\n\n"
			"Expected ouput\n"
			"printing the list\n"
			"\n"
			"adding node 5\n"
			"printing the list\n"
			"  5;\n"
			"adding node 5\n"
			"adding node 4\n"
			"adding node 3\n"
			"adding node 5\n"
			"printing the list\n"
			"  5;  4;  3;\n"
			"sorting the list\n"
			"printing the list\n"
			"  3;  4;  5;\n"
			"deleting node 10\n"
			"deleting node 5\n"
			"deleting node 5\n"
			"deleting node 4\n"
			"printing the list\n"
			"  3;\n"
			"adding node 5\n"
			"adding node 4\n"
			"adding node 3\n"
			"printing the list\n"
			"  3;  5;  4;\n"
			"flushing the list\n"
			"printing the list\n"
			"\n"
			"adding node 2\n"
			"adding node 3\n"
			"adding node 4\n"
			"printing the list\n"
			"  2;  3;  4;\n"
			"deleting node 2\n"
			"deleting node 4\n"
			"deleting node 3\n"
			"printing the list\n"
			"\n"
			);

	destroy_list(&list);

	return NULL;
}

int main() {
	pthread_t th_id;
	pthread_create(&th_id, NULL, test, NULL);
	pthread_join(th_id, NULL);
	return 0;
}

