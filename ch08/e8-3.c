#include "apue.h"

static void print(siginfo_t info);

int main(int argc, char *argv[]) {
	pid_t pid;
	siginfo_t info;
	siginfo_t info1;
	siginfo_t info2;
	
	// normal exit
	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {
		printf("\nchild pid = %ld\n", (long)getpid());
		exit(6);
	}
	if (waitid(P_PID, pid, &info, WCONTINUED | WEXITED | WNOWAIT) < 0) {
		err_sys("waitid error");
	}
	print(info);
	
	// abort
	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {
		printf("\nchild pid = %ld\n", (long)getpid());
		abort();
	}
	if (waitid(P_PID, pid, &info1, WCONTINUED | WEXITED | WNOWAIT) < 0) {
		err_sys("waitid error");
	}
	print(info1);

	// divide zero
	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {
		printf("\nchild pid = %ld\n", (long)getpid());
		int a = 1;
		a /= 0;
	}
	if (waitid(P_PID, pid, &info2, WCONTINUED | WEXITED | WNOWAIT) < 0) {
		err_sys("waitid error");
	}
	print(info2);
	
	exit(0);
}

static void print(siginfo_t info) {
	printf("******************************\n");
	printf("pid = %ld, siginfo_t content:\n", (long)getpid());
	printf("1. int: si_signo = %d\n", info.si_signo);
	printf("2. int: si_code = %d\n", info.si_code);
	printf("3. union sigval:\n");
	printf("   int: sival_int = %d\n", info.si_value.sival_int);
	printf("   int(*): sival_int ptr = %p\n", &(info.si_value.sival_int));
	printf("   void(*): sival_ptr = %p\n", info.si_value.sival_ptr);
	printf("4. int: si_errno = %d\n", info.si_errno);
	printf("5. pid: si_pid = %ld\n", (long)info.si_pid);
	printf("6. uid: si_uid = %ld\n", (long)info.si_uid);
	printf("7. void(*): si_addr = %p\n", info.si_addr);
	printf("8. int: si_status = %d\n", info.si_status);
	printf("9. long: si_band = %ld\n", info.si_band);
	printf("******************************\n");
}

