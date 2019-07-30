#include "apue.h"

#define MY_MAXLINE 4

void my_setbuf(FILE *restrict fp, char *restrict buf);

int main(int argc, char **argv) {
	/* Test setbuf() on stdin */
	
	char buf[MY_MAXLINE];
	
	/* Not work cause:
	 * "Normally, the stream is then fully buffered, but some systems may set
	 * line buffering if the stream is associated with a terminal device.
	 */
	my_setbuf(stdin, NULL);
	my_setbuf(stdout, NULL);

	while (fgets(buf, MY_MAXLINE, stdin) != NULL) {
		printf("\n[buf=%s, siz=%ld]\n", buf, sizeof(buf));
		if (fputs(buf, stdout) == EOF) {
			err_sys("output error");
		}
	}
	if (ferror(stdin)) {
		err_sys("input error");
	}

	return 0;
}

void my_setbuf(FILE *restrict fp, char *restrict buf) {
	if (buf == NULL) {
		setvbuf(fp, buf, _IONBF, 0);
	} else {
		setvbuf(fp, buf, _IOFBF, BUFSIZ);
	}
}

