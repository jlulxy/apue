#include "apue.h"
#include <fcntl.h>

int main(void) {
	int fd = open("temp.txt", O_RDWR | O_CREAT);
	printf("fd=%d\n", fd);
	close(fd);
}

/**
 * fd will always be 3
 */

