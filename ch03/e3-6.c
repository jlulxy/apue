/*
 * Has file access permissions problem when re-open file "test.txt".
 * For now, just use sudo. We'll show how to specify mode in creat()
 * function is Section 4.5 when we describe a file's access permissions
 * in detail.
 */
#include "apue.h"
#include <fcntl.h>

char buf[] = "abcdefghij";

int main(void) {
    int fd;
    int size;

    if ((fd = open("file3-6.txt", O_RDWR | O_APPEND)) == -1) {
        err_sys("open error");
    }
    if ((size = write(fd, buf, 10)) != 10) {
        err_sys("write error");
    }

    off_t currpos;
    currpos = lseek(fd, 0, SEEK_CUR);
    printf("offset=0, SEEK_CUR, currpos=%lld\n", currpos);

    currpos = lseek(fd, 5, SEEK_SET);
    printf("offset=5, SEEK_SET, currpos=%lld\n", currpos);

    char buf2[5];
    if ((size = read(fd, buf2, 5)) != 5) {
        err_sys("read error");
    }
    currpos = lseek(fd, 0, SEEK_CUR);
    printf("offset=0, SEEK_CUR, currpos=%lld\n", currpos);
    printf("read buf=%s\n", buf2);    
    exit(0);
}

