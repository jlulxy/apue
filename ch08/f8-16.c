#include "apue.h"
#include <sys/wait.h>

char *env_init[] = { "USER=unknow", "PATH=/tmp", NULL};
char *pathname="/home/ubuntu/project/apue/ch08/echoall.out";

int main(void) {
	pid_t pid;

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {
		if (execle(pathname, "arg0", "myarg1", "MY ARG2", (char*)0, 
				   env_init) < 0) {
			err_sys("execle error");
		}
	}
	if (waitpid(pid, NULL, 0) < 0) {
		err_sys("wait error");
	}
	printf("\n---wait child pid = %d over---\n\n", pid);

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {
		if (execlp("echoall.out", "echoall.out", "only 1 argv", (char*)0) < 0) {
			err_sys("execlp error");
		}
	}
	if (waitpid(pid, NULL, 0) < 0) {
		err_sys("wait error");
	}
	printf("\n---wait child pid = %d over---\n\n", pid);
	
	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {
		if (execlp("raap.out", "argv0", "argv1", "argv2", (char*)0) < 0) {
			err_sys("execlp error");
		}
	}
	if (waitpid(pid, NULL, 0) < 0) {
		err_sys("wait error");
	}
	printf("\n---wait child pid = %d over---\n\n", pid);

	exit(0);
}

// export PATH=$PATH:/home/ubuntu/project/apue/ch08

