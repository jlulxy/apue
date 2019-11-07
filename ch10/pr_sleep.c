#include "pr_sleep.h"

static int sleep_cnt = 0;
void pr_sleep(const char *msg, int n) {
	for (int i = 0; i < n; i++) {
		printf("[%d] %s: sleep ...\n", sleep_cnt++, msg);
		sleep(1);
	}
}

