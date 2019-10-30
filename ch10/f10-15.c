#include "apue.h"
#include "my_pr_mask.h"
#include <errno.h>

static void sig_quit(int);

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
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
		err_sys("SIG_SETMASK error");
	}
	printf("\nSIGQUIT unblocked\n");

	/* SIGQUIT here will terminate with core file */ 
	sleep(30);
	exit(0);
}

static void sig_quit(int signo) {
	printf("caught SIGQUIT");
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR) {
		err_sys("can't reset SIGQUIT");
	}

}

