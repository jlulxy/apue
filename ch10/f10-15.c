#include "apue.h"
#include "my_pr_mask.h"
#include <errno.h>

static void sig_quit(int);
static int sig_catch_cnt = 0;

int main(void) {
	sigset_t newmask, oldmask, pendmask;

	if (signal(SIGQUIT, sig_quit) == SIG_ERR) {
		err_sys("can't catch SIGQUIT");
	}
	/*
	 * Block SIGQUIT and save current signal mask
	 */
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGQUIT);
	my_pr_mask("newmask_1", &newmask);
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
		err_sys("SIG_BLOCK error");
	}
	my_pr_mask("newmask_2", &newmask);
	my_pr_mask("oldmask_1", &oldmask);
	
	/* SIGQUIT here will remain pending */
	sleep(5);

	if (sigpending(&pendmask) < 0) {
		err_sys("SIG_SETMASK error");
	}
	my_pr_mask("pendmask_1", &pendmask);
	if (sigismember(&pendmask, SIGQUIT)) {
		printf("\nSIGQUIT pending........\n");
	}

	/*
	 * Restore signal mask which unblocks SIGQUIT
	 */
	printf("\nStart SIGQUIT unblocked\n");
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
		err_sys("SIG_SETMASK error");
	}
	printf("\nAfter SIGQUIT unblocked sleeping: \n");

	/* SIGQUIT here will terminate with core file */ 
	for (int i = 0; i < 30; i++) {
		printf(">>> the %d second sleep\n", i);
		sleep(1);
	}
	printf("\n");
	exit(0);
}

static void sig_quit(int signo) {
	printf("\nThe [%d] time caught SIGQUIT in sig_quit()\n", sig_catch_cnt++);
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR) {
		err_sys("can't reset SIGQUIT");
	}
	if (signal(SIGQUIT, sig_quit) == SIG_ERR) {
		err_sys("can't catch SIGQUIT");
	} else {
		printf("sig SIGQUIT again in sig_quit() !!!\n");
	}
}

