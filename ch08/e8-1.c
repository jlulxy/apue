#include "apue.h"

int globvar = 6;

int main(void) {
	int var;
	pid_t pid;

	var = 88;
	printf("pid = %ld, before vfork\n", (long)getpid());
	// copy stdout to fprint the result of printf
	int fd_stdout = dup(fileno(stdout));
	printf("fd_stdout = %d\n", fd_stdout);
	
	if ((pid = vfork()) < 0) {
		err_sys("vfork error");
	} else if (pid == 0) {
		globvar++;
		var++;
		// close by my own to make printf return -1
		fclose(stdin);
		fclose(stdout);
		fclose(stderr);
		exit(0);
	}
	
	int p = 0;
	p = printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar, var);
	fprintf(fdopen(fd_stdout, "w"), "fprintf p = %d\n", p);

	exit(0);
}

