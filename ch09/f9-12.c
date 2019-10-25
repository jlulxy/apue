#include "apue.h"
#include <errno.h>

static void sig_hup(int signo) {
	printf("SIGHUP received. pid = %ld, signo = %d\n", (long)getpid(), signo);
}

static void pr_ids(char *name) {
	printf("%s: pid = %ld, ppid = %ld, pgrp = %ld, tpgrp = %ld\n",
		name, (long)getpid(), (long)getppid(), (long)getpgrp,
		(long)tcgetpgrp(STDIN_FILENO));
	fflush(stdout);
}

int main(void) {
	char c;
	pid_t pid;

	pr_ids("parents");
	
	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid > 0) {
		//* parent
		//* sleep to let child stop itself
		sleep(5);
	} else {
		//* child
		pr_ids("child");
		//* establish signal handler
		signal(SIGHUP, sig_hup);
		//* stop itself
		kill(getpid(), SIGTSTP);
		//* prints only if we're continue
		pr_ids("child");
		if (read(STDIN_FILENO, &c, 1) != 1) {
			printf("read error %d on controlling TTY\n", errno);
		}
	}
	exit(0);
}

