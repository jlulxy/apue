#include "apue.h"
#include <pwd.h>

static void my_alarm(int signo) {
	struct passwd *ptr;
	
	printf("in signal handler\n");
	/* Why the code comment below will block the process?
	 * But not just corrupt??
	 */
	// if ((ptr = getpwnam("ubuntu")) == NULL) {
	// 	err_sys("getpwnam(ubuntu) error");
	// }
	// if (strcmp(ptr->pw_name, "ubuntu") != 0) {
	// 	printf("return value corrupted!, pw_name=%s\n", ptr->pw_name);
	// }
	printf("signal function with pw_name=%s\n", ptr->pw_name);
	printf("my_alarm() alarm(1)\n");
	// signal(SIGALRM, my_alarm);
	
	/* alarm() will be reset to default behavier that print a `Alarm Clock`
     * and terminate this process
	 */
	alarm(1);
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
		/* printf() is un-reentrant function, will be corrupted by signal handler
		*/
		// printf("i=%10d\n", i);
		if (i >= 100000000) {
			i = 0;
		}
	}
}

