#include "apue.h"
#include <sys/wait.h>

char *env_init[] = { "USER=unknow", "PATH=/tmp", NULL};
char *pathname="/home/ubuntu/project/apue/ch08/echoall";

int main(void) {
	pid_t pid;

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {
		if (execle(pathname, "echoall", "myarg1", "MY ARG2", (char*)0, 
				   env_init) < 0) {
			err_sys("execle error");
		}
	}
	if (waitpid(pid, NULL, 0) < 0) {
		err_sys("wait error");
	}

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {
		if (execlp("echoall", "echoall", "only 1 argv", (char*)0) < 0) {
			err_sys("execlp error");
		}
	}

	exit(0);
}

// export PATH=$PATH:/home/ubuntu/project/apue/ch08

