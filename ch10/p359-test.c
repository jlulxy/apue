/*
 * 2019-11-07, test signal occurs between unblock and pause()
 */

#include "apue.h"

static void pr_sleep(const char*, int);
static int sleep_cnt = 0;
static void sig_usr1(int);

int main(void) {
	if (signal(SIGUSR1, sig_usr1) == SIG_ERR) {
		err_sys("signal(SIGUSR1) error");
	}
	sigset_t newmask, oldmask;
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGUSR1);
   
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
		err_sys("sigprocmask error");
	}

	pr_sleep("block SIGUSR1", 10);

	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
		err_sys("sigprocmask error");
	}
	
	pr_sleep("unblock SIGUSR1", 10);

	printf("start pause() !!!\n");
	pause();

	printf("finished!\n");
	exit(0);
}

static void pr_sleep(const char* msg, int n) {
	for (int i = 0; i < n; i++) {
		printf("\n[%d]: [%s] do sleep\n", sleep_cnt++, msg);
		sleep(1);
	}
}

static void sig_usr1(int signo) {
	pr_mask("in sig_usr1(): ");
	pr_sleep("in sig_usr1()", 3);
	if (signal(SIGUSR1, sig_usr1) == SIG_ERR) {
		err_sys("signal(SIGUSR1) error");
	}
}
