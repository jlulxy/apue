//cat f10-20.c | ./a.out > f10-20-copy.c

#include "apue.h"
#include <sys/resource.h>

#define BUFFSIZE 100
#define FILESIZE 1024

static void sig_xfsz(int);

int main(void) {
	int r;
	int w;
	int wcnt = 0;
	char buf[BUFFSIZE];
	char log[BUFFSIZE];
	FILE *fp;

	//** set soft limit
	struct rlimit limit;
	if (getrlimit(RLIMIT_FSIZE, &limit) < 0) {
		err_sys("getrlimit error");
	}
	limit.rlim_cur = FILESIZE;
	if (setrlimit(RLIMIT_FSIZE, &limit) < 0) {
		err_sys("setrlimit error");
	}
	//** set SIGXFSZ handler
	if (signal_intr(SIGXFSZ, sig_xfsz) == SIG_ERR) {
		err_sys("signal_intr(SIGXFSZ) error");
	}
	//** open a log file
	fp = fopen("e10-11.log", "w+");

	while ((r = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) {
		sprintf(log, "read %d bytes\n", r);
		fputs(log, fp);
		
		w = write(STDOUT_FILENO, buf, r);
		
		sprintf(log, "write %d bytes\n", w);
		fputs(log, fp);
		
		if (w > 0) {
			wcnt += w;
		}
	}

	if (r < 0) {
		err_sys("read error");
	}

	sprintf(log, "successful write cnt=%d\n", wcnt);
	fputs(log, fp);
	
	exit(0);
}

static void sig_xfsz(int signo) {
	// printf("in sig_xfsz\n");
	FILE *fp;
	char log[FILESIZE];
	
	fp = fopen("e10-11-sig.log", "w+");
	
	sprintf(log, "in sig_xfsz\n");
	fputs(log, fp);
}

