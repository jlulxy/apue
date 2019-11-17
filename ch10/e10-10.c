/* 2019-11-17 23:59
 * Should setbuf to line then I can see printf in log file.
 */

#include "apue.h"
#include <time.h>

int main(void) {
	int cnt = 0;
	time_t rawtime;
	struct tm *tm_info = NULL;

	setbuf(stdout, 0);

	while (1) {
		cnt++;
		sleep(60);
		if (cnt % 5 == 0) {
			cnt = 0;
			time(&rawtime);
			tm_info = localtime(&rawtime);
			printf("Current local time and date: %s\n", asctime(tm_info));
		}
	}

	exit(0);
}

