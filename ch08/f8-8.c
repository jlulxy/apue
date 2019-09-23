#include "apue.h"
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	pid_t pid;

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {
		printf("first child begin\n");
		if ((pid = fork()) < 0) {
			err_sys("fork error");
		} else if (pid > 0) {
			printf("first child end\n");
			exit(0);
		}

		//* second child
		sleep(2);
		printf("second child, parent pid = %ld\n", (long)getppid());
		exit(0);
	}

	if (waitpid(pid, NULL, 0) != pid) {
		err_sys("waitpid error");
	} else {
		printf("parent wait first child end\n");
	}

	/*
	 * We are parent (the original process); we continue executing,
	 * konwing that we are not the parent of the second child.
	 */
	exit(0);
}

/*
 * Note that the shell prints its prompt when the original process terminates,
 * which is before the second child prints its parent process ID.
 */

