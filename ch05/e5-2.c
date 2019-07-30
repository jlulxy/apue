#include "apue.h"

#define MY_MAXLINE 4

int main(int argc, char **argv) {
	printf("MAXLINE=%d\n", MAXLINE);
	
	char buf[MY_MAXLINE];

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

