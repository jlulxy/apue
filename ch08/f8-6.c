#include "apue.h"
#include "sys/wait.h"

static void print(int status) {
	printf("status = %d | ", status);
	int k = 0;
	for (int c = 31; c >= 0; c--) {
		k = status >> c;
		k & 1 ? printf("1") : printf("0");
	}
	printf("\n");
}

int main(int argc, char *argv[]) {
	pid_t pid;
	int status = 0;

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {
		exit(7);
		// exit(1023);
	}
	if (wait(&status) != pid) {
		err_sys("wait error");
	}
	print(status);
	pr_exit(status);

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {
		abort();
	}
	if (wait(&status) != pid) {
		err_sys("wait error");
	}
	print(status);
	pr_exit(status);

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {
		status /= 0;
	}
	if (wait(&status) != pid) {
		err_sys("wait error");
	}
	print(status);
	pr_exit(status);

	exit(0);
}

/*
void pr_exit(int status) {
	if (WIFEXITED(status)) {
		printf("normal termination, exit status = %d\n", WEXITSTATUS(status));

		......
	}
}
*/

// * Notice that WEXITSTATUS(status) just fetch the low-order 8 bits of the
// * argument that the child passed to exit, _exit, _Exit. !NOT! the low-order
// * 8 bits of the status.


