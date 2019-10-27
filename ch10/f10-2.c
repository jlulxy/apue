#include "apue.h"

static void sig_usr(int);

int main(void) {
	void* usr1 = NULL;
	void* usr2 = NULL;
	usr1 = signal(SIGUSR1, sig_usr);
	if (usr1 == SIG_ERR) {
		err_sys("can't catch SIGUSR1");
	}
	usr2 = signal(SIGUSR2, sig_usr);
	if (usr2 == SIG_ERR) {
		err_sys("can't catch SIGUSR2");
	}
	printf("usr1 = %p\n", usr1);
	printf("usr2 = %p\n", usr2);
	for ( ; ; ) {
		pause();
	}
}

static void sig_usr(int signo) {
	if (signo == SIGUSR1) {
		printf("received SIGUSR1\n");
	} else if (signo == SIGUSR2) {
		printf("received SIGUSR2\n");
	} else {
		err_dump("received signal %d\n", signo);
	}
}

