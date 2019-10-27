#include "apue.h"
#include <pwd.h>

static void my_alarm(int signo) {
	struct passwd *rootptr;
	
	printf("in signal handler\n");
	if ((rootptr = getpwnam("ubuntu")) == NULL) {
		err_sys("getpwnam(ubuntu) error");
	}
	alarm(1);
	printf("signal function with pw_name=%s\n", rootptr->pw_name);
	printf("my_alarm() alarm(1)\n");
}

int main(void) {
	struct passwd *ptr;
	int i;

	printf("main before signal() function\n");
	signal(SIGALRM, my_alarm);
	printf("main after signal() function\n");
	
	printf("main alarm(1)\n");
	alarm(1);

	for (i = 0; i >= 0; i++) {
		if ((ptr = getpwnam("ubuntu")) == NULL) {
			err_sys("getpwnam(ubuntu) error");
		}
		if (strcmp(ptr->pw_name, "ubuntu") != 0) {
			printf("return value corrupted!, pw_name=%s\n", ptr->pw_name);
		}
		// printf("i=%8d with pw_name=%s\n", i, ptr->pw_name);
		if (i >= 100000000) {
			i = 0;
		}
	}
}

