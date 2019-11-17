#include "apue.h"
#include <errno.h>

extern char *sys_siglist[];

void pr_all_mask(const char *str) {
	sigset_t sigset;
	int errno_save;
	int signo;
	
	errno_save = errno;
	if (sigprocmask(0, NULL, &sigset) < 0) {
		err_ret("sigprocmask error");
	} else {
		printf("%s:\n", str);
		for (signo = 1; ; signo++) {
			if (sys_siglist[signo] == NULL) {
				break;
			}
			if (sigismember(&sigset, signo) == -1) {
				continue;
			}
			printf("signo=%02d, signame=%s\n", signo, sys_siglist[signo]);
		}
	}
	errno = errno_save;
}

int main(void) {
	sigset_t sigset;
	if (sigfillset(&sigset) == -1) {
		err_ret("sigfillset error");
	}
	if (sigprocmask(SIG_SETMASK, &sigset, NULL) == -1) {
		err_ret("sigprocmask error");
	}
	pr_all_mask("exercise 10.09");
	return 0;
}
