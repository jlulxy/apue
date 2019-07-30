#include "apue.h"

int main(int argc, char **argv) {
	int ret;

	ret = printf("");
	printf("ret = %d\n", ret);

	exit(0);
}

/* The function call:
 * printf("");
 * returns 0, since no characters are output.
 */

