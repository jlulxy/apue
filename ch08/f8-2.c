#include "apue.h"

int globvar = 6;

int main(int argc, char **argv) {
	int var;
	pid_t pid;

	var = 88;
	printf("before vfork");
	printf("\n");
	if ((pid = vfork()) < 0) {
		err_sys("vfork error");
	} else if (pid == 0) {
		globvar++;
		var++;
		_exit(0);
		// exit(0);
		
		//** _exit() does not perfrom any flush of standard I/O buffers.
	}

	printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar, var);
	exit(0);
}

