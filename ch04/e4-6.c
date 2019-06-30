//** See more test in ./filehole/

#include "apue.h"

char buf1[] = "abcde";
char buf2[] = "ABCDE";

int main(int argc, char** argv) {
	if (argc < 3) {
		// err_ret("Usage: %s <source> <target>\n", argv[0]);
		printf("Usage: %s <source> <target>\n", argv[0]);
		return -1;
	}

	//** For now, just test
	int fd;
	if ((fd = creat("file.hold", FILE_MODE)) < 0) {
		err_sys("creat error");
	}
	if (write(fd, buf1, 5) != 5) {
		err_sys("buf1 write error");
	}
	if (lseek(fd, 800, SEEK_SET) == -1) {
		err_sys("lseek error");
	}
	if (write(fd, buf2, 5) != 5) {
		err_sys("buf2 write errpr");
	}

	exit(0);
}

