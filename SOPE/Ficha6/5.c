#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("test.txt", O_RDONLY);
    char c;

    printf("Sequential read:\n");

    off_t offset;
    while (read(fd, &c, 1) > 0) {
        offset = lseek(fd, 0, SEEK_CUR);
        printf("%ld\n", offset);
    }

    printf("Random access:\n");
    offset = lseek(fd, 6, SEEK_SET);
    printf("%ld\n", offset);

    close(fd);
}