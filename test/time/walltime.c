#include <time.h>
#include <stdint.h>
#include <sys/time.h>
#include <stdio.h>

int32_t GetWallTimestamp();

int main() {
	printf("GetWallTimestamp=%d\n", GetWallTimestamp());
}


int32_t GetWallTimestamp() {
	struct timespec ts;
	if (!clock_gettime(CLOCK_REALTIME, &ts)) {
		return (int32_t)ts.tv_sec;
	}

	struct timeval tv;
	if (!gettimeofday(&tv, NULL)) {
		return (int32_t)tv.tv_sec;
	}

	return (int32_t)time(NULL);
}
