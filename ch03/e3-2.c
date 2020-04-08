/*
3.2 编写一个与3.12节中dup2功能相同的函数，要求不屌用fcntl函数，并且要有正确的出错处理。
本质就是一次打开小于fd2的函数通过dup，找到后再关闭之前的打开的fd
*/
/* 
 * 2019-07-14 10:44
 * Call dup() until get fd=fd2, This will be super slow
 */
#include "apue.h"
#include "stdlib.h"

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
    size_t write_size;
    write(fd2,"hello World!\n",sizeof("hello World!\n"));
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

