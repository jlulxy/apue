#include "apue.h"

void my_setbuf(FILE *restrict fp, char *restrict buf);

int main(int argc, char **argv) {
	return 0;
}

void my_setbuf(FILE *restrict fp, char *restrict buf) {
	if (buf == NULL) {
		setvbuf(fp, buf, _IONBF, 0);
	} else {
		setvbuf(fp, buf, _IOFBF, BUFSIZ);
	}
}

