// gcc filehole.c -lapue -D_GNU_SOURCE

#include "apue.h"
#include <fcntl.h>

char buf1[] = "abcdexxxxx";
char buf2[] = "ABCDEXXXXX";
char buf3[16384];

void my_cp();

int main(int argc, char** argv) {
	//** create testfile.hold
	int fd;
	if ((fd = creat("file.hole", FILE_MODE)) < 0) {
		err_sys("creat error");
	}
	if (write(fd, buf1, 10) != 10) {
		err_sys("buf1 write error");
	}
	if (lseek(fd, 16374, SEEK_SET) == -1) {
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
	if ((read_len = read(fd, buf3, 16384)) < 0) {
		err_sys("buf3 read from file error");
	}
	printf("read_len=%ld\n", read_len);
	close(fd);

	//** write buf3 to file.copy
	if ((fd = creat("file.copy", FILE_MODE)) < 0) {
		err_sys("creat file.copy error");
	}
	if (write(fd, buf3, 16384) != 16384) {
		err_sys("write buf3 to file.copy error");
	}
	close(fd);
	
	/*
	** In Ununtu18.04, SEEK_HOLE and SEEK_DATA are all
	** treat 4096(4K) as one part, we can call 'block'
	** in a file.
	** 
	** That is, for exercise 4.6, I cannot completely
	** "cp" the hole file to and other without any extra
	** '\0'. There will fill some additional '\0' in the
	** data block.
	*/

	//** find hole by lseek whence=SEEK_HOLE
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

	off_t next_hole_16373 = lseek(fd, 16373, SEEK_HOLE);
	printf("next_hole_16373=%ld\n", next_hole_16373);
	
	off_t next_hole_16374 = lseek(fd, 16374, SEEK_HOLE);
	printf("next_hole_16374=%ld\n", next_hole_16374);
	
	off_t next_hole_16375 = lseek(fd, 16375, SEEK_HOLE);
	printf("next_hole_16375=%ld\n", next_hole_16375);

	//** find data by lseek whence=SEEK_DATA
	off_t next_data_0 = lseek(fd, 0, SEEK_DATA);
	printf("next_data_0=%ld\n", next_data_0);
	
	off_t next_data_9 = lseek(fd, 9, SEEK_DATA);
	printf("next_data_9=%ld\n", next_data_9);

	off_t next_data_10 = lseek(fd, 10, SEEK_DATA);
	printf("next_data_10=%ld\n", next_data_10);

	off_t next_data_11 = lseek(fd, 11, SEEK_DATA);
	printf("next_data_11=%ld\n", next_data_11);
	
	off_t next_data_100 = lseek(fd, 100, SEEK_DATA);
	printf("next_data_100=%ld\n", next_data_100);

	off_t next_data_4100 = lseek(fd, 4100, SEEK_DATA);
	printf("next_data_4100=%ld\n", next_data_4100);

	off_t next_data_12287 = lseek(fd, 12287, SEEK_DATA);
	printf("next_data_12287=%ld\n", next_data_12287);

	off_t next_data_12288 = lseek(fd, 12288, SEEK_DATA);
	printf("next_data_12288=%ld\n", next_data_12288);

	off_t next_data_12289 = lseek(fd, 12289, SEEK_DATA);
	printf("next_data_12289=%ld\n", next_data_12289);

	off_t next_data_16373 = lseek(fd, 16373, SEEK_DATA);
	printf("next_data_16373=%ld\n", next_data_16373);
	
	off_t next_data_16374 = lseek(fd, 16374, SEEK_DATA);
	printf("next_data_16374=%ld\n", next_data_16374);
	
	off_t next_data_16380 = lseek(fd, 16380, SEEK_DATA);
	printf("next_data_16380=%ld\n", next_data_16380);
	close(fd);
	
	/* Update at 2019-07-23*/
	my_cp();
	exit(0);
}

void my_cp() {
	//** create test file: file1.hold and file1.copy
	int fd, fd_copy;
	if ((fd = open("file1.hole", O_RDWR)) < 0) {
		err_sys("open error");
	}
	if (write(fd, buf1, 10) != 10) {
		err_sys("buf1 write error");
	}
	if (lseek(fd, 1000000, SEEK_SET) == -1) {
		err_sys("lseek error");
	}
	if (write(fd, buf2, 10) != 10) {
		err_sys("buf1 write error");
	}
	if ((fd_copy = creat("file1.copy", FILE_MODE)) < 0) {
		err_sys("create error");
	}
	
	//** set off_set to 0
	if (lseek(fd, 0, SEEK_SET) == -1) {
		err_sys("lseek error");
	}
	
	off_t last_data = 0;
	off_t next_data = 0;
	off_t next_hole = 0;
	off_t currpos = 0;
	ssize_t read_len = -1;
	while ((next_data = lseek(fd, last_data, SEEK_DATA)) >= last_data) {
		next_hole = lseek(fd, next_data, SEEK_HOLE);
		last_data = next_hole + 1;
		printf("cp currpos=%ld\n", currpos);
		printf("cp next_data=%ld\n", next_data);
		printf("cp next_hole=%ld\n", next_hole);
		printf("cp last_data=%ld\n", last_data);
		if ((currpos = lseek(fd, next_data, SEEK_SET)) < 0) {
			err_sys("reset lseek error");
		}
		if ((read_len = read(fd, buf3, next_hole - next_data)) < 0) {
			err_sys("buf3 read error");
		}
		printf("cp read_len=%ld\n", read_len);

		//** write to file1.copy
		if ((currpos = lseek(fd_copy, next_data, SEEK_SET)) < 0) {
			err_sys("lseek with SEEK_SET to create hole error");
		}
		if (write(fd_copy, buf3, read_len) != read_len) {
			err_sys("buf3 write error");
		}
	}
	close(fd);
	close(fd_copy);
}

