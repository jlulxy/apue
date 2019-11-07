#include "apue.h"

static void sig_int(int);
static void sig_usr1(int);
static int sleep_cnt = 0;
static void pr_sleep(const char*, int);

int main(void) {
	sigset_t newmask, oldmask, waitmask;
	
	pr_mask("program start: ");

	if (signal(SIGINT, sig_int) == SIG_ERR) {
		err_sys("signal(SIGINT) error");
	}
	if (signal(SIGUSR1, sig_usr1) == SIG_ERR) {
		err_sys("signal(SIGUSR1) error");
	}

	sigemptyset(&waitmask);
	sigaddset(&waitmask, SIGUSR1);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGINT);

	//** Block SIGINT and save current signal mask.
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
		err_sys("SIG_BLOCK error");
	}
	pr_sleep("bolck SIGINT", 10);

	//** Critical region of code
	pr_mask("in critical region:");

	//** Pause, allowing all signals except SIGUSR1
	if (sigsuspend(&waitmask) != -1) {
		err_sys("sigsuspend error");
	}
	pr_sleep("sigsuspend SIGUSR1", 10);
	
	pr_mask("after return from sigsuspend: ");

	//** Reset signal mask which unblock SIGINT
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
		err_sys("SIG_SETMASK error");
	}
	pr_sleep("reset to oldmask", 10);
	
	//** And continue processing ...
	pr_mask("program exit: ");
	pr_sleep("before exit", 10);
	exit(0);
}

static void sig_int(int signo) {
	pr_mask("\nin sig_int(): ");
	pr_sleep("sig_int()", 3);
}

static void sig_usr1(int signo) {
	pr_mask("\nin sig_usr1(): ");
	pr_sleep("sig_usr1()", 3);
	printf("re-signal SIGUSR1 again!\n");
	if (signal(SIGUSR1, sig_usr1) == SIG_ERR) {
		err_sys("signal(SIGUSR1) error");
	}
}

static void pr_sleep(const char* msg, int n) {
	for (int i = 0; i < n; i++) {
		printf("[%d] %s: sleep ...\n", sleep_cnt++, msg);
		sleep(1);
	}
}

