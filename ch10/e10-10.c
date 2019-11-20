/* 2019-11-17 23:59
 * Should setbuf to line then I can see printf in log file.
 * 2019-11-18
 * nohup ./e10-10.out > e10-10.log 2>&1 &
 */

#include "apue.h"
#include <time.h>

int main(void) {
	int cnt = 0;
	time_t rawtime;
	time_t lasttime = 0;
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
			printf("time_t difference = %ld\n", rawtime - lasttime);
			lasttime = rawtime;
		}
	}

	exit(0);
}

