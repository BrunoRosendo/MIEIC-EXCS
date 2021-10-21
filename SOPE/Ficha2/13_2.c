#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int proc;
    int np;

    if (mkfifo("/tmp/np", 0666) < 0) {
        perror("mkfifo()");
        exit(1);
    }
    if ((proc = fork()) == -1) {
        perror("fork()");
        exit(2);
    }
    if (proc == 0) {
        char msg[256];
        while ((np = open("/tmp/np", O_RDONLY)) < 0) ; // sync
        read(np, msg, 256);
        strcat(msg, " Systems");
        printf("%s\n", msg);
    } else {
        while ((np = open("/tmp/np", O_WRONLY)) < 0) ; // sync
        write(np, "Operating", 1 + strlen("Operating"));
    }

    return 0;
}