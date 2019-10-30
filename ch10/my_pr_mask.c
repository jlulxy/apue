#include "apue.h"
#include "my_pr_mask.h"
#include <errno.h>

void my_pr_mask(const char *str, sigset_t *set_p) {
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

	printf("%s[", str);
	if (sigismember(set_p, SIGINT)) {
		printf("SIGINT, ");
	}
	if (sigismember(set_p, SIGQUIT)) {
		printf("SIGQUIT, ");
	} 
	if (sigismember(set_p, SIGUSR1)) {
		printf("SIGUSR1, ");
	}
	if (sigismember(set_p, SIGUSR2)) {
		printf("SIGUSR2, ");
	}
	if (sigismember(set_p, SIGALRM)) {
		printf("SIGALRM"); 
	}	
	/* remaining signals can go here */
	printf("]\n");
	
	/* restore errno */
	errno = errno_save;
}
