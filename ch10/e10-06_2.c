/* 
 * 2019-11-10 eggmeng
 * In this version, I first fopen a file, and pass the FILE pointer to both
 * processes.
 * But why parent and child both print increase n to 49?
 */

#include "apue.h"

static int increase_at_a_time(FILE *fp);

int main(void) {
	FILE *fp = NULL;
	int c = 0;
	pid_t pid;

	if ((fp = fopen("e10-06.txt", "w+")) == NULL) {
		err_sys("fopen error");
	}
	if (putc(c + '0', fp) == -1) {
		err_sys("putc error");
	}
	// fflush(fp);
	rewind(fp);
	if ((c = getc(fp)) == -1) {
		err_sys("getc error");
	}
	printf("before parent-child c=%d\n", c);
	
	TELL_WAIT();
	
	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {
		printf("child pid = %d\n", getpid());
		sleep(1);
		WAIT_PARENT();
		//** Error output: `getc error: Interrupted system call`
		//** See more in e10-06_2.c
		//** Use mode "r+" instead of "w+":
		// if ((fp = fopen("e10-06.txt", "w+")) == NULL) {
		// 	err_sys("fopen error");
		// }
		int c = increase_at_a_time(fp);
		printf("childd: %d increase int to %d\n", getpid(), c);
		printf("child %d finished!\n", getpid());
	} else {
		printf("parent pid = %d\n", getpid());
		sleep(1);
		int c = increase_at_a_time(fp);
		printf("parend: %d increase int to %d\n", getpid(), c);
		TELL_CHILD(pid);
		printf("parent %d finished!\n", getpid());
		fclose(fp);
	}

	return 0;
}

static int increase_at_a_time(FILE *fp) {
	int n = 0;
	rewind(fp);
	
	if ((n = getc(fp)) == -1) {
		err_sys("pid:%d getc() error", getpid());
	}
	printf("pid: %d getc() get n=%d\n", getpid(), n);
	
	n = n + 1;
	if (putc(n, fp) == -1) {
		err_sys("pid:%d putc() error", getpid());
	}
	printf("pid: %d putc() put n=%d\n", getpid(), n);

	return n;
}
