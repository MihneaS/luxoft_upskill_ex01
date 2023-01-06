#include <stdio.h>
#include <stdlib.h>

#define TREAT_ERR(err) {fprintf(stderr, "%s:%d error:%d\n", __FILE__, __LINE__, err); exit(1);}
