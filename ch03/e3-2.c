/* 
 * 2019-07-14 10:44
 * Call dup() until get fd=fd2, This will be super slow
 */
#include "apue.h"

int mydup2(int fd, int fd2);

int main(int argc, char** argv) {
    if (argc < 2) {
        err_ret("Usage: ./mydup2.out fd2");
    }
    int fd = 0;
    int fd2 = atoi(argv[1]);
    printf("fd=%d, fd2=%d\n", fd, fd2);

    if (fd2 < 3 || fd2 > 1000) {
        err_ret("fd2 should in range of [3, 1000]");
    }
    int ret = mydup2(fd, fd2);
    printf("mydup2 ret=%d\n", ret);

    exit(0);
}

int mydup2(int fd, int fd2) {
    if (fd2 == fd) {
        return fd2;
    }

    close(fd2);
    int fst_dup = -1;
    int cur_dup = -1;
    
    while ((cur_dup = dup(fd)) != fd2) {
        if (cur_dup < 0) {
            err_ret("dup() error, ret=%d\n", cur_dup);
        }
        if (fst_dup == -1) {
            fst_dup = cur_dup;
        }
        printf("open fd %d | ", cur_dup);
    }
    printf("\n");

    while (fst_dup < fd2) {
        printf("close fd %d | ", fst_dup);
        close(fst_dup);
        fst_dup++;
    }
    printf("\n");

    return fd2;
}

