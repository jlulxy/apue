#include "apue.h"

/*
static int func1(void) {
	sleep(2);
	printf("This is func1(), pid = %ld\n", (long)getpid());
	return 1;
}

static int func2(void) {
	printf("This is func2(), pid = %ld\n", (long)getpid());
	sleep(1);
	printf("func1 return = %d\n", func1());
	return 2;
}

int main(int argc, char *argv[]) {
	pid_t pid;
	printf("This is main() beg, pid = %ld\n", (long)getpid());

	if ((pid = vfork()) < 0) {
		err_sys("vfork error");
	} else if (pid == 0) {
		printf("func2 return = %d\n", func2());
		_exit(0);
	}

	printf("This is main() end, pid = %ld\n", (long)getpid());
}
*/

// reference
static void f1(void) {
	pid_t pid;
	if ((pid = vfork()) < 0) {
		err_sys("vfork error");
	}
	printf("pid = %ld, f1()\n", (long)getpid());
	// child and parent both return
}

static void f2(void) {
	// automatic variables
	char buf[1000];
	int i;

	for (i = 0; i < 1000; i++) {
		buf[i] = 0;
	}
	
	printf("pid = %ld, f2()\n", (long)getpid());
}

int main(void) {
	printf("pid = %ld, main()\n", (long)getpid());
	f1();
	f2();
	_exit(0);
}

