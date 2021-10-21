#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int fd;
    char *text1="AAAAA";
    char *text2="BBBBB";
    fd = open("f1.txt",O_CREAT|O_WRONLY,0600);
    if (fd == -1) {
        printf("There was an error: %d\n", errno);
        exit(1);
    }
    getchar();
    write(fd,text1,5);
    getchar();
    write(fd,text2,5);
    close(fd);
    return 0;
}