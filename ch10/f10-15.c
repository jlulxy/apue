#include "apue.h"
#include <errno.h>

static void sig_quit(int);
static void my_pr_mask(const char*, sigset_t*);

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

static void my_pr_mask(const char *str, sigset_t *set_p) {
	sigset_t sigset;
	int errno_save;
	/* we can be called by signal handlers */
	errno_save = errno;
	
	if (set_p == NULL) {
		set_p = &sigset;
		if (sigprocmask(0, NULL, set_p) < 0) {
			err_ret("sigprocmask error");
		}
	}

	printf("%s", str);
	if (sigismember(set_p, SIGINT)) {
		printf(" SIGINT");
	}
	if (sigismember(set_p, SIGQUIT)) {
		printf(" SIGQUIT");
	} 
	if (sigismember(set_p, SIGUSR1)) {
		printf(" SIGUSR1");
	}
	if (sigismember(set_p, SIGUSR2)) {
		printf(" SIGUSR2");
	}
	if (sigismember(set_p, SIGALRM)) {
		printf(" SIGALRM"); 
	}	
	/* remaining signals can go here */
	printf("\n");
	
	/* restore errno */
	errno = errno_save;
}

