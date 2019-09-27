#include "apue.h"

// My solution
static void func1(void) {
	pid_t pid;

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {
		printf("pid = %ld, child\n", (long)(getpid()));
		_exit(0);
	}

	// parent sleep 2 and then check zombie
	sleep(2);
	
	int status;
	char cmd[30] = "ps -aux | grep -v grep | grep ";
	char pid_str[10];
	sprintf(pid_str, "%d", pid);
	strcat(cmd, pid_str);
	printf("pid = %ld, cmd string = %s\n", (long)(getpid()), cmd);

	if ((status = system(cmd)) < 0) {
		err_sys("system() error");
	}

	sleep(2);
	exit(0);
}

// Reference
#ifdef SOLARIS
#define PSCMD "ps -a -o pid,ppid, s,tty,comm"
#else
#define PSCMD "ps -o pid,ppid,s,tty,comm"
#endif
static void func2(void) {
	pid_t pid;

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {
		exit(0);
	}

	// parent
	sleep(4);
	system(PSCMD);

	exit(0);
}

int main(int argc, char *argv[]) {
	// func1();
	func2();
	return(0);
}

