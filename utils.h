#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define handle_error_en(en) \
	do {fprintf(stderr, "%s:%d error:%s\n", __FILE__, __LINE__, strerror(en)); exit(1);} while(0)

#endif // UTILS_H
