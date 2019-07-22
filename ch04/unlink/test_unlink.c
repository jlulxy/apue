#include "apue.h"
#include <fcntl.h>

int main(void) {
	if (open("tempfile", O_RDWR | O_CREAT) < 0) {
		err_sys("open error");
	}
	if (link("tempfile", "tempfile_link1") < 0) {
		err_sys("link error");
	}
	sleep(15);
	if (unlink("tempfile") < 0) {
		err_sys("unlink error");
	}
	printf("done\n");
	exit(0);
}

/*
 * 2019-07-22
 * 1. Create a file tempfile with some letters.
 * 2. Create a hard link with "link" cmd called tempfile_link.
 * 3. Do "rm tempfile_link1".
 * 4. Run this program.
 * 5. Do "ls -ali" multiple times to see the output about tempfile*
 */

