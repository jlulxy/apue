#include "apue.h"
#define BUFFSIZE 1024
char buf[BUFFSIZE];

int main(void) {
	ssize_t ret;
	ret = readlink("./a.ln", buf, BUFFSIZE);
	printf("ret=%ld\n", ret);
	printf("buf=%s\n", buf);
	return(0);
}
