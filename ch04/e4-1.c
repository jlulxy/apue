#include "apue.h"

int main(int argc, char** argv) {
	int i;
	struct stat buf;
	char* ptr;

	for (i = 1; i < argc; i++) {
		printf("%s: ", argv[i]);
		if (stat(argv[i], &buf) < 0) {
			err_ret("stat error");
			continue;
		}
		if (S_ISREG(buf.st_mode)) {
			ptr = "regular";
		} else if (S_ISDIR(buf.st_mode)) {
			ptr = "directory";
		} else if (S_ISCHR(buf.st_mode)) {
			ptr = "character special";
		} else if (S_ISBLK(buf.st_mode)) {
			ptr = "block special";
		} else if (S_ISFIFO(buf.st_mode)) {
			ptr = "fifo";
		} else if (S_ISLNK(buf.st_mode)) {
			ptr = "symbolic link";
		} else if (S_ISSOCK(buf.st_mode)) {
			ptr = "socket";
		} else {
			ptr = "** unknown mode **";
		}
		printf("%s\n", ptr);
	}
	exit(0);
}

/*
 * If stat is called, it always tries to follow a symbolic link, so the program
 * will never print a file type of "symbolic link". For the example shown in
 * the text, where /dev/cdrom is a symbolic link to /dav/sr0, stat reports that
 * /dev/chrom is a block special file, not a symbolic link. If the symbolic
 * link points to a nonexistent file, stat return an error.
 */

