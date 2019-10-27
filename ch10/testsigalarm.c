#include "apue.h"

int i = 0;

static void catchalarm(int signo) {
	printf("signo=%d, i=%d\n", signo, i);
	alarm(1);
}

int main(void) {
	if (signal(SIGALRM, catchalarm) == SIG_ERR) {
		err_sys("can't catch SIGALRM\n");
	}
	alarm(1);
	for(; ; ) {
		printf("i=%d\n", i++);
	}
}
