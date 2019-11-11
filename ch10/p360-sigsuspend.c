#include "apue.h"
#include "pr_sleep.h"

static void sig_usr1(int);
static void sig_usr2(int);

int main() {
	if (signal(SIGUSR1, sig_usr1) == SIG_ERR) {
		err_sys("signal(SIGUSR1) error");
	}
	if (signal(SIGUSR2, sig_usr2) == SIG_ERR) {
		err_sys("signal(SIGUSR2) error");
	}

	sigset_t newmask, oldmask, waitmask;
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGUSR1);

	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
		err_sys("sigprocmask(SIG_BOLCK) error");
	}

	pr_sleep("block SIGUSR1", 10);

	sigemptyset(&waitmask);
	sigaddset(&waitmask, SIGUSR2);
	pr_sleep("begin sigsuspend(&waitmask)", 10);
	if (sigsuspend(&waitmask) != -1) {
		err_sys("sigsuspend(&waitmask) error");
	}
	
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
		err_sys("sigprocmask(SIG_SETMASK) error");
	}
	pr_sleep("sigprocmask(SIG_SETMASK)", 10);
	
	exit(0);
}

static void sig_usr1(int signo) {
	pr_mask("sig_usr1()");
	pr_sleep("sig_usr1()", 5);
	if (signal(SIGUSR1, sig_usr1) == SIG_ERR) {
		err_sys("signal(SIGUSR1) error");
	}
}

static void sig_usr2(int signo) {
	pr_mask("sig_usr2()");
	pr_sleep("sig_usr2()", 5);
	if (signal(SIGUSR2, sig_usr2) == SIG_ERR) {
		err_sys("signal(SIGUSR2) error");
	}
}
