#include "apue.h"

int main(void) {
	int c;
	while ((c = getc(stdin)) != EOF) {
		if (putc(c, stdout) == EOF) {
			err_sys("oe");
		}
	}

	if (ferror(stdin)) {
		err_sys("ie");
	}
	exit(0);
}
