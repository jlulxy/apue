// gcc filehole.c -lapue -D_GNU_SOURCE

#include "apue.h"
#include <fcntl.h>

char buf1[] = "abcdexxxxx";
char buf2[] = "ABCDEXXXXX";
char buf3[16394];

int main(int argc, char** argv) {
	//** create testfile.hold
	int fd;
	if ((fd = creat("file.hole", FILE_MODE)) < 0) {
		err_sys("creat error");
	}
	if (write(fd, buf1, 10) != 10) {
		err_sys("buf1 write error");
	}
	if (lseek(fd, 16384, SEEK_SET) == -1) {
		err_sys("lseek error");
	}
	if (write(fd, buf2, 10) != 10) {
		err_sys("buf2 write error");
	}
	close(fd);
	
	//** read testfile.hold into buf3
	if ((fd = open("file.hole", O_RDWR)) < 0) {
		err_sys("open file.hole error");
	}
	ssize_t read_len = -1;
	if ((read_len = read(fd, buf3, 16394)) < 0) {
		err_sys("buf3 read from file error");
	}
	printf("read_len=%ld\n", read_len);

	//** write buf3 to file.copy
	close(fd);
	if ((fd = creat("file.copy", FILE_MODE)) < 0) {
		err_sys("creat file.copy error");
	}
	if (write(fd, buf3, 16394) != 16394) {
		err_sys("write buf3 to file.copy error");
	}
	close(fd);
	
	//** find hole by useing lseek whence SEEK_HOLE
	if ((fd = open("file.hole", O_RDWR)) < 0) {
		err_sys("open file.hole error");
	}
	off_t next_hole_0 = lseek(fd, 0, SEEK_HOLE);
	printf("next_hole_0=%ld\n", next_hole_0);

	off_t next_hole_10 = lseek(fd, 10, SEEK_HOLE);
	printf("next_hole_10=%ld\n", next_hole_10);
	
	off_t next_hole_4096 = lseek(fd, 4096, SEEK_HOLE);
	printf("next_hole_4096=%ld\n", next_hole_4096);

	off_t next_hole_4097 = lseek(fd, 4097, SEEK_HOLE);
	printf("next_hole_4097=%ld\n", next_hole_4097);

	off_t next_hole_16381 = lseek(fd, 16381, SEEK_HOLE);
	printf("next_hole_16381=%ld\n", next_hole_16381);
	
	off_t next_hole_16384 = lseek(fd, 16384, SEEK_HOLE);
	printf("next_hole_16384=%ld\n", next_hole_16384);
	
	off_t next_hole_16390 = lseek(fd, 16390, SEEK_HOLE);
	printf("next_hole_16390=%ld\n", next_hole_16390);
	
	exit(0);
}

void test_my_font() {
	printf("Courier New may be the best is Xshell.\n");
}

