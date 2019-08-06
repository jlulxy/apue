#include "apue.h"
#include <sys/utsname.h>

int main() {
	struct utsname name;

	if (uname(&name) == -1) {
		err_ret("uname error");
	}

	printf("sysname=%s\n", name.sysname);
	printf("nodename=%s\n", name.nodename);
	printf("release=%s\n", name.release);
	printf("version=%s\n", name.version);
	printf("machine=%s\n", name.machine);

	exit(0);
}

