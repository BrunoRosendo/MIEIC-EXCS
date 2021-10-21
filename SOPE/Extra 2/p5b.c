#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int fd;
    char *text1="CCCCC";
    char *text2="DDDDD";
    fd = open("f1.txt", O_WRONLY,0600);
    if (fd == -1) {
        printf("There was an error: %d\n", errno);
        exit(1);
    }
    getchar();
    write(fd,text1,5);   write(fd,text2,5);
    close(fd);
    return 0;
}