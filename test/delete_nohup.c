#include "apue.h"

#define ONE_G 1073741824

static void sig_usr(int);
int cnt = 0;

int main(void) {
	setbuf(stdout, NULL);
	if (signal(SIGUSR1, sig_usr) == SIG_ERR) {
		err_sys("can't catch SIGUSR1");
	}
	if (signal(SIGUSR2, sig_usr) == SIG_ERR) {
		err_sys("can't catch SIGUSR1");
	}

	for (;;) {
		pause();
	}
}

static void sig_usr(int signo) {
	if (signo == SIGUSR1) {
		printf("received SIGUSR1\n");
		if (signal(SIGUSR1, sig_usr) == SIG_ERR) {
			err_sys("can't catch SIGUSR1");
		}
	}
	if (signo == SIGUSR2) {
		printf("received SIGUSR2\n");
		if (signal(SIGUSR2, sig_usr) == SIG_ERR) {
			err_sys("can't catch SIGUSR1");
		}
	}
	printf("cnt=%d\n", cnt++);
	for (int i = 0; i < ONE_G; i++) {
		for (int j = 0; j < 8; j++) {
			printf("%c", '#');
		}
	}
	printf("\n");
}
