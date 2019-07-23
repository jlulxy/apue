#include "apue.h"
#include <fcntl.h>

#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

int main(int argc, char** argv) {
	umask(0);
	if (creat("e4-9.foo", RWRWRW) < 0) {
		err_sys("create error for foo");
	}
	umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (creat("e4-9.bar", RWRWRW) < 0) {
		err_sys("create error for bar");
	}
	exit(0);
}


/*
 * If we try, using either open() or creat(), to create a file that already
 * exists, the file's access permission bits are not change. We can verify
 * this by running the program from Figure 4.9.
 */

