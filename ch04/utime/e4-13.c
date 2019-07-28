#include "apue.h"
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int i, fd;
    struct stat statbuf;
    struct timespec times[3];

    for (i = 1; i < argc; i++) {
        if (stat(argv[i], &statbuf) < 0) {
            err_ret("%s: stat error", argv[i]);
            continue;
        }
        times[0] = statbuf.st_atim;
        times[1] = statbuf.st_mtim;
        times[2] = statbuf.st_ctim;
        printf("atime: tv_sec=%ld, tv_nsec=%ld\n",
                times[0].tv_sec, times[0].tv_nsec);
        printf("mtime: tv_sec=%ld, tv_nsec=%ld\n",
                times[1].tv_sec, times[1].tv_nsec);
        printf("ctime: tv_sec=%ld, tv_nsec=%ld\n\n",
                times[2].tv_sec, times[2].tv_nsec);
    }
}
