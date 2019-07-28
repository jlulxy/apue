#include "apue.h"
#include <fcntl.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {
    int i, fd, ret;
    struct stat statbuf;
    struct timespec times[3];
	struct timeval mytimes[2];
	char pathbuf[80];
	int pathlen;

    for (i = 1; i < argc; i++) {
        if (stat(argv[i], &statbuf) < 0) {
            err_ret("%s: stat error", argv[i]);
            continue;
        }
        times[0] = statbuf.st_atim;
        times[1] = statbuf.st_mtim;
        times[2] = statbuf.st_ctim;
        
		if (i == 1) {
			getcwd(pathbuf, sizeof(pathbuf));
			pathlen = strlen(pathbuf);
			printf("pathbuf=%s, pathlen=%d\n", pathbuf, pathlen);
			
			pathbuf[pathlen++] = '/';
			pathbuf[pathlen] = 0;
			strcpy(&pathbuf[pathlen], argv[i]);
			mytimes[0].tv_sec = statbuf.st_atim.tv_sec;
			mytimes[0].tv_usec = statbuf.st_atim.tv_nsec / 1000;
			mytimes[1].tv_sec = statbuf.st_mtim.tv_sec;
			mytimes[1].tv_usec = statbuf.st_mtim.tv_nsec / 1000;
			mytimes[1].tv_sec -= 1000000;
			// ret = utimes(pathbuf, mytimes);
			ret = utimes(argv[i], mytimes);
			if (ret != 0) {
				err_ret("utime error ret=%d, pathbuf=%s\n", ret, pathbuf); 
			}
		}

		printf("atime: tv_sec=%ld, tv_nsec=%ld\n",
                times[0].tv_sec, times[0].tv_nsec);
        printf("mtime: tv_sec=%ld, tv_nsec=%ld\n",
                times[1].tv_sec, times[1].tv_nsec);
        printf("ctime: tv_sec=%ld, tv_nsec=%ld\n\n",
                times[2].tv_sec, times[2].tv_nsec);
    }
}
