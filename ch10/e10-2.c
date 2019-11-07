//** Implement the `sig2str` described in Section 10.22
#include "apue.h"

extern char *sys_siglist[];

static int sig2str(int, char*);

int main(int argc, char **argv) {
	int signo, ret;
	char sigstr[40];

	if (argc < 2) {
		printf("Usage: ./a.out signo\n");
		return 0;
	}
	signo = atoi(argv[1]);
	printf("input signo=%d\n", signo);
	ret = sig2str(signo, sigstr);
	if (ret != 0) {
		printf("error signo: %d\n", signo);
		return 0;
	}
	printf("signo: %d ==> sigstr: %s\n", signo, sigstr);
	
	return 0;
}

static int sig2str(int signo, char *sigstr) {
	//** Can't use sizeof() on extern variables.
	// size_t len = sizeof(sys_siglist) / sizeof(char*);
	//** if signo >= 32 will get segment fault.
	// int len = 32;
	int len = 320;
	if (0 > signo || signo >= len) {
		printf("sig2str() invalid signo=%d\n", signo);
		return -1;
	}
	//** if signo=0 will core cause sys_siglist[0]=null, there is no signo 0!
	printf("sys_siglist[%d]=%s\n", signo, sys_siglist[signo]);
	strcpy(sigstr, sys_siglist[signo]);
	return 0;
}

