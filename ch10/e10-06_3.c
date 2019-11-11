/* 
 * 2019-11-11 eggmeng
 * Delete recall fopen() in child, the problem is, after getc/putc file offset
 * will be 1, always pay attention to offset and call rewind.
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
	if (putc(c + 'a', fp) == -1) {
		err_sys("putc error");
	}
	// fflush(fp);
	rewind(fp);
	
	//** 2019-11-11
	//** I can set fp unbuffered instead of calling fflush(fp) everytime
	//** in function increase_at_a_time().
	setbuf(fp, NULL);

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
		c = increase_at_a_time(fp);
		printf("childd: %d increase int to %d\n", getpid(), c);
		printf("childd: %d finished!\n", getpid());
	} else {
		printf("parent pid = %d\n", getpid());
		sleep(1);
		c = increase_at_a_time(fp);
		printf("parent: %d increase int to %d\n", getpid(), c);
		printf("parent: %d finished!\n", getpid());
		TELL_CHILD(pid);
		//** fflush here doesn't work cause this just flush parent's IO.
		//** We need flush child opened IO.
		fflush(fp);
	}

	return 0;
}

static int increase_at_a_time(FILE *fp) {
	int n = 0;
	//** !!!MUST flush IO to detect chaning.
	//** Already set fp unbuffered.
	//fflush(fp);

	printf("\nin increase_at_a_time() fp offset=%ld\n", ftell(fp));	
	rewind(fp);
	if ((n = getc(fp)) == -1) {
		err_sys("pid:%d getc() error", getpid());
	}
	printf("pid: %d getc() get n=%d\n", getpid(), n);
	printf("getc() then fp offset=%ld\n", ftell(fp));	
	
	n = n + 1;
	rewind(fp);
	if (putc(n, fp) == -1) {
		err_sys("pid:%d putc() error", getpid());
	}
	printf("pid: %d putc() put n=%d\n", getpid(), n);
	printf("putc() then fp offset=%ld\n", ftell(fp));	

	return n;
}
